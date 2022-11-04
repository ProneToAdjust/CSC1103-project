#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "minimax.h"

const char PLAYER1 = 'X';
const char PLAYER2 = 'O';
const char COMPUTER = 'O';
int arrBestMove[2];
int currentTurn = 0;
int currentPlayer = 0;
char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}};

// int scoresArr[3] = {1, -1, 0};     //X: 1, O:-1, Tie: 0

void computerMove(); // insert AI/algorithm, takes in move/position in board as parameter

void printBoard();
void resetGame();
void playerMove(char player);
char checkWin();
void printWinner(char player);
int isBoardFull();
void choosePlayer();
int turnTracker(char player);
void playerTracker(int player); // track current turn is whose, can think of merging with turnTracker()

//int miniMax(int depth, int isMaximizing);
//void bestMove();


int main()
{
    char winner = ' ';

    resetGame();
    choosePlayer();

    while (winner == ' ' && isBoardFull() != 0)
    {
        printBoard();
        playerMove(currentPlayer);
        winner = checkWin(board);
        if (winner != ' ' || isBoardFull() == 0)
        {
            break;
        }
        printBoard();
        playerTracker(currentPlayer);
        // playerMove(currentPlayer);

        int *arrBestMove;
        arrBestMove = bestMoveByAI(board, 2);
        board[arrBestMove[0]][arrBestMove[1]] = 'O';

        winner = checkWin(board);
        if (winner != ' ' || isBoardFull() == 0)
        {
            break;
        }
        playerTracker(currentPlayer);
    }

    printBoard();
    printWinner(winner);

    return 0;
}

void printBoard()
{
    printf("| %c | %c | %c | \n", board[0][0], board[0][1], board[0][2]);
    printf("| %c | %c | %c | \n", board[1][0], board[1][1], board[1][2]);
    printf("| %c | %c | %c | \n", board[2][0], board[2][1], board[2][2]);
    printf("_____________\n");
}

void resetGame()
{
    currentPlayer = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (board[i][k] != ' ')
            {
                board[i][k] = ' ';
            }
        }
    }
}

void playerMove(char player)
{
    char move = ' ';
    if (player == 1)
    {
        move = PLAYER1;
    }
    else if (player == 2)
    {
        move = PLAYER2;
    }
    int box, x, y;

    do
    {
        printf("Player % d, Please enter move: \n", currentPlayer);
        printf("Enter row: \n ");
        scanf("%d", &x);
        printf("Enter column: \n ");
        scanf("%d", &y);

        if (board[x][y] != ' ')
        {
            printf("Please make another move, current box is occupied.");
        }
        else
        {
            board[x][y] = move;
            break;
        }
    }

    while (board[x][y] != ' '); // continue looping to ask user for move if move is invalid
}

char checkWin(char currentBoard[3][3])
{
    char winner = 'S';
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
    if (isBoardFull() == 0)
    {
        return 'T'; // if tie, return 'T'
    }
    return ' ';
}

void printWinner(char player)
{
    switch (player)
    {
    case 'X':
        printf("The winner is %c! \n", player);
        break;

    case 'O':
        printf("The winner is %c! \n", player);
        break;

    case 'T':
        printf("This is a TIE! \n");
        break;
    }
}

int isBoardFull()
{
    int emptySquares = 9;
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (board[i][k] != ' ')
            {
                emptySquares -= 1;
            }
        }
    }
    return emptySquares;
}

void choosePlayer()
{
    do
    {
        printf("Play as Player 1 or 2? ");
        scanf("%d", &currentPlayer);

        if (currentPlayer == 1)
        {
            break;
        }
        else if (currentPlayer == 2)
        {
            break;
        }
        else
        {
            printf("\n Please only input 1 or 2 \n");
        }
    } while (!(currentPlayer == 1 || currentPlayer == 2));
}

int turnTracker(char player)
{ // can pass in current player as para

    if (player == 1)
    {
        // print current turn is whose
    }
    if (player == 2)
    {
    }
    static int turn = 9;
    turn -= 1;
    return turn;
}

void playerTracker(int player)
{
    if (player == 1)
    {
        currentPlayer = 2;
    }
    if (player == 2)
    {
        currentPlayer = 1;
    }
}

/*
void bestMove()
{
    int bestScore = -99;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (board[i][k] == ' ')
            { // check if spot is empty
                board[i][k] = COMPUTER;
                //printBoard();
                int score = miniMax(0, 0);
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
    board[bestMoveRow][bestMoveCol] = COMPUTER;
}



int miniMax(int depth, int isMaximizing)
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
        int bestScore = -99;
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (board[i][k] == ' ')
                {
                    board[i][k] = COMPUTER; //'O' turn
                    //printBoard();
                    score = miniMax(depth + 1, 0);
                    board[i][k] = ' '; // undo move
                    if (score > bestScore)
                    {
                        bestScore = score;
                    }
                    // bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 99;
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (board[i][k] == ' ')
                {
                    board[i][k] = PLAYER1; //'X' turn (HUMAN)
                    score = miniMax(depth + 1, 1);
                    board[i][k] = ' '; // undo move
                    if (score < bestScore)
                    {
                        bestScore = score;
                    }
                    // bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}
*/
