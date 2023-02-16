#include <stdio.h>
#define M 5
#define N 5
#define MINE -1

int B[M][N];
int T[M][N];
int column[8] = { +1,-1,+1,-1,0,+1,0,-1 };
int row[8] = 	{ +1,-1,-1,+1,+1,0,-1,0 };
// khai bao hai mang column va row de dung cho ham count_mines 

void init() {
	int i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			B[i][j] = 0;
			T[i][j] = 0;
		}
	}
	B[1][2] = MINE;
	B[3][1] = MINE;
}

void count_mines() {
	int i, j, x;
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			if (B[i][j] != MINE) {
				for (x = 0; x < 8; x++) {
					if (B[i + column[x]][j + row[x]] == MINE) {
						++B[i][j];
						/*lay toa do o duoc chon lam chuan. cong tru theo column va rown
						VD: chon o B[3][3], xet 8 o xung quanh thi:
						B[3 + 1][3 + 1] = B[4][4] : Toa do goc phai phia duoi o duoc chon
						...
						B[3 + 0][3 + 1] = B[3][4] : Toa do o ben phai o duoc chon
						cu the chay het vong lap ta se duoc 8 o xung quanh o da duoc chon.
						Neu 8 o xung quanh, toa do o nao = MINE thi tang o duoc chon len 1.
						*/
					}
				}
			}
		}
	}
}

void printMap1() {
	int j, i;
	printf("  ");
	for (j = 0; j < N; j++) {
		printf("%d ", j % 10);
	}
	printf("\n");

	for (i = 0; i < M; i++) {
		printf("%d ", i % 10);
		for (j = 0; j < N; j++)
			if (B[i][j] == MINE)
				printf("x ");
			else if (B[i][j] == 0)
				printf(". ");
			else  printf("%d ", B[i][j]);
		printf("\n");
	}
}

void printMap2() {
	int  i, j;
	printf("  ");
	for (i = 0; i < M; i++) {
		printf("%d ", i);
	}
	printf("\n");
	for (i = 0; i < M; i++) {
		printf("%d ", i);
		for (j = 0; j < N; j++) {
			if (T[i][j] == 0) printf("# ");
			else if (B[i][j] == MINE) printf("x ");
			else if (B[i][j] == 0) printf(". ");
			else printf("%d ", B[i][j]);
		}
		printf("\n");
	}
}

int count_remain() {
	int i, j;
	int cnt = 0;
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			if (T[i][j] == 0)
				cnt++;
	return cnt;
}

void open_cell_1(int r, int c) {
	if (T[r][c] == 0)
		T[r][c] = 1;
}



int condition(int r, int c) {
	if (r < 0 || r >= M || c < 0 || c >= N) {
		return 0;
	}return 1;
}

void open_cell_2(int r, int c) {
	int t;
	T[r][c] = 1;
	if (B[r][c] == 0) {
		for (t = 0; t < 8; t++) {
			if (condition(r + column[t], c + row[t]))
				T[r + column[t]][c + row[t]] = 1;
		}
	}
}



void open_cell_3(int r, int c) {
	int x;
	if (condition(r, c) == 0) return;
	else if (T[r][c] == 1) {
		return;
	}
	else {
		T[r][c] = 1;
		for (x = 0; x < 8; x++) {
			if (B[r][c] > 0){
				if (B[r + column[x]][c + row[x]] == MINE) {
					return;
				}
			}
			else open_cell_3(r + column[x], c + row[x]);
		}
	}
}

int main() {
	int r, c;
	int k = 2;
	init();
	count_mines();
	while (1) {
		printMap2();
		printf("Nhap o can mo: ");
		scanf("%d%d", &r, &c);
		system("cls");
		system("color 2");
		system("color 3");
		if (B[r][c] == MINE) {
			printMap1();
			printf("You Lose.\n");
			break;
		}
		open_cell_3(r, c);
		if (count_remain() == k) {
			printMap1();
			printf("You Win.\n");
			break;
		}
	}
	return 0;
}
