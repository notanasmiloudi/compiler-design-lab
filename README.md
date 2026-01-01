# Epsilon-NFA Elimination Program

## Overview

This program eliminates ε (epsilon) transitions from a Non-Deterministic Finite Automaton (NFA), producing an equivalent NFA without epsilon transitions. This is an essential step before determinization of NFAs.

## What are Epsilon Transitions?

Epsilon transitions are transitions in an NFA that do not consume any input symbol. They allow the automaton to change states "for free" without reading input. While useful for constructing NFAs from regular expressions, they complicate processing and must be removed for many algorithms.

## Algorithm

The program implements the standard epsilon-elimination algorithm:

1. **Compute ε-closure**: For each state, find all states reachable via epsilon transitions
2. **Build new transitions**: δ'(q, a) = ε-closure(δ(ε-closure(q), a))
3. **Determine final states**: A state is final if its ε-closure contains an original final state

## Features

- Interactive command-line interface
- Support for multiple input symbols
- Handles arbitrary number of states (up to 20)
- Clear visualization of epsilon closures
- Complete transition table display
- Identifies new final states after elimination

## Compilation
```bash
gcc epsilon_nfa_elimination.c -o epsilon_nfa
```

## Execution
```bash
./epsilon_nfa
```

## Input Format

The program will prompt you for the following information:

1. **Number of states**: Total states in the NFA (states numbered from 0)
2. **Number of symbols**: Input alphabet size (excluding epsilon)
3. **Symbols**: The input alphabet (e.g., a, b, c)
4. **Transitions**: Enter transitions one by one
   - From state: source state number
   - On symbol: input symbol or 'e' for epsilon
   - To state: destination state number
   - Enter -1 when done
5. **Initial state**: The starting state
6. **Final states**: Number and list of accepting states

**Note:** This program is part of a lab assignment for understanding automata theory concepts. It demonstrates the practical implementation of epsilon-NFA elimination algorithms.
