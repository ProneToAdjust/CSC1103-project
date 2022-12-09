/* gcc -o tictactoe_main tictactoe_main.c minimax.c naive_bayes_ai.c
 *  .\tictactoe_main
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include "minimax.h"
#include "naive_bayes_ai.h"

/*Array for board*/
char board[3][3];

/*Character of players*/
const char PlayerONE = 'X';
const char PlayerTWO = 'O';

/*Function call*/
void Instructions();
void BoardDisplay();
void Player1Turn();
void Player2Turn();
bool whoWinsRows();
bool whoWinsColumns();
bool whoWinsDiagonal();
int CheckEmptyCells();
void WINNER(char);

// changan code
int randomNumGen(bool randomSeed);
int zeroOrOne(bool randomSeed);
void manualPlayer();
void level1();
void level2();
void level3();
void level4();
int playerChoice;
int difficulty;

// prints game instructions
void Instructions()
{
    bool instructiontrue = true;

    do
    {
        printf("WELCOME TO A GAME OF TIC TAC TOE !\n\nInput 1 for 1 Player\nInput 2 for 2 Player\nPlease key your input:");
        scanf("%d", &playerChoice);

        if (playerChoice == 1)
        {
            do
            {
                printf("\nInput 1 for level 1\nInput 2 for level 2\nInput 3 for level 3\nInput 4 for level 4\nPlease key your input:");
                scanf("%d", &difficulty);

                if (difficulty == 1 || difficulty == 2 || difficulty == 3 || difficulty == 4)
                {
                    printf("Choose any empty cells and start playing\n");
                    instructiontrue = false;
                }

                else
                {
                    printf("Invalid input, please try again.\n\n");
                }
            } while (instructiontrue == true);
        }

        else if (playerChoice == 2)
        {
            printf("Choose any empty cells and start playing\n");
            instructiontrue = false;
        }

        else
        {
            printf("Invalid input, please try again.\n\n");
        }
    } while (instructiontrue == true);
}

/*A function to display board*/
void BoardDisplay()
{
    char display_board[3][3];
    int position_num = 0;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            position_num++;
            if (board[row][col] != ' ')
            {
                display_board[row][col] = board[row][col];
            }
            else
            {
                display_board[row][col] = position_num + '0';
            }
        }
        
    }
    
    // A function to display board
    printf("\n");
    printf("   %c | %c | %c", display_board[0][0], display_board[0][1], display_board[0][2]);
    printf("\n  ---|---|---\n");
    printf("   %c | %c | %c", display_board[1][0], display_board[1][1], display_board[1][2]);
    printf("\n  ---|---|---\n");
    printf("   %c | %c | %c", display_board[2][0], display_board[2][1], display_board[2][2]);
    printf("\n");
}

// ask player 1 for input for x,y and input in the grid if the move is not taken
void Player1Turn()
{
    int row, column, position;
    bool ValidMove = true;
    do
    {
        printf("\nPlayer 1 (X) please enter position (1-9): ");
        scanf("%d", &position);

        position--;
        
        row = position/3;
        column = row > 0 ? position % 3 : position;
        
        if (board[row][column] != ' ') // if board not empty
        {
            ValidMove = false;
            printf("Row/Column have been taken!\n");
        }
        else
        {
            // assigns X to selected cell
            board[row][column] = PlayerONE;
            break;
        }
    } while (ValidMove == false);
}

// it will execute the chosen gameplay chosen in instruction function
void Player2Turn()
{
    if (playerChoice == 1)
    {
        if (difficulty == 1)
        {
            level1();
        }

        else if (difficulty == 2)
        {
            level2();
        }

        else if (difficulty == 3)
        {
            level3();
        }

        else
        {
            level4();
        }
    }

    else
    {
        manualPlayer();
    }
}

// ask player 2 for input for x,y and input in the grid if the move is not taken
void manualPlayer()
{
    int row, column, position;
    bool ValidMove = true;
    do
    {
        printf("\nPlayer 2 (O) please enter position (1-9): ");
        scanf("%d", &position);
        
        position--;

        row = position/3;
        column = row > 0 ? position % 3 : position;
        
        if (board[row][column] != ' ') // if board not empty
        {
            ValidMove = false;
            printf("Row/Column have been taken!\n");
        }
        else
        {
            // assigns O to selected cell
            board[row][column] = PlayerTWO;
            break;
        }
    } while (ValidMove == false);
}

// x and y is generated through random generator
void level1()
{
    int row, column;
    bool ValidMove = true;
    do
    {
        int row = randomNumGen(true);
        int column = randomNumGen(false);
        row--;
        column--;
        if (board[row][column] != ' ') // if board not empty
        {
            ValidMove = false;
        }
        else
        {
            // assigns O to selected cell
            board[row][column] = PlayerTWO;
            break;
        }
    } while (ValidMove == false);
}

// Naive Bayes AI opponent, intermediate
void level2(){
    int converted_board[9];


    // Convert current game board to be used in the naive_bayes_ai local library
    int index = 0;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {   
            switch (board[row][col])
            {
            case 'X':
                converted_board[index] = 'o';
                break;

            case 'O':
                converted_board[index] = 'x';
                break;

            default:
                converted_board[index] = 'b';
                break;
            }
            index++;
        }
    }

    // Get position of best possible move from NB ai
    int best_move = get_best_move(converted_board);

    // Convert to position data usable by game board
    int row = best_move/3;
    int col = row > 0 ? best_move % 3 : best_move;

    // Make move
    board[row][col] = PlayerTWO;
}

// random generator is used to determine if level 1 or level 4 is executed
void level3()
{
    int option = zeroOrOne(true);
    if (option == 0)
    {
        level1();
    }
    else
    {
        level4();
    }
}

// minimax algorithm is used for this level
void level4()
{
    int *arrBestMove;
    arrBestMove = bestMoveByAI(board, 1);       //bestMoveByAI() defined in minimax.c file, linked by header
    board[arrBestMove[0]][arrBestMove[1]] = PlayerTWO;      //arrBestMove[0] = x axis, arrBestMove[1] = y axis
}

// Resets the board after game ends
void emptyBoard()
{

    // Initially the board is empty
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    }
}

/*checks the board to see if there are any empty cells left*/
int checkEmptyCells()
{
    int emptycells = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                emptycells--;
            }
        }
    }
    return emptycells;
}

/*check rows*/
bool whoWinsRows()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            if (board[i][0] == ' ' || board[i][1] == ' ' || board[i][2] == ' ')
                return (false);
            else
                return (true);
        }
    }
    return (false);
}

/*check columns*/
bool whoWinColumns()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            if (board[0][i] == ' ' || board[1][i] == ' ' || board[2][i] == ' ')
                return (false);
            else
                return (true);
        }
    }
    return (false);
}

/*check diagonals*/
bool whoWinsDiagonal()
{
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        if (board[0][0] == ' ' || board[1][1] == ' ' || board[2][2] == ' ')
            return (false);
        else
            return (true);
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        if (board[0][2] == ' ' || board[1][1] == ' ' || board[2][0] == ' ')
            return (false);
        else
            return (true);
    }
    return (false);
}

/*check winner*/
bool gameOver()
{
    return (whoWinsRows() || whoWinColumns() || whoWinsDiagonal());
}

/*print outcome of results*/
void WINNER(char winnername)
{
    if (winnername == PlayerONE)
    {

        printf("\nPlayer 1 Wins!");
    }
    else if (winnername == PlayerTWO)
    {
        printf("\nPlayer 2 Wins!");
    }
    else
    {
        printf("\nIt's a tie!");
    }
}

/*main function*/
int main()
{
    bool winner = false;
    char winnername = ' ';
    char again = ' ';
    Instructions(); // displays instructions
    emptyBoard();   // displayed empty board

    do
    {
        winnername = ' '; // resets winner
        again = ' ';
        winner = false;
        emptyBoard();   // displayed empty board upon playing again

        while (winner == false && checkEmptyCells() != 0) // while there is no winner and have empty cells
        {
            BoardDisplay();
            Player1Turn();
            //Player2Turn();    //uncomment to have AI go first -JunWei

            winner = gameOver();
            if (winner != true && checkEmptyCells() != 0)
            {
                BoardDisplay();
                Player2Turn();
                //Player1Turn();    //uncomment to have AI go first -JunWei
                winner = gameOver();
                if (winner == true)
                    winnername = PlayerTWO;
            }
            else
            {
                winner = gameOver();
                if (winner == true)
                    winnername = PlayerONE;
            }
        }

        BoardDisplay();
        WINNER(winnername); // declares winner

        printf("\nDo you want to play again? (Y/N): ");
        scanf("%c", &again);
        scanf("%c", &again);
        again = toupper(again);
    } while (again == 'Y');

    printf("\nEnd of game, thank you!\n");

    return 0;
}

// generate a random number (1-3) for level 1
int randomNumGen(bool randomSeed)
{
    int randomNum;

    /* initialize random seed: */
    if (randomSeed)
        srand(time(NULL));

    /* generate secret number between 1 and 3: */
    randomNum = rand() % 3 + 1;

    return randomNum;
}

// generate a random 0 or 1 for level 3
int zeroOrOne(bool randomSeed)
{
    int randomNo;

    /* initialize random seed: */
    if (randomSeed)
        srand(time(NULL));

    /* generate secret number between 1 and 3: */
    randomNo = rand() % 2;

    return randomNo;
}