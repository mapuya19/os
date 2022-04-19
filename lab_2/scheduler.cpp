#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
using namespace std;

struct process {
  int pid;
  int R1;
  int B1;
  int R2;
  int B2;

  // N/A == 999
  // ready == 1
  // running == 2
  // blocked == 3
  // ready to terminate == 4
  // terminated == 0
  int state;

  // N/A == 999
  // R1 == 1
  // B1 == 2
  // R2 == 3
  // B2 == 4
  // ready to terminate == 5
  // terminated == 0
  int stage;

  string print_state() {
    if (state == 1) {
      return "Ready";
    } else if (state == 2) {
      return "Run";
    } else if (state == 3) {
      return "Blocked";
    } else if (state == 4) {
      return "Ready";
    } else if (state == 0) {
      return "";
    } else {
      return "";
    }
  }

  string print_stage() {
    if (stage == 1) {
      return "R1 ";
    } else if (stage == 2) {
      return "B1 ";
    } else if (stage == 3) {
      return "R2 ";
    } else if (stage == 4) {
      return "B2 ";
    } else if (stage == 5) {
      return "";
    } else {
      return "";
    }
  }
};

// print out each time
template<typename T> void print_part(T t, const int& width, const char& separator) {
    cout << left << setw(width) << setfill(separator) << t;
}

void fifo(int n, process *p) {
  int cycle = 1;
  bool process_is_running = false;
  bool process_is_terminating = false;
  int cycled = 0;
  int terminated = 0;
  queue<process> processes;

  const char separator = ' ';
  const int cycle_width = 8;
  const int process_width = 20;

  // fill queue
  for (int i = 1; i <= n; i++) {
    p[i].pid = i;
    processes.push(p[i]);
  }

  // print header
  print_part("Cycle", cycle_width, separator);
  for (int i = 1; i <= n; i++) {
    print_part("P" + to_string(i) + " State", process_width, separator);
  }
  cout << endl;

  // cycle 1
  for (int i = 0; i < n; i++) {
    process current = processes.front();
    processes.pop();

    // start R1
    if (i == 0) {
      current.state = 2;
      current.stage = 1;
      process_is_running = true;
    }
    
    // all other processes ready
    else {
      current.state = 1;
      current.stage = 1;
    }

    processes.push(current);
  }

  // cycle++;
  print_part(cycle, cycle_width, separator);

  // cycles after 1
  while (terminated <= n) {
    process current = processes.front();
    processes.pop();
    cycled++;
    // cout << current.pid;

    // if a process is not running
    if (process_is_running == false) {
      // if current terminated, print blank
      if (current.state == 0 && current.stage == 0) {
        print_part(current.print_state(), process_width, separator);
        goto skipping;
      }
      
      // if current is ready for R1 or R2
      else if (current.state == 1 && (current.stage == 1 || current.stage == 3)) {
        current.state = 2;

        if (current.stage == 1) {
          current.R1--;
          print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
        } else if (current.stage == 3) {
          current.R2--;
          print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
        }

        process_is_running = true;
      } 
      
      // if current is ready to terminate
      else if (current.state == 4 && current.stage == 5) {
        print_part("Terminate", process_width, separator);
        current.state = 0;
        current.stage = 0;
        process_is_terminating = true;
        process_is_running = true;
      }
      
      // if current is blocking B1 or B2
      else if (current.state == 3 && (current.stage == 2 || current.stage == 4)) {
        if (current.stage == 2) {
          // if current B1 finishes, run R2
          if (current.B1 == 0) {
            current.state = 2;
            current.stage = 3;
            current.R2--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
            process_is_running = false;
          } else {
            current.B1--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }

        else if (current.stage == 4) {
          // if current B2 finishes, terminate
          if (current.B2 == 0) {
            print_part("Terminate", process_width, separator);
            current.state = 0;
            current.stage = 0;
            cout << "\n\n";
            cout << "Finished FIFO.";
            break;
          } else {
            current.B2--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }
      }
    }

    // if a process is running
    else if (process_is_running == true) {
      // if current is terminated
      if (current.state == 0 && current.stage == 0) {
        print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
        goto skipping;
      } 
      
      // if current is ready
      else if (current.state == 1 && (current.stage == 1 || current.stage == 3)) {
        print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
      } 
      
      // if current is ready to terminate
      else if (current.state == 4 || current.stage == 5) {
        print_part(current.print_state(), process_width, separator);
      }
      
      // if current is running R1 or R2
      else if (current.state == 2 && (current.stage == 1 || current.stage == 3)) {
        if (current.stage == 1) {
          // if current R1 finishes, run B1
          if (current.R1 == 0) {
            current.state = 3;
            current.stage = 2;
            current.B1--;
            
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
            process_is_running = false;
          } else {
            current.R1--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }

        else if (current.stage == 3) {
          // if current R2 finishes, run B2
          if (current.R2 == 0) {
            current.state = 3;
            current.stage = 4;
            current.B2--;

            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
            process_is_running = false;
          } else {
            current.R2--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }
      }

      // if current is blocking B1 or B2      
      else if (current.state == 3 && (current.stage == 2 || current.stage == 4)) {
        if (current.stage == 2) {
          if (current.B1 == 0) {
            // set current ready
            current.state = 1;
            current.stage = 3;

            // print ready
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          } else {
            current.B1--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }

        else if (current.stage == 4) {
          // if B2 finishes, set current ready to terminate
          if (current.B2 == 0) {
            current.state = 4;
            current.stage = 5;
            print_part(current.print_state(), process_width, separator);
          } else {
            current.B2--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }
      }
    }

    // if all processes have gone through the cycle
    if (cycled == n) {
      cycled = 0;
      cycle++;

      cout << endl;
      print_part(cycle, cycle_width, separator);
      
      // if current will block in the next cycle
      if (current.state == 2) {
        if (current.stage == 1 && current.R1 == 0) {
          process_is_running = false;
        } else if (current.stage == 3 && current.R2 == 0) {
          process_is_running = false;
        }
      }

      // if current will finish R1 next cycle
      if (current.R1 == 0 && current.stage == 1) {
        current.state = 3;
        current.stage = 2;
      } 
      
      // if current will finish R2 next cycle
      else if (current.R2 == 0 && current.stage == 3) {
        current.state = 3;
        current.stage = 4;
      }

      // if a process terminated this cycle -> reset the bools
      if (process_is_terminating == true) {
        terminated++;
        process_is_running = false;
        process_is_terminating = false;
      }
    }

    skipping:
      processes.push(current);
  }
 }

void rr(int n, int q, process *p) {
  int cycle = 1;
  bool process_is_running = false;
  bool process_is_terminating = false;
  int cycled = 0;
  int terminated = 0;
  queue<process> processes;

  const char separator = ' ';
  const int cycle_width = 8;
  const int process_width = 20;

  // fill queue
  for (int i = 1; i <= n; i++) {
    p[i].pid = i;
    processes.push(p[i]);
  }

  // print header
  print_part("Cycle", cycle_width, separator);
  for (int i = 1; i <= n; i++) {
    print_part("P" + to_string(i) + " State", process_width, separator);
  }
  cout << endl;

  // cycle 1
  for (int i = 0; i < n; i++) {
    process current = processes.front();
    processes.pop();

    // start R1
    if (i == 0) {
      current.state = 2;
      current.stage = 1;
      process_is_running = true;
    }
    
    // all other processes ready
    else {
      current.state = 1;
      current.stage = 1;
    }

    processes.push(current);
  }

  // cycle++;
  print_part(cycle, cycle_width, separator);

  // cycles after 1
  while (terminated <= n) {
    process current = processes.front();
    processes.pop();
    cycled++;
    // cout << current.pid;

    // if a process is not running
    if (process_is_running == false) {
      // if current terminated, print blank
      if (current.state == 0 && current.stage == 0) {
        print_part(current.print_state(), process_width, separator);
        goto skipping;
      }
      
      // if current is ready for R1 or R2
      else if (current.state == 1 && (current.stage == 1 || current.stage == 3)) {
        current.state = 2;

        if (current.stage == 1) {
          current.R1--;
          print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
        } else if (current.stage == 3) {
          current.R2--;
          print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
        }

        process_is_running = true;
      } 
      
      // if current is ready to terminate
      else if (current.state == 4 && current.stage == 5) {
        print_part("Terminate", process_width, separator);
        current.state = 0;
        current.stage = 0;
        process_is_terminating = true;
        process_is_running = true;
      }
      
      // if current is blocking B1 or B2
      else if (current.state == 3 && (current.stage == 2 || current.stage == 4)) {
        if (current.stage == 2) {
          // if current B1 finishes, run R2
          if (current.B1 == 0) {
            current.state = 2;
            current.stage = 3;
            current.R2--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
            process_is_running = false;
          } else {
            current.B1--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }

        else if (current.stage == 4) {
          // if current B2 finishes, terminate
          if (current.B2 == 0) {
            print_part("Terminate", process_width, separator);
            current.state = 0;
            current.stage = 0;
            cout << "\n\n";
            cout << "Finished FIFO.";
            break;
          } else {
            current.B2--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }
      }
    }

    // if a process is running
    else if (process_is_running == true) {
      // if current is terminated
      if (current.state == 0 && current.stage == 0) {
        print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
        goto skipping;
      } 
      
      // if current is ready
      else if (current.state == 1 && (current.stage == 1 || current.stage == 3)) {
        print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
      } 
      
      // if current is ready to terminate
      else if (current.state == 4 || current.stage == 5) {
        print_part(current.print_state(), process_width, separator);
      }
      
      // if current is running R1 or R2
      else if (current.state == 2 && (current.stage == 1 || current.stage == 3)) {
        if (current.stage == 1) {
          // if current R1 finishes, run B1
          if (current.R1 == 0) {
            current.state = 3;
            current.stage = 2;
            current.B1--;
            
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
            process_is_running = false;
          } else {
            current.R1--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }

        else if (current.stage == 3) {
          // if current R2 finishes, run B2
          if (current.R2 == 0) {
            current.state = 3;
            current.stage = 4;
            current.B2--;

            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
            process_is_running = false;
          } else {
            current.R2--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }
      }

      // if current is blocking B1 or B2      
      else if (current.state == 3 && (current.stage == 2 || current.stage == 4)) {
        if (current.stage == 2) {
          if (current.B1 == 0) {
            // set current ready
            current.state = 1;
            current.stage = 3;

            // print ready
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          } else {
            current.B1--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }

        else if (current.stage == 4) {
          // if B2 finishes, set current ready to terminate
          if (current.B2 == 0) {
            current.state = 4;
            current.stage = 5;
            print_part(current.print_state(), process_width, separator);
          } else {
            current.B2--;
            print_part(current.print_state() + " " + current.print_stage(), process_width, separator);
          }
        }
      }
    }

    // if all processes have gone through the cycle
    if (cycled == n) {
      cycled = 0;
      cycle++;

      cout << endl;
      print_part(cycle, cycle_width, separator);
      
      // if current will block in the next cycle
      if (current.state == 2) {
        if (current.stage == 1 && current.R1 == 0) {
          process_is_running = false;
        } else if (current.stage == 3 && current.R2 == 0) {
          process_is_running = false;
        }
      }

      // if current will finish R1 next cycle
      if (current.R1 == 0 && current.stage == 1) {
        current.state = 3;
        current.stage = 2;
      } 
      
      // if current will finish R2 next cycle
      else if (current.R2 == 0 && current.stage == 3) {
        current.state = 3;
        current.stage = 4;
      }

      // if a process terminated this cycle -> reset the bools
      if (process_is_terminating == true) {
        terminated++;
        process_is_running = false;
        process_is_terminating = false;
      }
    }

    if (cycle == 13) {
      break;
    }

    skipping:
      processes.push(current);
  }
}

int main() {
  int n;
  int SA;
  int q;
  process p[10];

  // bool is_done = false;
  cout << "Enter process count: ";
  cin >> n;

  cout << "Enter SA: ";
  cin >> SA;

  if (SA == 2) {
    cout << "Enter time quantum: ";
    cin >> q;
  }

  for (int i = 1; i <= n ; i++) {
    cout << "Enter R1 B1 R2 B2 for process " << i << ": ";
    cin >> p[i].R1 >> p[i].B1 >> p[i].R2 >> p[i].B2;
    p[i].state = 999;
    p[i].stage = 999;
    cout << "\n";
  }

  if (SA == 1) {
    fifo(n, p);
  } else {
    rr(n, q, p);
  }

  return 0;
}
