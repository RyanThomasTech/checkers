#include <string.h>
#include "checkersMoves.h"

void PopulateBoard(char*** board);
void PlayTurn(char*** board, int turnCount);
bool BothSidesHavePieces(char** board);
int GetLetterVal(char xPosChar);

static bool jumpRequired = false;
static int turnCount = 0;

int main(){
	char** board;
	PopulateBoard(&board);
	while (BothSidesHavePieces(board)){
		PrintBoard(board);
		PlayTurn(&board, turnCount);
		turnCount++;
	}
	PrintBoard(board);
	for(int i=0; i<8;i++){
		free(board[i]);
	}
	free(board);
	printf("\nGame over!\n");
}

void PopulateBoard(char*** board){
	(*board) = (char **) malloc(8*sizeof(char*));
	for (int row =0; row<8; row++){
		(*board)[row] = (char *) malloc(8*sizeof(char));
		for (int col = 0; col<8; col++){
			if ((row==0 || row==2) && col%2==1){
				(*board)[row][col] = 'b';
			} else if (row==1 && col%2==0){
				(*board)[row][col] = 'b';
			} else if ((row==5 || row==7) && col%2==0){
				(*board)[row][col] =  'r';
			} else if (row==6 && col%2==1){
				(*board)[row][col] = 'r';
			} else {
				(*board)[row][col] = ' ';
			}
		}
	}
}

bool BothSidesHavePieces(char** board){
	bool redPieceFound = false;
	bool blackPieceFound = false;
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (board[row][col]=='r' || board[row][col]=='R'){
				redPieceFound = true;
			} else if (board[row][col]=='b' || board[row][col]=='B'){
				blackPieceFound = true;
			}
			if (redPieceFound && blackPieceFound){
				return true;
			}
		}
	}
	return false;
}

void PlayTurn(char*** board, int turnCount){
	//jumpRequired = JumpAvailable(board, turnCount);
	bool redPlayer = turnCount%2;
	char usrInput[7], originXPosChar, destXPosChar;
	int destXPos, destYPos, originXPos, originYPos;
	do {
		printf("Input the position of the piece you're moving, then the position you're moving to, separated by a comma (e.g. a2,b3)... ");
		memset(usrInput, '\0', sizeof(usrInput));
		fgets(usrInput, 7, stdin);
		originXPosChar = usrInput[0];
		destXPosChar = usrInput[3];
		originXPos = GetLetterVal(originXPosChar);
		destXPos = GetLetterVal(destXPosChar);
		originYPos = usrInput[1]-'0';
		destYPos = usrInput[4]-'0';
	} while ( CheckLegalAndMakeMove(redPlayer, originXPos, destXPos, originYPos, destYPos, board) != 0 );
}

int GetLetterVal(char xPosChar){
	if (xPosChar == 97 || xPosChar == 65 ) return 0;
	if (xPosChar == 98 || xPosChar == 66 ) return 1;
	if (xPosChar == 99 || xPosChar == 67 ) return 2;
	if (xPosChar == 100 || xPosChar == 68 ) return 3;
	if (xPosChar == 101 || xPosChar == 69 ) return 4;
	if (xPosChar == 102 || xPosChar == 70 ) return 5;
	if (xPosChar == 103 || xPosChar == 71 ) return 6;
	if (xPosChar == 104 || xPosChar == 72 ) return 7;
	printf("\n erroneous value received\n");
	return -1;
}

