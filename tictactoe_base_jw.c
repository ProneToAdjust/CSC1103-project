#include <stdio.h>
#include <stdlib.h>

const char PLAYER1 = 'X';
const char PLAYER2 = 'O';
int currentTurn = 0;
int currentPlayer = 0;
char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}};


void computerMove();  // insert AI/algorithm, takes in move/position in board as parameter

void printBoard();
void resetGame();
void playerMove(char player);
char checkWin();
void printWinner(char player);
int isBoardFull();
void choosePlayer();
int turnTracker(char player);
void playerTracker(int player); // track current turn is whose, can think of merging with turnTracker()


int main()
{
    char winner = ' ';

    resetGame();
    choosePlayer();

    while (winner == ' ' && isBoardFull() != 0)
    {
        printBoard();
        playerMove(currentPlayer);
        winner = checkWin();
        if (winner != ' ' || isBoardFull() == 0)
        {
            break;
        }
        printBoard();
        playerTracker(currentPlayer);
        playerMove(currentPlayer);
        winner = checkWin();
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
    if(player == 1){
        move = PLAYER1;
    }
    else if(player == 2){
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

    while (board[x][y] != ' ');     //continue looping to ask user for move if move is invalid

}

char checkWin()
{
    // loops through to check all rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    // loops through to check all columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == board[1][j]  && board[0][j] == board[2][j])
        {
            return board[0][j];
        }
    }

    // check diagonal, top left to bottom right
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }

    // check diagonal, top right to bottom left
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }

    return ' '; // if no winner, return empty char
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

    case ' ':
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

void choosePlayer(){
    do{
        printf("Play as Player 1 or 2? ");
        scanf("%d", &currentPlayer);

        if(currentPlayer == 1){
            break;
        }
        else if(currentPlayer == 2){
            break;
        }
        else{
            printf("\n Please only input 1 or 2 \n");
        }
    }
    while(!(currentPlayer==1 || currentPlayer== 2));
}

int turnTracker(char player){      //can pass in current player as para

    if(player == 1){
        //print current turn is whose
    }
    if(player == 2){

    }
    static int turn = 9;
    turn-=1;
    return turn;
}

void playerTracker(int player){
    if(player == 1){
        currentPlayer = 2;
    }
    if(player == 2){
        currentPlayer = 1;
    }
}