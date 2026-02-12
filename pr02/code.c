#include <stdio.h>
#include <string.h>

#define MAX 20

int n, m;
int transition[MAX][MAX];
int final[MAX];
int reachable[MAX];
int distinguish[MAX][MAX];
int parent[MAX];

// DFS to mark reachable states
void dfs(int state) {
    reachable[state] = 1;
    for (int i = 0; i < m; i++) {
        int next = transition[state][i];
        if (!reachable[next])
            dfs(next);
    }
}

// Find representative
int find(int x) {
    while (parent[x] != x)
        x = parent[x];
    return x;
}

// Union sets
void union_set(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py)
        parent[py] = px;
}

int main() {
    int i, j, k;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("\nEnter transition table:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("δ(q%d, symbol%d): ", i, j);
            scanf("%d", &transition[i][j]);
        }
    }

    printf("\nEnter final states (1 for final, 0 for non-final):\n");
    for (i = 0; i < n; i++) {
        printf("Is q%d final? ", i);
        scanf("%d", &final[i]);
    }

    // STEP 1: Remove unreachable states
    for (i = 0; i < n; i++)
        reachable[i] = 0;

    dfs(0);  // assuming q0 is start state

    printf("\nReachable States:\n");
    for (i = 0; i < n; i++)
        if (reachable[i])
            printf("q%d ", i);
    printf("\n");

    // STEP 2: Initialize distinguish table
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            distinguish[i][j] = 0;

    // Mark pairs (final vs non-final) only if both reachable
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (reachable[i] && reachable[j] && final[i] != final[j]) {
                distinguish[i][j] = distinguish[j][i] = 1;
            }
        }
    }

    // STEP 3: Iterative marking
    int changed = 1;
    while (changed) {
        changed = 0;
        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                if (reachable[i] && reachable[j] && !distinguish[i][j]) {
                    for (k = 0; k < m; k++) {
                        int p = transition[i][k];
                        int q = transition[j][k];
                        if (distinguish[p][q] || distinguish[q][p]) {
                            distinguish[i][j] = distinguish[j][i] = 1;
                            changed = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    // STEP 4: Initialize parent array
    for (i = 0; i < n; i++)
        parent[i] = i;

    // Merge equivalent reachable states
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (reachable[i] && reachable[j] && !distinguish[i][j]) {
                union_set(i, j);
            }
        }
    }

    // STEP 5: Print Minimized DFA
    printf("\nMinimized DFA:\n");

    int printed[MAX] = {0};

    for (i = 0; i < n; i++) {
        if (reachable[i]) {
            int rep = find(i);
            if (!printed[rep]) {
                printed[rep] = 1;

                printf("\nState Group { ");
                for (j = 0; j < n; j++) {
                    if (reachable[j] && find(j) == rep)
                        printf("q%d ", j);
                }
                printf("}\n");

                printf("Transitions:\n");
                for (k = 0; k < m; k++) {
                    int next = transition[rep][k];
                    printf("  On symbol%d -> Group with representative q%d\n",
                           k, find(next));
                }

                // Check if final
                int isFinal = 0;
                for (j = 0; j < n; j++) {
                    if (reachable[j] && find(j) == rep && final[j]) {
                        isFinal = 1;
                        break;
                    }
                }

                printf("Final State: %s\n", isFinal ? "Yes" : "No");
            }
        }
    }

    return 0;
}

