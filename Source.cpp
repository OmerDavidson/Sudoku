#include <stdio.h>
#include <stdlib.h>
#define SIZE 9

int cnt = 0;

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
}*pgame;
typedef struct pos {
	int x;
	int y;
	boolean last;
}pos;

boolean rowsCols(game* cur) {
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

boolean legal(game* cur) {
	if (rowsCols(cur) && squares(cur))
		return TRUE;
	else
		return FALSE;
}

void readBoard(const char* path, game* cur) {
	FILE* file = fopen(path, "rb");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			fread(&(cur->board[i][j]), sizeof(BYTE), 1, file);//read the value into the board
			(cur->board[i][j]) -= '0';
			fseek(file, 1, SEEK_CUR);//skip the comma
		}
	}
	fclose(file);
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

pos* getEmpty(game* cur) {
	pos* locations = (pos*)malloc(sizeof(pos));
	int length = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (cur->board[i][j] == 0) {
				if (!length) {
					locations[length].x = i;
					locations[length].y = j;
					locations[length].last = FALSE;
					length++;

				}
				else {
					locations = (pos*)realloc(locations, sizeof(pos) * (++length));
					locations[length - 1].x = i;
					locations[length - 1].y = j;
					locations[length - 1].last = FALSE;
				}
			}
		}
	}
	locations[length - 1].last = TRUE;
	if (length)
		return locations;
	else {
		//free(locations);
		return 0;
	}
}

pos* getZero(game* cur) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (cur->board[i][j] == 0) {
				pos* ret = (pos*)malloc(sizeof(pos));
				ret->x = i;
				ret->y = j;
				return ret;
			}
		}
	}
	return NULL;
}

boolean endGame(game* cur) {
	if (!getEmpty(cur) && legal(cur))
		return TRUE;
	else
		return FALSE;

}

boolean solve(game* cur) {
	cnt++;
	if (!legal(cur)) {
		return FALSE;
	}
	pos* locations = getZero(cur);
	if (!locations) {
		return TRUE;
	}
	//go through all possible positions
	for (int i = 0; i < SIZE; i++) {
		cur->board[locations->x][locations->y] = i + 1;
		if (solve(cur)) {
			return TRUE;
		}
	}
	cur->board[locations->x][locations->y] = 0;
	return FALSE;
}

int main() {
	game* c = (pgame)malloc(sizeof(game));
	readBoard("impossible.txt", c);
	printBoard(c);
	//printf("legal: %d\n", legal(c));

	printf("solve: %d\n", solve(c));
	printBoard(c);
	//printf("legal: %d\n", legal(c));
	printf("cnt: %d\n", cnt);
}
