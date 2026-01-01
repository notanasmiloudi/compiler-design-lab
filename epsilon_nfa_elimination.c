#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10




// Created by Anas Miloudi G2 Networks



// Structure to represent an NFA
typedef struct {
    int numStates;           // Number of states
    int numSymbols;          // Number of symbols (without epsilon)
    char symbols[MAX_SYMBOLS]; // Input symbols
    int transitions[MAX_STATES][MAX_SYMBOLS+1][MAX_STATES]; // Transition table (last column for epsilon)
    int initialState;        // Initial state
    int finalStates[MAX_STATES]; // Final states (1 = final, 0 = not final)
    int epsilonClosure[MAX_STATES][MAX_STATES]; // Epsilon-closure for each state
} NFA;

// Task 1: Read the NFA from user input
void readNFA(NFA *nfa) {
    printf("=== Task 1: Reading the NFA ===\n");
    
    // Read number of states
    printf("Enter number of states: ");
    scanf("%d", &nfa->numStates);
    
    // Read number of input symbols (without epsilon)
    printf("Enter number of input symbols (without epsilon): ");
    scanf("%d", &nfa->numSymbols);
    
    // Read the symbols
    printf("Enter the symbols (e.g., a b c): ");
    for(int i = 0; i < nfa->numSymbols; i++) {
        scanf(" %c", &nfa->symbols[i]);
    }
    
    // Initialize transition table
    for(int i = 0; i < MAX_STATES; i++) {
        for(int j = 0; j < MAX_SYMBOLS+1; j++) {
            for(int k = 0; k < MAX_STATES; k++) {
                nfa->transitions[i][j][k] = 0;
            }
        }
    }
    
    // Read transitions
    printf("\nEnter transitions (state, symbol, next_state). Enter -1 to stop.\n");
    printf("Use 'e' for epsilon transitions.\n");
    int state, nextState;
    char symbol;
    
    while(1) {
        printf("From state: ");
        scanf("%d", &state);
        if(state == -1) break;
        
        printf("On symbol: ");
        scanf(" %c", &symbol);
        
        printf("To state: ");
        scanf("%d", &nextState);
        
        // Determine the symbol index in the table
        int symbolIndex;
        if(symbol == 'e') {
            symbolIndex = nfa->numSymbols; // Epsilon in the last column
        } else {
            symbolIndex = -1;
            for(int i = 0; i < nfa->numSymbols; i++) {
                if(nfa->symbols[i] == symbol) {
                    symbolIndex = i;
                    break;
                }
            }
            if(symbolIndex == -1) {
                printf("Invalid symbol!\n");
                continue;
            }
        }
        
        nfa->transitions[state][symbolIndex][nextState] = 1;
    }
    
    // Read initial state
    printf("Enter initial state: ");
    scanf("%d", &nfa->initialState);
    
    // Read final states
    printf("Enter number of final states: ");
    int numFinal;
    scanf("%d", &numFinal);
    
    for(int i = 0; i < MAX_STATES; i++) {
        nfa->finalStates[i] = 0;
    }
    
    printf("Enter final states: ");
    for(int i = 0; i < numFinal; i++) {
        int finalState;
        scanf("%d", &finalState);
        nfa->finalStates[finalState] = 1;
    }
    
    printf("\nNFA read successfully!\n\n");
}

Mohammed Mrd, [12/31/2025 9:26 PM]
// Task 2: Calculate epsilon-closure for each state
void calculateEpsilonClosure(NFA *nfa) {
    printf("=== Task 2: Calculating Epsilon-Closure ===\n");
    
    // Initialize epsilon-closure
    for(int i = 0; i < nfa->numStates; i++) {
        for(int j = 0; j < nfa->numStates; j++) {
            nfa->epsilonClosure[i][j] = 0;
        }
        nfa->epsilonClosure[i][i] = 1; // Each state is in its own epsilon-closure
    }
    
    // Calculate epsilon-closure using reachability algorithm
    for(int state = 0; state < nfa->numStates; state++) {
        int changed = 1;
        while(changed) {
            changed = 0;
            for(int i = 0; i < nfa->numStates; i++) {
                if(nfa->epsilonClosure[state][i]) {
                    // Add all states reachable from i via epsilon
                    for(int j = 0; j < nfa->numStates; j++) {
                        if(nfa->transitions[i][nfa->numSymbols][j] && !nfa->epsilonClosure[state][j]) {
                            nfa->epsilonClosure[state][j] = 1;
                            changed = 1;
                        }
                    }
                }
            }
        }
    }
    
    // Display epsilon-closure for each state
    for(int i = 0; i < nfa->numStates; i++) {
        printf("ε-closure(%d) = { ", i);
        for(int j = 0; j < nfa->numStates; j++) {
            if(nfa->epsilonClosure[i][j]) {
                printf("%d ", j);
            }
        }
        printf("}\n");
    }
    printf("\n");
}

// Task 3: Compute new transitions without epsilon
void computeNewTransitions(NFA *nfa, int newTransitions[MAX_STATES][MAX_SYMBOLS][MAX_STATES]) {
    printf("=== Task 3: Computing New Transitions (without epsilon) ===\n");
    
    // Initialize new transitions
    for(int i = 0; i < MAX_STATES; i++) {
        for(int j = 0; j < MAX_SYMBOLS; j++) {
            for(int k = 0; k < MAX_STATES; k++) {
                newTransitions[i][j][k] = 0;
            }
        }
    }
    
    // For each state and each symbol
    for(int state = 0; state < nfa->numStates; state++) {
        for(int symbol = 0; symbol < nfa->numSymbols; symbol++) {
            // For each state in epsilon-closure of current state
            for(int epsState = 0; epsState < nfa->numStates; epsState++) {
                if(nfa->epsilonClosure[state][epsState]) {
                    // If there's a transition from epsState on symbol
                    for(int nextState = 0; nextState < nfa->numStates; nextState++) {
                        if(nfa->transitions[epsState][symbol][nextState]) {
                            // Add epsilon-closure of nextState to new transitions
                            for(int finalState = 0; finalState < nfa->numStates; finalState++) {
                                if(nfa->epsilonClosure[nextState][finalState]) {
                                    newTransitions[state][symbol][finalState] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    printf("New transitions computed successfully!\n\n");
}

// Task 4: Determine new final states
void determineNewFinalStates(NFA *nfa, int newFinalStates[MAX_STATES]) {
    printf("=== Task 4: Determining New Final States ===\n");
    
    // A state is final if its epsilon-closure contains an original final state
    for(int i = 0; i < nfa->numStates; i++) {
        newFinalStates[i] = 0;
        for(int j = 0; j < nfa->numStates; j++) {
            if(nfa->epsilonClosure[i][j] && nfa->finalStates[j]) {
                newFinalStates[i] = 1;
                break;
            }
        }
    }
    
    printf("New final states: { ");
    for(int i = 0; i < nfa->numStates; i++) {
        if(newFinalStates[i]) {
            printf("%d ", i);
        }
    }
    printf("}\n\n");
}

Mohammed Mrd, [12/31/2025 9:26 PM]
// Task 5: Display the new automaton
void displayNewAutomaton(NFA *nfa, int newTransitions[MAX_STATES][MAX_SYMBOLS][MAX_STATES], int newFinalStates[MAX_STATES]) {
    printf("=== Task 5: Displaying New Automaton (without epsilon) ===\n");
    printf("\n");
    
    printf("Number of states: %d\n", nfa->numStates);
    printf("Initial state: %d\n", nfa->initialState);
    
    printf("Final states: { ");
    for(int i = 0; i < nfa->numStates; i++) {
        if(newFinalStates[i]) {
            printf("%d ", i);
        }
    }
    printf("}\n\n");
    
    printf("Transitions:\n");
    for(int state = 0; state < nfa->numStates; state++) {
        for(int symbol = 0; symbol < nfa->numSymbols; symbol++) {
            printf("δ(%d, %c) = { ", state, nfa->symbols[symbol]);
            int hasTransition = 0;
            for(int nextState = 0; nextState < nfa->numStates; nextState++) {
                if(newTransitions[state][symbol][nextState]) {
                    printf("%d ", nextState);
                    hasTransition = 1;
                }
            }
            if(!hasTransition) {
                printf("∅");
            }
            printf(" }\n");
        }
    }
}

int main() {
    NFA nfa;
    int newTransitions[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
    int newFinalStates[MAX_STATES];
    
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║  Epsilon-NFA Elimination Program              ║\n");
    printf("║  Removes ε-transitions from an NFA            ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    // Task 1: Read the NFA
    readNFA(&nfa);
    
    // Task 2: Calculate epsilon-closure
    calculateEpsilonClosure(&nfa);
    
    // Task 3: Compute new transitions
    computeNewTransitions(&nfa, newTransitions);
    
    // Task 4: Determine new final states
    determineNewFinalStates(&nfa, newFinalStates);
    
    // Task 5: Display the new automaton
    displayNewAutomaton(&nfa, newTransitions, newFinalStates);
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║  Program completed successfully!              ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    return 0;

}