#include <iostream>
#include <string>
using namespace std;

struct process {
  int pid;
  int r1_total;
  int r1_current;
  int b1_total;
  int b1_current;
  bool r1_finish = false;
  bool b1_finish = false;

  int r2_total;
  int r2_current;
  int b2_total;
  int b2_current;
  bool r2_finish = false;
  bool b2_finish = false;

  string state = "Ready";
  bool terminate = false;
};

bool check_finish(process p1, process p2) {
  return (p1.terminate && p2.terminate);
}

void fifo(int n, int q, int SA, process *p) {
  int cycle_count = 1;
  
  // process count??
  for (int i = 0; i < n; i++) {
    // if p[i]

    // // Tie Breaker
    // if (p[i].state == "Ready" && p[i+1].state == "Ready" && p[i].r1_finish == false) {
    //     p[i].state = "Run";
    // }

    // if (p[i].state == "Run" && p[i+1].state == "Ready" && p[i].r1_finish == false) {
    //     for (int j = 1; j <= p[i].r1_total; j++) {
    //         p[i].r1_current++;
    //         cout << cycle_count << "    " << p[i].state << " (" << p[i].r1_current << " of " << p[i].r1_total << ")   " << p[i + 1].state;
    //         cycle_count++;
    //     }

    //     p[i].state = "Blocked";
    //     p[i].r1_finish = true;
    // }

    // if (p[i].state == "Blocked" && p[i+1].state == "Ready" && p[i].r1_finish = true) {
    //     p[i+1].state = "Run";
    //     for (int j = 1; j <= p[i+1].r1_total; j++) {
           
    //         p[i+1].r1_current++;
    //         if (p[i].b1_finish == false) {
    //              p[i].b1_current++;
    //             cout << cycle_count << "    " << p[i].state << " (" << p[i].b1_current << " of " << p[i].b1_total << ")   " << p[i + 1].state << " (" << p[i+1].r1_current << " of " << p[i+1].r1_total << ")   " ;
    //         } else if (p[i].b1_finish == true) {
    //             cout << cycle_count << "    " << p[i].state << " (" << p[i].b1_current << " of " << p[i].b1_total << ")   " << p[i + 1].state << " (" << p[i+1].r1_current << " of " << p[i+1].r1_total << ")   " ;
    //         }
    //         cycle_count++;
    //     }
    // }

    // if (p[i].state == "Blocked" && p[i+1].state == "Run") {

    // }

    // if (p[i].state == "Ready" && p[i+1].state == "Run") {

    // }

    // if (p[i].state == "Terminate" && p[i+1].state == "Run") {

    // }

    

    for (int k = 1; k <= p[n].r1_total; k++) {
        
    //   if (i == 0 && p[i].state == "") {
    //     p[i].state = "Run";
    //     p[i + 1].state = "Ready";
    //   }

    //   p[j].run_time_current =

    //       cout << cycle_count << "    " << p[j].state << " (" << k << " of "
    //            << p[j].run_time_total << ")   " << p[j + 1].state;
    //   cycle_count++;

    //   if (p[n].r1_current == p[n].r1_total) {
    //       for (int l = 1; l <= p[n].r2_total; l++) {

    //       }
    //   }
    }
  }
}

void rr() {}

int main() {
  int n;
  int SA;
  int q;
  struct process p[100];

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
    cout << "Enter R1 B1 R2 B2";
    cin >> p[i].r1_total >> p[i].b1_total >> p[i].r2_total >> p[i].b2_total;
    p[i].pid = i + 1;
    cout << endl;
  }

  if (SA == 1) {
    fifo(n, SA, q, p);
  } else { rr(); }

  return;
}
