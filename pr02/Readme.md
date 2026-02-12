# DFA Minimization in C

---

## **Overview**

A **Detinistic Finite Automaton (DFA)** is a finite state machine used in:

* Lexical analysis
* Pattern matching
* Regular expression implementation
* Compiler design

However, a DFA constructed from a regular expression or NFA may contain:

* **Unreachable states**
* **Equivalent (redundant) states**

Such a DFA is **not optimal**.

### **DFA Minimization** is the process of:

1. Removing **unreachable states**
2. Merging **equivalent states**
3. Producing a **minimal DFA**
4. Preserving the same language

A minimized DFA:

* Has the **minimum number of states**
* Is **unique** (up to renaming of states)
* Is more efficient for implementation

---

## **Algorithm Steps**

## **Part 1: Remove Unreachable States**

1. **Start**
2. Assume `q0` is start state
3. Mark all states as **not reachable**
4. Perform **DFS (Depth First Search)** from `q0`
5. Mark all visited states as reachable
6. Remove all unmarked states

### **Why Remove Unreachable States?**

Unreachable states:

* Can never be visited from start state
* Do not affect language
* Must be removed before minimization

## **Part 2: Table Filling Method**

This method identifies **distinguishable states**.

### **Step 1: Create Distinguishability Table**

* Create a table for all pairs of states (qi, qj)
* Initially mark all pairs as **unmarked**

### **Step 2: Mark Final vs Non-Final Pairs**

For every pair (qi, qj):

* If one is **final** and other is **non-final**
* Mark them as **distinguishable**

Reason:
Final and non-final states cannot be equivalent.

### **Step 3: Iterative Marking**

Repeat until no changes occur:

For each unmarked pair (qi, qj):

* For each input symbol `a`
* Find:

  * δ(qi, a) = p
  * δ(qj, a) = q
* If pair (p, q) is already marked
  → Mark (qi, qj)

Reason:
If transitions go to distinguishable states,
then original states are also distinguishable.

### **Step 4: Merge Equivalent States**

* All **unmarked pairs** are equivalent
* Merge them into single state

### **Step 5: Construct Minimized DFA**

1. Each group becomes one state
2. Update transitions
3. Mark final states appropriately

---

# Complete Algorithm Summary

1. Start
2. Read number of states, symbols
3. Read transition table
4. Read final states
5. Perform DFS to remove unreachable states
6. Create distinguishability table
7. Mark final vs non-final pairs
8. Iteratively mark distinguishable pairs
9. Merge unmarked pairs
10. Print minimized DFA
11. Stop

---

# How the Code Works

## Step 1: Input Transition Table

```c
scanf("%d", &transition[i][j]);
```

Stores:

[
\delta(q_i, a_j)
]

Which represents DFA transition function.

## Step 2: Remove Unreachable States (DFS)

```c
void dfs(int state)
```

* Marks state as reachable
* Recursively visits connected states

This ensures:

Only useful states remain.

## Step 3: Mark Final vs Non-Final

```c
if (final[i] != final[j])
    distinguish[i][j] = 1;
```

Theory:

Final and non-final states accept different languages,
so they cannot be equivalent.

## Step 4: Check Transitions

```c
int p = transition[i][k];
int q = transition[j][k];
```

If transitions lead to distinguishable states,
mark the pair.

This is based on:

### **Myhill–Nerode Theorem**

Two states are equivalent
if and only if
for every input string
they either both accept or both reject.

## Step 5: Merge Equivalent States

Using Union-Find:

```c
union_set(i, j);
```

Groups equivalent states into single representative.

---

## DFA Minimization Flowchart (Theory)

1. Start
2. Read DFA
3. Remove unreachable states
4. Mark final vs non-final pairs
5. For each unmarked pair

   * Compare transitions
   * Mark if needed
6. Repeat until stable
7. Merge unmarked pairs
8. Print minimized DFA
9. Stop

---

# Key Concepts

## 1. Reachable State

A state reachable from start state via some input string.

## 2. Equivalent States

Two states are equivalent if:

For every input string,
they either both accept or both reject.

## 3. Distinguishable States

Two states are distinguishable if:

There exists some input string
that leads one to accept
and the other to reject.

## 4. Minimal DFA

A DFA with:

* No unreachable states
* No equivalent states
* Minimum number of states
* Same language

---

# Time Complexity

* Reachability (DFS):
  O(n × m)

* Table filling:
  O(n² × m)

Overall complexity:

[
O(n^2 \cdot m)
]

Where:

* n = number of states
* m = number of input symbols

---

# Sample Input

```txt
Enter number of states: 8
Enter number of input symbols: 2

Enter transition table:
δ(q0, symbol0): 5
δ(q0, symbol1): 1
δ(q1, symbol0): 2
δ(q1, symbol1): 6
δ(q2, symbol0): 2
δ(q2, symbol1): 0
δ(q3, symbol0): 3
δ(q3, symbol1): 3
δ(q4, symbol0): 5
δ(q4, symbol1): 7
δ(q5, symbol0): 6
δ(q5, symbol1): 2
δ(q6, symbol0): 4
δ(q6, symbol1): 6
δ(q7, symbol0): 2
δ(q7, symbol1): 6

Enter final states (1 for final, 0 for non-final):
Is q0 final? 0
Is q1 final? 0
Is q2 final? 1
Is q3 final? 0
Is q4 final? 0
Is q5 final? 0
Is q6 final? 0
Is q7 final? 0
```

---

# Sample Output (Minimized DFA)

```txt

Reachable States:
q0 q1 q2 q4 q5 q6 q7 

Minimized DFA:

State Group { q0 q4 }
Transitions:
  On symbol0 -> Group with representative q5
  On symbol1 -> Group with representative q1
Final State: No

State Group { q1 q7 }
Transitions:
  On symbol0 -> Group with representative q2
  On symbol1 -> Group with representative q6
Final State: No

State Group { q2 }
Transitions:
  On symbol0 -> Group with representative q2
  On symbol1 -> Group with representative q0
Final State: Yes

State Group { q5 }
Transitions:
  On symbol0 -> Group with representative q6
  On symbol1 -> Group with representative q2
Final State: No

State Group { q6 }
Transitions:
  On symbol0 -> Group with representative q0
  On symbol1 -> Group with representative q6
Final State: No
```
