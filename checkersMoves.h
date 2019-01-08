#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

extern int CheckLegalAndMakeMove(bool redPlayer, int originX, int destX, int originY, int destY, char*** board);
bool AnyJumpIsAvailable(bool redPlayer, char*** board);
char CheckForKing(char movingPiece, int destY);
bool PieceCanJump(int row, int col, char*** board);
bool CheckMoveIsJump(int destX, int destY, int originX, int originY);
bool CheckPlayerMovingOwnPiece(bool redPlayer, int originX, int originY, char*** board);
bool CheckStandardMoveIsLegal(bool isJump, int originX, int originY, int destX, int destY, char*** board);
extern void PrintBoard(char** board);

