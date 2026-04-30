/*
=======================================================
  Smart Scheduler & Resource Allocator
  Interactive Terminal Version
=======================================================
  Algorithms:
    1. Greedy  -> Task Scheduling (Activity Selection)
    2. DP      -> Resource Allocation (0/1 Knapsack)
=======================================================
*/
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
 
using namespace std;
 
struct Task {
    string name;
    int start;
    int end;
};
 
struct Resource {
    string name;
    int cost;
    int value;
};
 
// ── Helpers ──────────────────────────────────────────
// Read everything as a full line — avoids cin>> / getline mixing bug
 
string read_line(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}
 
int read_int(const string& prompt) {
    while (true) {
        string s = read_line(prompt);
        stringstream ss(s);
        int n;
        if (ss >> n) return n;
        cout << "  [!] Please enter a valid number.\n";
    }
}
 
void print_line(char c = '-', int len = 50) {
    cout << "\n" << string(len, c) << "\n";
}
 
void pause() {
    read_line("\n  Press Enter to continue...");
}
 
// ── MODULE 1: GREEDY TASK SCHEDULER ──────────────────
 
vector<int> greedy_schedule(vector<Task>& tasks) {
    int n = tasks.size();
    vector<int> indices(n);
    for (int i = 0; i < n; i++) indices[i] = i;
 
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return tasks[a].end < tasks[b].end;
    });
 
    vector<int> selected;
    int last_end = -1;
 
    for (int i : indices) {
        if (tasks[i].start >= last_end) {
            selected.push_back(i);
            last_end = tasks[i].end;
        }
    }
    return selected;
}
 
void display_schedule(vector<Task>& tasks, vector<int>& selected) {
    vector<bool> is_selected(tasks.size(), false);
    for (int i : selected) is_selected[i] = true;
 
    print_line('=');
    cout << "   GREEDY TASK SCHEDULER -- RESULTS\n";
    print_line('=');
 
    int total_hours = 0;
    cout << "\n  Scheduled (" << selected.size() << " tasks):\n\n";
    for (int i : selected) {
        int duration = tasks[i].end - tasks[i].start;
        total_hours += duration;
        cout << "    [SCHEDULED]  " << left << setw(20) << tasks[i].name
             << "  " << setw(2) << tasks[i].start << ":00 --> "
             << setw(2) << tasks[i].end << ":00"
             << "  (" << duration << "h)\n";
    }
    cout << "\n  Total productive hours: " << total_hours << "h\n";
 
    bool any_skipped = false;
    for (int i = 0; i < (int)tasks.size(); i++) {
        if (!is_selected[i]) { any_skipped = true; break; }
    }
 
    if (any_skipped) {
        cout << "\n  Skipped (overlap conflicts):\n\n";
        for (int i = 0; i < (int)tasks.size(); i++) {
            if (!is_selected[i]) {
                cout << "    [SKIPPED]    " << left << setw(20) << tasks[i].name
                     << "  " << setw(2) << tasks[i].start << ":00 --> "
                     << setw(2) << tasks[i].end << ":00\n";
            }
        }
    }
    print_line('=');
}
 
void run_task_scheduler() {
    vector<Task> tasks;
 
    print_line('=');
    cout << "   TASK SCHEDULER -- Enter Your Tasks\n";
    print_line('=');
 
    int n = read_int("\n  How many tasks do you want to schedule? ");
    cout << "\n  Use 24-hour format  (e.g. 9 = 9:00 AM,  14 = 2:00 PM)\n\n";
 
    for (int i = 0; i < n; i++) {
        Task t;
        cout << "  -- Task " << (i + 1) << " --\n";
        t.name  = read_line("  Name       : ");
        t.start = read_int ("  Start hour : ");
        t.end   = read_int ("  End hour   : ");
        cout << "\n";
 
        if (t.start >= t.end) {
            cout << "  [!] End time must be after start time. Task skipped.\n\n";
        } else {
            tasks.push_back(t);
        }
    }
 
    if (tasks.empty()) {
        cout << "\n  No valid tasks entered.\n";
        return;
    }
 
    vector<int> selected = greedy_schedule(tasks);
    display_schedule(tasks, selected);
}
 
// ── MODULE 2: DP RESOURCE ALLOCATOR ──────────────────
 
vector<int> knapsack_allocate(vector<Resource>& resources, int budget) {
    int n = resources.size();
    int W = budget;
 
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
 
    for (int i = 1; i <= n; i++) {
        int cost  = resources[i - 1].cost;
        int value = resources[i - 1].value;
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];
            if (cost <= w) {
                int take = dp[i - 1][w - cost] + value;
                if (take > dp[i][w])
                    dp[i][w] = take;
            }
        }
    }
 
    vector<int> selected;
    int w = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i - 1);
            w -= resources[i - 1].cost;
        }
    }
    return selected;
}
 
void display_allocation(vector<Resource>& resources, vector<int>& selected, int budget) {
    vector<bool> is_selected(resources.size(), false);
    for (int i : selected) is_selected[i] = true;
 
    int total_cost = 0, total_value = 0;
    for (int i : selected) {
        total_cost  += resources[i].cost;
        total_value += resources[i].value;
    }
 
    print_line('=');
    cout << "   DP RESOURCE ALLOCATOR -- RESULTS\n";
    print_line('=');
 
    cout << "\n  Budget: " << budget << " units\n";
    cout << "\n  Best combination (" << selected.size() << " resources):\n\n";
 
    for (int i : selected) {
        cout << "    [SELECTED]   " << left << setw(22) << resources[i].name
             << "  cost=" << setw(3) << resources[i].cost
             << "  value=" << resources[i].value << "\n";
    }
 
    cout << "\n  Budget used  : " << total_cost << " / " << budget << " units\n";
    cout << "  Total value  : " << total_value << "\n";
 
    bool any_skipped = false;
    for (int i = 0; i < (int)resources.size(); i++) {
        if (!is_selected[i]) { any_skipped = true; break; }
    }
 
    if (any_skipped) {
        cout << "\n  Not selected:\n\n";
        for (int i = 0; i < (int)resources.size(); i++) {
            if (!is_selected[i]) {
                cout << "    [SKIPPED]    " << left << setw(22) << resources[i].name
                     << "  cost=" << setw(3) << resources[i].cost
                     << "  value=" << resources[i].value << "\n";
            }
        }
    }
    print_line('=');
}
 
void run_resource_allocator() {
    vector<Resource> resources;
 
    print_line('=');
    cout << "   RESOURCE ALLOCATOR -- Enter Your Resources\n";
    print_line('=');
 
    int budget = read_int("\n  Total budget (units) : ");
    int n      = read_int("  Number of resources  : ");
 
    cout << "\n  Rate value 1-10 (how important/useful the resource is)\n\n";
 
    for (int i = 0; i < n; i++) {
        Resource r;
        cout << "  -- Resource " << (i + 1) << " --\n";
        r.name  = read_line("  Name  : ");
        r.cost  = read_int ("  Cost  : ");
        r.value = read_int ("  Value : ");
        cout << "\n";
 
        if (r.cost <= 0 || r.value <= 0) {
            cout << "  [!] Cost and value must be positive. Resource skipped.\n\n";
        } else {
            resources.push_back(r);
        }
    }
 
    if (resources.empty()) {
        cout << "\n  No valid resources entered.\n";
        return;
    }
 
    vector<int> selected = knapsack_allocate(resources, budget);
    display_allocation(resources, selected, budget);
}
 
// ── MAIN MENU ─────────────────────────────────────────
 
int main() {
    cout << "\n";
    cout << "  ****************************************************\n";
    cout << "  *                                                  *\n";
    cout << "  *       SMART SCHEDULER & RESOURCE ALLOCATOR       *\n";
    cout << "  *                                                  *\n";
    cout << "  *   [ Greedy Algorithm ]  [ 0/1 Knapsack DP ]     *\n";
    cout << "  *                                                  *\n";
    cout << "  ****************************************************\n";
 
    while (true) {
        cout << "\n  What do you want to do?\n";
        cout << "\n    1.  Schedule my tasks for the day  (Greedy Algorithm)";
        cout << "\n    2.  Allocate resources in budget   (DP - 0/1 Knapsack)";
        cout << "\n    3.  Exit\n";
 
        int choice = read_int("\n  Enter choice (1/2/3): ");
 
        if (choice == 1) {
            run_task_scheduler();
            pause();
        } else if (choice == 2) {
            run_resource_allocator();
            pause();
        } else if (choice == 3) {
            cout << "\n  Goodbye!\n\n";
            break;
        } else {
            cout << "\n  [!] Invalid choice. Enter 1, 2, or 3.\n";
        }
    }
 
    return 0;
}