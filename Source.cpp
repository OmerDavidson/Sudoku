#include <stdio.h>
#include <stdlib.h>
#define SIZE 9

typedef char BYTE;
typedef enum { FALSE, TRUE } boolean;
typedef struct game {

	BYTE board[SIZE][SIZE] = {
		{ 1,2,4,5,3,8,9,6,7 },
		{ 1,2,4,5,3,8,9,6,7 },
		{ 1,2,4,5,3,8,9,6,7 },
		{ 1,2,4,5,3,8,9,6,7 },
		{ 1,2,4,5,3,8,9,6,7 },
		{ 1,2,4,5,3,8,9,6,7 },
		{ 1,2,4,5,3,8,9,6,7 },
		{ 1,2,4,5,3,8,9,6,7 },
		{ 1,2,4,5,3,8,9,6,7 },
	};
	//TODO: change intialization to loop
}*pgame;
boolean rowsLegal(game* cur) {
	boolean legal = TRUE;
	boolean mone[SIZE];


	for (int i = 0; i < SIZE; i++) {
		for (int k = 0; k < SIZE; k++) {//initialize
			mone[k] = FALSE;
		}
		for (int j = 0; j < SIZE; j++) {
			if (mone[cur->board[i][j] - 1]) {
				printf("%d %d %d\n", i, j, mone[cur->board[i][j] - 1]);
				return FALSE;
			}

			mone[cur->board[i][j] - 1] = TRUE;
		}
	}
}

boolean Legal(game* cur) {
	boolean legal = TRUE;
	boolean moneR[SIZE],moneC[SIZE];


	for (int i = 0; i < SIZE; i++) {
		for (int k = 0; k < SIZE; k++) {//initialize
			moneR[k] = FALSE;
			moneC[k] = FALSE;
		}
		for (int j = 0; j < SIZE; j++) {
			if (moneR[cur->board[i][j] - 1]|| moneC[cur->board[j][i] - 1]) {
				return FALSE;
			}

			moneR[cur->board[i][j] - 1] = TRUE;
			moneC[cur->board[j][i] - 1] = TRUE;

		}
	}
}
void readBoard(char * path, game* cur) {
	FILE*  file =fopen(path, "rb");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			fread(&(cur->board[i][j]), sizeof(BYTE), 1, file);//read the value into the board
			fseek(file, 1, SEEK_CUR);//skip the comma
		}
	}
	fclose(file);
}

int main() {
	game* c = (pgame)malloc(sizeof(game));
	printf("%d\n", rowsLegal(c));
}