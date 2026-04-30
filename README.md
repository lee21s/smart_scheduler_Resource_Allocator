Smart Scheduler & Resource Allocator

A C++ terminal application that solves two real-world optimization problems using classic algorithms — built for clarity, correctness, and hands-on learning.

 What It Does
FeatureAlgorithmProblem SolvedTask SchedulerGreedy (Activity Selection)Schedule the maximum number of non-overlapping tasks in a dayResource AllocatorDynamic Programming (0/1 Knapsack)Pick the best combination of resources within a budget

 Algorithms
1. Greedy Algorithm — Task Scheduling
Selects the maximum number of non-overlapping tasks from a list of daily activities.
How it works:

Sort all tasks by their end time
Pick the task that finishes earliest
Skip any task that overlaps with the last selected task
Repeat until all tasks are processed

Time Complexity:  O(n log n)
Space Complexity: O(n)
Example:
TaskStartEndResultTeam meeting9:0010:00✅ ScheduledCode review9:0011:00❌ Skipped (overlaps)Design sync10:0012:00✅ ScheduledClient call12:0013:00✅ Scheduled

2. Dynamic Programming — Resource Allocation (0/1 Knapsack)
Selects the best combination of resources that fits within a given budget and maximizes total value.
How it works:

Build a 2D DP table of size (n+1) × (budget+1)
For each resource, decide: skip it or take it — whichever gives more value
Backtrack through the table to find which resources were selected

Recurrence relation:
dp[i][w] = max(
    dp[i-1][w],                        // skip resource i
    dp[i-1][w - cost[i]] + value[i]    // take resource i
)
Time Complexity:  O(n × W)
Space Complexity: O(n × W)

 How to Run
Requirements

A C++ compiler (g++ recommended)
Works on Windows, Linux, and macOS

Compile
bashg++ smart_scheduler.cpp -o scheduler
Run
bash# Linux / macOS
./scheduler

# Windows
scheduler.exe

Sample Output
*************************************************
*                                               *
*    SMART SCHEDULER & RESOURCE ALLOCATOR       *
*                                               *
*  [ Greedy Algorithm ]  [ 0/1 Knapsack DP ]   *
*                                               *
*************************************************

What do you want to do?
  1. Schedule my tasks for the day  (Greedy Algorithm)
  2. Allocate resources in budget   (DP - 0/1 Knapsack)
  3. Exit

Enter choice (1/2/3): 1

-- Task 1 --
Name       : Morning gym
Start hour : 6
End hour   : 7

==================================================
GREEDY TASK SCHEDULER -- RESULTS
==================================================
Scheduled (3 tasks):

[SCHEDULED]  Morning gym      6:00 -->  7:00  (1h)
[SCHEDULED]  College class    9:00 --> 11:00  (2h)
[SCHEDULED]  Lunch           12:00 --> 13:00  (1h)

# Total productive hours: 4h

[] Project Structure
├── smart_scheduler.cpp    # Main source file (all code in one file)
└── README.md              # Documentation

 Features

 Fully interactive terminal — enter your own tasks and resources at runtime
 Input validation — rejects invalid times and negative values
 Loop menu — run scheduling and allocation multiple times without restarting
 No external libraries — pure standard C++


Real-World Use Cases
FeatureReal-World ApplicationTask SchedulerPlanning your daily study or work scheduleResource AllocatorDeciding which items to buy within a budget

 Team
Name                   Role
Leethesh             Developer
Aditya               Developer
Vishnu               Developer
Ratna                Developer

 Submission
This project was submitted to CCC as part of a coursework assignment, demonstrating practical applications of Greedy and Dynamic Programming algorithms.
