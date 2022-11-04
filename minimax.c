#include <stdio.h>
#include <limits.h>
#include "minimax.h"

static char computer = 'N';
static char human = 'N';

int *bestMoveByAI(char board[3][3], int playerNumber)
{
    static int arrBestMove[2];
    int bestScore = INT_MIN;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    if (playerNumber == 1) // if computer is player 1 (goes first), computer is X and human is O
    {
        computer = 'X';
        human = 'O';
    }
    if (playerNumber == 2) // vice versa (computer goes second)
    {
        computer = 'O';
        human = 'X';
    }

    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (board[i][k] == ' ')
            { // check if spot is empty
                board[i][k] = computer;
                // printBoard();
                int score = miniMax(0, 0, INT_MIN, INT_MAX);
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
    return arrBestMove;
}

int miniMax(int depth, int isMaximizing, int alpha, int beta)
{
    char result = checkWin(board);
    int score;
    if (result != ' ')
    {
        if (result == 'X')
        {
            score = -1;
            return score;
        }
        if (result == 'O')
        {
            score = 1;
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
                    score = miniMax(depth + 1, 0, alpha, beta);
                    board[i][k] = ' ';     // undo move
                    if (score > bestScore) // equi to bestScore = max(score, bestScore);
                    {
                        bestScore = score;
                    }
                    
                    //alpha-beta pruning
                    if (alpha > bestScore)
                    {
                        alpha = alpha;
                    }
                    if (alpha < bestScore)
                    {
                        alpha = bestScore;
                    }
                    if (beta <= alpha)
                    {
                        return bestScore;
                    }
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (board[i][k] == ' ')
                {
                    board[i][k] = human; //'X' turn (HUMAN)
                    score = miniMax(depth + 1, 1, alpha, beta);
                    board[i][k] = ' ';     // undo move
                    if (score < bestScore) // equi to bestScore = min(score, bestScore);
                    {
                        bestScore = score;
                    }

                    //alpha-beta pruning
                    if (beta < bestScore)
                    {
                        beta = beta;
                    }
                    if (beta > bestScore)
                    {
                        beta = bestScore;
                    }
                    if (beta <= alpha)
                    {
                        return bestScore;
                    }
                }
            }
        }
        return bestScore;
    }
}