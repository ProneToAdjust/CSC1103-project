# CSC1103-project
> A tic tac toe console application written in C

## Features
### 2 player mode
User takes turns to make their move on the board
### 1 player mode
Play against 4 difficulties:
1) Level 1: Makes a random move
2) Level 2: Uses a Naive Bayes classifier to decide its move
3) Level 3: Makes a move at random or uses the minimax algorithm
4) Level 4: Uses a minimax algorithm 

## Building
To access functional Tic Tac Toe program in terminal:
```
gcc -o tictactoe_main tictactoe_main.c minimax.c naive_bayes_ai.c
.\tictactoe_main
```
Alternatively, just run tictactoe_main.exe
