#include "checkersMoves.h"

int CheckLegalAndMakeMove(bool redPlayer, int originX, int destX, int originY, int destY, char*** board){
	bool jumpAvailable = AnyJumpIsAvailable(redPlayer,board);
	bool moveIsJump = CheckMoveIsJump(destX,destY,originX,originY);
	bool playerMovingOwnPiece = CheckPlayerMovingOwnPiece(redPlayer, originX, originY, board);
	bool standardMoveIsLegal = CheckStandardMoveIsLegal(moveIsJump, originX,originY,destX,destY,board);
	if (!playerMovingOwnPiece){
		printf("\nIt's not your turn.");
		return 1;
	}
	if (jumpAvailable && (!moveIsJump || !standardMoveIsLegal)){
		printf("\n You must jump if able.");
		return 1;
	}
	if (!standardMoveIsLegal){
		printf("\nIllegal move");
		return 1;
	}
	char buffer = (*board)[originY][originX];
	if (moveIsJump){
		(*board)[originY+((destY-originY)/2)][originX+((destX-originX)/2)] = ' ';
		(*board)[originY][originX] = ' ';
		(*board)[destY][destX] = CheckForKing(buffer, destY);
		if (PieceCanJump(destY,destX, board)){
			PrintBoard(*board);
			printf("\n Continue jumping with another move selection: ");
			return 1;
		}
	}
	(*board)[originY][originX] = ' ';
	(*board)[destY][destX] = CheckForKing(buffer, destY);
	return 0;
}

char CheckForKing(char movingPiece, int destY){
	if (movingPiece == 'r' && destY == 0){
		return 'R';
	} else if (movingPiece == 'b' && destY == 7){
		return 'B';
	}
	return movingPiece;
}

bool CheckStandardMoveIsLegal(bool isJump, int originX, int originY, int destX, int destY, char*** board){
	char piece = (*board)[originY][originX];
	if (isJump){
		char betweenPiece = 
			(*board)[originY+((destY-originY)/2)][originX+((destX-originX)/2)];
		if ((*board)[destY][destX]==' '){
			if (piece == 'r' && (destY-originY)==-2){
				if (betweenPiece=='b' || betweenPiece=='B'){
					return true;
				}
			} else if (piece=='b' && (destY-originY)==2){
				if (betweenPiece=='r' || betweenPiece=='R'){
					return true;
				}
			} else if (abs(destY-originY)==2){
				if (piece=='B' && (betweenPiece=='r' || betweenPiece=='R')){
					return true;
				}
				if (piece=='R' && (betweenPiece=='b' || betweenPiece=='B')){
					return true;
				}
			}
		}
	} else if (abs(destX-originX)==1 && (*board)[destY][destX]==' '){
		if (piece == 'r' && (destY-originY)==-1){
			return true;
		} else if (piece=='b' && (destY-originY)==1){
			return true;
		} else if (abs(destY-originY)==1){
			return true;
		}
	}
	return false;
}


bool CheckPlayerMovingOwnPiece(bool redPlayer, int originX, int originY, char*** board){
	char piece = (*board)[originY][originX];
	if(redPlayer && (piece == 'r' || piece == 'R')){
		return true;
	} else if (!redPlayer && (piece=='b' || piece=='B')){
		return true;
	}
	return false;
}


bool CheckMoveIsJump(int destX, int destY, int originX, int originY){
	if (abs(destX-originX)==2 && abs(destY-originY)==2){
		return true;
	}
	return false;
}

bool AnyJumpIsAvailable(bool redPlayer, char*** board){
	for (int row = 0; row<8; row++){
		for(int col = 0; col<8; col++){
			char piece = (*board)[row][col];
			if (redPlayer && (piece == 'r' || piece == 'R')){
				if (PieceCanJump(row,col, board)){
					return true;
				}
			} else if (!redPlayer && (piece == 'b' || piece == 'B')){
				if (PieceCanJump(row,col,board)){
					return true;
				}
			}
		}
	}
	return false;
}

bool PieceCanJump(int row, int col, char*** board){
	char piece = (*board)[row][col];
	if (piece == 'r' || piece == 'R' ){
		if (row-2 >= 0 && col+2 <= 7 && (*board)[row-2][col+2] == ' '){
			if ( (*board)[row-1][col+1] == 'b' || (*board)[row-1][col+1] == 'B'){
				return true;
			}
		}
		if (row-2 >= 0 && col-2 >= 0 && (*board)[row-2][col-2] == ' '){
			if ( (*board)[row-1][col-1] == 'b' || (*board)[row-1][col-1] == 'B'){
				return true;
			}
		}
	}
	if (piece == 'b' || piece == 'B'){
		if (row+2 <= 7 && col+2 <= 7 && (*board)[row+2][col+2] == ' '){
			if ( (*board)[row+1][col+1] == 'r' || (*board)[row+1][col+1] == 'R'){
				return true;
			}
		}
		if (row+2 <=7 && col-2 >= 0 && (*board)[row+2][col-2] == ' '){
			if ( (*board)[row+1][col-1] == 'r' || (*board)[row+1][col-1] == 'R'){
				return true;
			}
		}
	}
	if (piece == 'R' ){
		if (row+2 <= 7 && col+2 <= 7 && (*board)[row+2][col+2] == ' '){
			if ( (*board)[row+1][col+1] == 'b' || (*board)[row+1][col+1] == 'B'){
				return true;
			}
		}
		if (row+2 <=7 && col-2 >= 0 && (*board)[row+2][col-2] == ' '){
			if ( (*board)[row+1][col-1] == 'b' || (*board)[row+1][col-1] == 'B'){
				return true;
			}
		}
	}
	if (piece == 'B'){
		if (row-2 >= 0 && col+2 <= 7 && (*board)[row-2][col+2] == ' '){
			if ( (*board)[row-1][col+1] == 'r' || (*board)[row-1][col+1] == 'R'){
				return true;
			}
		}
		if (row-2 >= 0 && col-2 >= 0 && (*board)[row-2][col-2] == ' '){
			if ( (*board)[row-1][col-1] == 'r' || (*board)[row-1][col-1] == 'R'){
				return true;
			}
		}
	}
	return false;
}

void PrintBoard(char** board){
	printf("  A B C D E F G H\n");
	for (int row=0; row<8;row++){
		printf("%d|", row);
		for (int col = 0; col<8; col++){
			printf("%c|",board[row][col]);
		}
		printf("\n |");
		for (int col = 0; col<8; col++){
			printf("-+");
		}
		printf("\n");
	}
	printf("  A B C D E F G H\n");
}
