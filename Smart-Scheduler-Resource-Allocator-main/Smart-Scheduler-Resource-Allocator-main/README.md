# Smart Scheduler & Resource Allocator

A C++ terminal application that solves two real-world problems using classic algorithms:

- **Task Scheduling** → Greedy Algorithm (Activity Selection Problem)
- **Resource Allocation** → Dynamic Programming (0/1 Knapsack Problem)

---

## Algorithms Used

### 1. Greedy Algorithm — Task Scheduling

Schedules the **maximum number of non-overlapping tasks** in a day.

**How it works:**
1. Sort all tasks by their **end time**
2. Pick the task that finishes earliest
3. Skip any task that overlaps with the last selected task
4. Repeat until all tasks are processed

**Time Complexity:** O(n log n)  
**Space Complexity:** O(n)

**Example:**

| Task | Start | End | Result |
|------|-------|-----|--------|
| Team meeting | 9:00 | 10:00 | ✅ Scheduled |
| Code review | 9:00 | 11:00 | ❌ Skipped (overlaps) |
| Design sync | 10:00 | 12:00 | ✅ Scheduled |
| Client call | 12:00 | 13:00 | ✅ Scheduled |

---

### 2. Dynamic Programming — Resource Allocation (0/1 Knapsack)

Selects the **best combination of resources** that fits within a budget and maximizes total value.

**How it works:**
1. Build a 2D DP table of size `(n+1) x (budget+1)`
2. For each resource, decide: skip it or take it (whichever gives more value)
3. Backtrack through the table to find which resources were selected

**Recurrence:**
```
dp[i][w] = max(
    dp[i-1][w],                        // skip resource i
    dp[i-1][w - cost[i]] + value[i]    // take resource i
)
```

**Time Complexity:** O(n × W)  
**Space Complexity:** O(n × W)

---

## How to Run

### Requirements
- A C++ compiler (g++ recommended)
- Works on Windows, Linux, and macOS

### Compile

```bash
g++ smart_scheduler.cpp -o scheduler
```

### Run

**Linux / macOS:**
```bash
./scheduler
```

**Windows:**
```bash
scheduler.exe
```

---

## Sample Output

```
  ****************************************************
  *                                                  *
  *       SMART SCHEDULER & RESOURCE ALLOCATOR       *
  *                                                  *
  *   [ Greedy Algorithm ]  [ 0/1 Knapsack DP ]     *
  *                                                  *
  ****************************************************

  What do you want to do?

    1.  Schedule my tasks for the day  (Greedy Algorithm)
    2.  Allocate resources in budget   (DP - 0/1 Knapsack)
    3.  Exit

  Enter choice (1/2/3): 1

  -- Task 1 --
  Name       : Morning gym
  Start hour : 6
  End hour   : 7

  ==================================================
     GREEDY TASK SCHEDULER -- RESULTS
  ==================================================

  Scheduled (3 tasks):

    [SCHEDULED]  Morning gym          6:00 -->  7:00  (1h)
    [SCHEDULED]  College class        9:00 --> 11:00  (2h)
    [SCHEDULED]  Lunch               12:00 --> 13:00  (1h)

  Total productive hours: 4h
  ==================================================
```

---

## Project Structure

```
├── smart_scheduler.cpp    # Main source file (all code in one file)
└── README.md              # This file
```

---

## Features

- Fully **interactive terminal** — enter your own tasks and resources at runtime
- **Input validation** — rejects invalid times and negative values
- **Loop menu** — run scheduling and allocation multiple times without restarting
- **No external libraries** — pure standard C++

---

## Use Cases

| Feature | Real-world Application |
|---|---|
| Task Scheduler | Planning your daily study/work schedule |
| Resource Allocator | Deciding which items to buy within a budget |

---

## Team

| Name | Role |
|------|------|
| (Your Name) | Developer |

---

*Project submitted to CCC — uses Greedy and Dynamic Programming algorithms.*
