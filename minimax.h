extern char board[3][3];
char checkWin();
int *bestMoveByAI(char board[3][3], int playerNumber);
int miniMax(int depth, int isMaximizing, int alpha, int beta);