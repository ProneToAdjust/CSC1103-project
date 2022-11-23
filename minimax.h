extern char board[3][3];
int checkEmptyCells();
char checkWin();
int *bestMoveByAI(char board[3][3], int togglePrune);
int miniMax(int depth, int isMaximizing, int alpha, int beta, int togglePrune);