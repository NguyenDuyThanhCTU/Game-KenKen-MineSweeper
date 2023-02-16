#include <stdio.h>
#define N 5
#define M 5
#define MINE 5
int Column[8] ={1,-1,0,1,0,-1,1,-1};
int Row[8]	  ={1,-1,1,0,-1,0,-1,1};
int B[M][N];
int T[M][N];
void init(){
	int i,j;
	for(i=0;i<=M;i++)
		for(j=0;j<=N;j++)
			B[i][j] = 0;
			T[i][j] = 0;
}
void select(int a,int b){
	int i,j;
	int temp[M][N];
	if(B[a][b] == 0){
		B[a][b] = 1;
		for(i=0;i<8;i++)
			B[a + Column[i]][b + Row[i]] = 2;
//		for(i=0;i<M;i++){
//			for(j=0;j<N;j++){
//				B[i][j] = 3; Neu chay qua hai vong lap thi ca map bi cap nhat nen SAI
//				B[i][j] = 1;
//			}
//		}
//		if(temp[M][N] == 0){
//				temp[M][N] = 1;
//			}
//		for(i=0;i<8;i++){
//			temp[M][N] = B[a + Column[i]][b + Row[i]] //mang hai chieu temp khong the chua du lieu cua mang B.
//			if(temp[M][N] == 0){
//				temp[M][N] = 1;
//			}
//		}
	}
}
void printMap1(){
	int i,j;
	printf("   ");
	for(i=0;i<N;i++)
		printf(" %d ",i);
	printf("\n");
	
	for(i=0;i<M;i++){
		printf(" %d ",i);
		for(j=0;j<N;j++){
			printf(" %d ",B[i][j]);
		}
		printf("\n");
	}
}

int main(){
	init();
	printMap1();
	select(2,2);
	printf("\n");
	printMap1();
	return 0;
}

