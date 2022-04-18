#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <assert.h>
using namespace std;

struct process {
  // set (cycle)? equal to current stage
  // decrement every 1ms cycle until 0, move to next stage
  int pid;
  int cycle;
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

  string toString() {
    if (stage == 1) {
      return "R1";
    } else if (stage == 2) {
      return "B1";
    } else if (stage == 3) {
      return "R2";
    } else if (stage == 4) {
      return "B2";
    } else if (stage == 5) {
      return "terminate";
    } else {
      return "none";
    }
  }
};



void fifo(int n, int q, int SA, process *p) {
  int cycle = 1;
  bool process_is_running = false;
  bool process_is_terminating = false;
  int cycled = 0; // + 1 when all processes cycled
  int terminated = 0;
  vector<process> processes;

  // fill queue
  for (int i = 0; i < n; i++) {
    if (p[i].pid != 0) {
      processes.push_back(p[i]);
    }
  }

  cout << "Cycle  ";
  for (int i = 0; i < n; i++) {
    cout << "P" << i << " State       ";
  }
  cout << endl;

  // cycle 1
  for (int i = 0; i < n; i++) {
    vector<process> temp = processes;
    process current = temp.front();
    temp.erase(temp.begin());
    
    if (i == 0) {
      current.state = 2;
      current.stage = 1;
      current.R1--;

      cout << cycle << "      run R1";
    } else {
      current.state = 1;

      cout << cycle << "      " << current.state << " " << current.toString();
    } 
  }

  // cycles after 1
  while (terminated != n) {
    vector<process> temp = processes;
    process current = temp.front();
    temp.erase(temp.begin());
    cycled++;

    cout << cycle;
    if (process_is_running == false) {
      if (current.state == 0 && current.stage == 0) {
        continue;
      } else if (current.state == 1 &&
                 (current.stage == 1 || current.stage == 3)) {
        if (current.stage == 1) {
          current.R1--;
        } else if (current.stage == 2) {
          current.R2--;
        }

        current.state = 2;
        process_is_running = true;
      } else if (current.state == 4 && current.stage == 4) {
        current.state = 0;
        current.stage = 0;
        process_is_terminating = true;
        process_is_running == true;
      } else if (current.state == 3 &&
                 (current.stage == 2 || current.stage == 4)) {
        // continue blocking B1 or B2
        // if B1 finishes -> run R2
        if (current.B1 == 0) {
          current.stage = 3;
        }

        if (current.B2 == 0) {
          current.state = 0;
          current.stage = 0;
          process_is_terminating = true;
          process_is_running = false;
        }
      }
    } 
    
    else if (process_is_running == true) {
      if (current.state == 0 && current.stage == 0) {
        continue;
      } else if ((current.state == 1 &&
                  (current.stage == 1 || current.stage == 3)) ||
                 current.state == 4) {
        // keep at ready
      } else if (current.state == 2 && (current.stage == 1 || current.stage == 3)) {
        // continue running R1 or R2
        if (current.R1 == 0) {
          current.stage = 2;
        }

        if (current.R2 == 0) {
          current.stage == 4;
        }

        process_is_running == false;
      } else if (current.state = 3 && (current.stage == 2 || current.stage == 4)) {
        // continue blocking B1 or B2
        if (current.stage == 2 && current.B1 != 0) {
          current.B1--;
        }

        if (current.stage == 4 && current.B2 != 0) {
          current.B2--;
        }

        if (current.stage == 2 && current.B1 == 0) {
          current.stage = 3;
        }

        if (current.stage == 4 && current.B2 == 0) {
          current.state = 4;
          current.stage = 5;
        }
      }
    }

    // edge cases -> if all processes have gone through the cycle
    if (cycled == n) {
      cycled == 0;
      cycle++;
      
      // if P is the last process in the cycle
      if (current.pid == n) {
        // ???
      }

      if (current.state == 3) {
        process_is_running ==
            false; // allows a new P to run instead of remain ready
      }

      if (current.R1 == 1 || current.R2 == 1) {
        current.stage = 2;
      }
    }

    // if a process terminated this cycle -> reset the bools
    // same situation, allow the next process P to run instead of remain ready
    if (process_is_terminating == true) {
      process_is_running = false;
      process_is_terminating = false;
    }
    
    // push P to back of queue
    temp.push_back(current);
    cycle++;
  }
}

void rr() {}

int main() {
  int n;
  int SA;
  int q;
  struct process p[10];

  bool is_done = false;
  cout << "Enter process count: ";
  cin >> n;

  cout << "Enter SA: ";
  cin >> SA;

  if (SA == 2) {
    cout << "Enter time quantum: ";
    cin >> q;
  }

  for (int i = 0; i < n; i++) {
    p[i].pid = i + 1;
    cout << "Enter R1 B1 R2 B2 for process " + p[i].pid;
    cin >> p[i].R1 >> p[i].B1 >> p[i].R2 >> p[i].B2;
    p[i].state = 999;
    p[i].stage = 999;
    cout << endl;
  }

  if (SA == 1) {
    fifo(n, SA, q, p);
  } else {
    rr();
  }

  return;
}
