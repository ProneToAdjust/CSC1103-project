#include <stdio.h>
#include <limits.h>
#include "minimax.h"

static char computer = 'N';
static char human = 'N';
int moveCount;

int *bestMoveByAI(char board[3][3], int playerNumber, int togglePrune)
{
    moveCount = 0;
    static int arrBestMove[2];
    int score = -1;
    int bestScore = INT_MIN;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    if (playerNumber == 1) // if computer is player 1 (goes first), computer is X and human is O
    {
        computer = 'X';
        human = 'O';
    }
    else if (playerNumber == 2) // vice versa (computer goes second)
    {
        computer = 'O';
        human = 'X';
    }

    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (board[i][k] == ' ') // check if spot is empty
            {
                board[i][k] = computer;                
                score = (togglePrune == 1) ? miniMax(0, 0, INT_MIN, INT_MAX, 1) : miniMax(0, 0, INT_MIN, INT_MAX, 0);
                board[i][k] = ' '; // undo the move
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMoveRow = i;
                    bestMoveCol = k;
                }
            }
        }
    }
    arrBestMove[0] = bestMoveRow;
    arrBestMove[1] = bestMoveCol;
    printf("Total moves made by Computer: %d\n", moveCount / 2);
    return arrBestMove;
}

int miniMax(int depth, int isMaximizing, int alpha, int beta, int togglePrune)
{
    moveCount += 1;
    char result = checkWin(board);

    int score;
    if (result != ' ')
    {
        if (result == 'X')
        {
            score = -10;
            score = score - depth;

            return score;
        }
        if (result == 'O')
        {
            score = 10;            // score is 10 since not more than 9 moves (depth) can be made.
            score = score - depth; // ensures that AI always picks the move that has lesser depth(lesser moves)

            return score;
        }
        if (result == 'T')
        {
            score = 0;
            return score;
        }
    }

    if (isMaximizing == 1)
    {
        int bestScore = INT_MIN;
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (board[i][k] == ' ')
                {
                    board[i][k] = computer; //'O' turn
                    // printBoard();
                    score = miniMax(depth + 1, 0, alpha, beta, togglePrune);
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
    else // if isMaximizing == 0
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (board[i][k] == ' ')
                {
                    board[i][k] = human; //'X' turn (HUMAN)
                    score = miniMax(depth + 1, 1, alpha, beta, togglePrune);
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

char checkWin(char currentBoard[3][3])  //not using pyrena's gameover() function because it would take too much refactoring and would further complicate the algorithm
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