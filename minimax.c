#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

#include "minimax.h"

static char computer = 'N';
static char human = 'N';
int moveCount; // variable to count number of loops

struct timespec start, end;

int *bestMoveByAI(char board[3][3], int togglePrune)
{
    clock_gettime(CLOCK_MONOTONIC, &start); // start clock function to record time taken to run algorithm
    moveCount = 0;                          // reset counter to 0 before starting
    static int arrBestMove[2];
    int score = -1;
    int bestScore = INT_MIN;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    computer = 'O';
    human = 'X';

    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (board[i][k] == ' ') // check if spot is empty
            {
                board[i][k] = computer; // simulate the move
                score = (togglePrune == 1) ? miniMax(0, 0, INT_MIN, INT_MAX, 1) : miniMax(0, 0, INT_MIN, INT_MAX, 0);   //calls minimax function
                board[i][k] = ' '; // undo the move
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMoveRow = i;        //sets current loop's position as the x axis for best move
                    bestMoveCol = k;        //sets current loop's position as the y axis for best move
                }
            }
        }
    }
    arrBestMove[0] = bestMoveRow;       //sets best move into array
    arrBestMove[1] = bestMoveCol;
    printf("Total moves made by Computer: %d\n", moveCount / 2);        //calculation of number of moves simulated by minimax
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;       //calculation of time taken
    printf("Time taken to run the algorithm is: %lf", time_taken);
    return arrBestMove;
}

int miniMax(int depth, int isMaximizing, int alpha, int beta, int togglePrune)
{
    moveCount += 1;
    char result = checkWin(board);      //check if game has ended. if no, continue recursive
    int score;
    if (result != ' ')      //if game has ended, stop the recursive function, return the score
    {
        if (result == 'X')      //player(human) is X, minimizer
        {
            score = -10;
            score = score - depth;

            return score;
        }
        if (result == 'O')      //AI(computer) is O, maximizer
        {
            score = 10;            // score is 10 since not more than 9 moves (depth) can be made.
            score = score - depth; // ensures that AI always picks the move that has lesser depth(lesser moves)

            return score;
        }
        if (result == 'T')      //If game is a tie
        {
            score = 0;
            return score;
        }
    }

    if (isMaximizing == 1)      //AI(computer) is the maximizer
    {
        int bestScore = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (board[i][k] == ' ')
                {
                    board[i][k] = computer; //'O' turn
                    score = miniMax(depth + 1, 0, alpha, beta, togglePrune);    //calls minimax recursively, but isMaximizing is set to 0 here, since next turn is Human's
                    board[i][k] = ' '; // undo move
                    if (togglePrune == 1)
                    {
                        if (score > bestScore) // equi to bestScore = max(score, bestScore);
                        {
                            bestScore = score;
                        }
                        // alpha-beta pruning
                        if (alpha < bestScore)
                        {
                            alpha = bestScore;
                        }
                        if (beta <= alpha)
                        {
                            goto jump1; // to break out of nested loop, i know that it is not recommended to use goto, but i feel that in this scenario it'll simplify the code
                        }
                    }
                    else
                    {
                        if (score > bestScore) // equi to bestScore = max(score, bestScore);
                        {
                            bestScore = score;
                        }
                    }
                }
            }
        }
    jump1:
        return bestScore;
    }
    else // if isMaximizing == 0 player(human) is the minimizer
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (board[i][k] == ' ')
                {
                    board[i][k] = human; //'X' turn (HUMAN)
                    score = miniMax(depth + 1, 1, alpha, beta, togglePrune);    //calls minimax recursively, but isMaximizing is set to 1 here, since next turn is Computer's
                    board[i][k] = ' '; // undo move
                    if (togglePrune == 1)
                    {
                        if (score < bestScore) // equi to bestScore = min(score, bestScore);
                        {
                            bestScore = score;
                        }
                        // alpha-beta pruning
                        if (beta > bestScore)
                        {
                            beta = bestScore;
                        }
                        if (beta <= alpha)
                        {
                            goto jump2; // to break out of nested loop, i know that it is not recommended to use goto, but i feel that in this scenario it'll simplify the code
                        }
                    }
                    else
                    {
                        if (score < bestScore) // equi to bestScore = min(score, bestScore);
                        {
                            bestScore = score;
                        }
                    }
                }
            }
        }
    jump2:
        return bestScore;
    }
}

char checkWin(char currentBoard[3][3]) // not using pyrena's gameover() function because it would take too much refactoring and would further complicate the algorithm, both functions differ by returning different data types
{
    // loops through to check all rows
    for (int i = 0; i < 3; i++)
    {
        if (currentBoard[i][0] == currentBoard[i][1] && currentBoard[i][0] == currentBoard[i][2])
        {
            if (currentBoard[i][0] == 'X' || currentBoard[i][0] == 'O')
            {
                return currentBoard[i][0];
            }
        }
    }

    // loops through to check all columns
    for (int j = 0; j < 3; j++)
    {
        if (currentBoard[0][j] == currentBoard[1][j] && currentBoard[0][j] == currentBoard[2][j])
        {
            if (currentBoard[0][j] == 'X' || currentBoard[0][j] == 'O')
            {
                return currentBoard[0][j];
            }
        }
    }

    // check diagonal, top left to bottom right
    if (currentBoard[0][0] == currentBoard[1][1] && currentBoard[0][0] == currentBoard[2][2])
    {
        if (currentBoard[0][0] == 'X' || currentBoard[0][0] == 'O')
        {
            return currentBoard[0][0];
        }
    }

    // check diagonal, top right to bottom left
    if (currentBoard[0][2] == currentBoard[1][1] && currentBoard[0][2] == currentBoard[2][0])
    {
        if (currentBoard[0][2] == 'X' || currentBoard[0][2] == 'O')
        {
            return currentBoard[0][2];
        }
    }

    // checks for tie
    if (checkEmptyCells() == 0)
    {
        return 'T'; // if tie, return 'T'
    }
    return ' ';
}