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
boolean legal(game* cur) {
	boolean legal = TRUE;
	boolean moneR[SIZE], moneC[SIZE];

	for (int i = 0; i < SIZE; i++) {
		for (int k = 0; k < SIZE; k++) {//initialize
			moneR[k] = FALSE;
			moneC[k] = FALSE;
		}
		for (int j = 0; j < SIZE; j++) {
			if (cur->board[i][j]) {//rows
				if (moneR[cur->board[i][j] - 1]) {
					return FALSE;
				}
				moneR[cur->board[i][j] - 1] = TRUE;
			}
			if (cur->board[j][i]) {//collumns
				if (moneC[cur->board[j][i] - 1]) {
					return FALSE;
				}
				moneC[cur->board[j][i] - 1] = TRUE;
			}
		}
	}
	return TRUE;
}
boolean squares(game* cur) {
	boolean mone[SIZE];
	for (int i = 0; i < SIZE; i += 3) {
		for (int j = 0; j < SIZE; j += 3) {
			for (int k = 0; k < SIZE; k++)//intialize the mone
				mone[k] = FALSE;

			for (int x = i; x < i + 3; x++) {
				for (int y = j; y < j + 3; y++) {
					if (cur->board[x][y]) {
						if (mone[cur->board[x][y] - 1])
							return FALSE;
						mone[cur->board[x][y] - 1] = TRUE;
					}
				}
			}
		}
	}
	return TRUE;
}
void readBoard(char * path, game* cur) {
	FILE*  file = fopen(path, "rb");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			fread(&(cur->board[i][j]), sizeof(BYTE), 1, file);//read the value into the board
			(cur->board[i][j]) -= '0';
			fseek(file, 1, SEEK_CUR);//skip the comma
		}
	}
	fclose(file);

	//cur->board[2][3] = 5;
}

void printBoard(game* cur) {
	for (int i = 0; i < SIZE; i++) {
		if (i % 3 == 0) {
			for (int j = 0; j < SIZE; j++)
				printf("--");
			printf("-\n");
		}
		for (int j = 0; j < SIZE; j++) {
			if (j % 3 == 0)
				printf("|");
			printf("%d", cur->board[i][j]);
			if ((j + 1) % 3 != 0)
				printf(" ");


		}
		printf("|\n");
	}
	for (int j = 0; j < SIZE; j++)
		printf("--");
	printf("-\n");
}

int main() {
	game* c = (pgame)malloc(sizeof(game));
	readBoard("board.txt", c);
	printBoard(c);
	printf("%d\n", squares(c));
}