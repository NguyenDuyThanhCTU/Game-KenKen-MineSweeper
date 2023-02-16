/*
	Name: KenKen 
	Copyright: 
	Author: Duy Thanh & Bao Tri
	Date: 25/10/20 20:30
	Description: kenken puzzles
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <D:\Project\KenKen\List_Player.c>

#define MAX_M 100
#define MAX_N 100


typedef struct{
	int x;
	int y;
}Point;

typedef struct{
	int Result;
	char opt;
	int num_Cell;
	Point Array_Cell[5];
}Frame;

typedef struct{
	int Num_Frame;
	Frame Array_Frame[35];
}List;

typedef struct{
	int so_PT;
	int Array_PT[12];
}Col;

typedef struct{
	int so_PT;
	int Array_PT[20];
}Row;

typedef struct{
	int m, n;
	int Array[MAX_M][MAX_N];
	int Num_row;
	Col Array_col[10];
	Row Array_row[10];
}MAP;


int time(){
	int hours, minutes, seconds;
	struct tm ts;
	time_t now;
	
	now = time(0);
	ts = *localtime(&now);
	hours = ts.tm_hour;
	minutes = ts.tm_min;
	if(hours > 12)
		hours = hours - 12;
	seconds = hours*3600 + minutes*60;
	
	return seconds;
}


void MakeNull_List(List *list){
	list->Num_Frame = 0;	
}

void Read_File(List *list, char fname[]){
	FILE *file = fopen(fname, "r");
	fscanf(file, "%d\n", &list->Num_Frame);
	int i, j;
	for(i=0;i<list->Num_Frame;i++){
		fscanf(file, "%d ", &list->Array_Frame[i].Result);
		fscanf(file, "%c ", &list->Array_Frame[i].opt);
		fscanf(file, "%d ", &list->Array_Frame[i].num_Cell);
		for(j=0;j<list->Array_Frame[i].num_Cell;j++){
			fscanf(file, "%d ", &list->Array_Frame[i].Array_Cell[j].x);
			fscanf(file, "%d ",  &list->Array_Frame[i].Array_Cell[j].y);
		}
		fscanf(file, "\n");
	}
		fclose(file);		
}


void Read_Map(MAP *map, char fname[]){
	FILE *file = fopen(fname, "r");
	fscanf(file, "%d %d", &map->m, &map->n);
	int i, j;
	for(i=0;i<map->m;i++){
		for(j=0;j<map->n;j++)
			fscanf(file, "%d ", &map->Array[i][j]);
		fscanf(file, "\n");
	}
	fscanf(file, "%d\n", &map->Num_row);
	for(i=0; i<map->Num_row;i++){
		fscanf(file, "%d ", &map->Array_row[i].so_PT);
		for(j=0;j<map->Array_row[i].so_PT;j++)
			fscanf(file, "%d ", &map->Array_row[i].Array_PT[j]);
		fscanf(file, "\n");
	}
	for(i=0;i<map->m;i++){
		fscanf(file, "%d ", &map->Array_col[i].so_PT);
		for(j=0;j<map->Array_col[i].so_PT;j++)
			fscanf(file, "%d ", &map->Array_col[i].Array_PT[j]);
		fscanf(file, "\n");
	}
	fclose(file);	
}


int X(int i, int j,List list){
	return list.Array_Frame[i].Array_Cell[j].x;	
}

int Y(int i, int j,List list){
	return list.Array_Frame[i].Array_Cell[j].y;	
}

int OPT(char c, int a, int b){
	switch(c){
		case '+': return a+b;
		case '-': return a-b;
		case '*': return a*b;
		case '/': return a/b;
	}
	return 0;	
}

int KT_Toado(int i, int j, List list){
	int nFrame;
	for(nFrame=0;nFrame<list.Num_Frame;nFrame++){
		if(X(nFrame, 0, list)==i && Y(nFrame, 0, list)==j)
			return 1;
	}
	return 0;
}


void inOpt(int i, int j, List list){
	int nFrame;
	for(nFrame=0;nFrame<list.Num_Frame;nFrame++){
		if(X(nFrame, 0, list)==i && Y(nFrame, 0, list)==j){
			printf("%3d%c", list.Array_Frame[nFrame].Result, list.Array_Frame[nFrame].opt);
			break;
		}
	}
}


int KT_Frame(List list, MAP map){
	int nFrame, nCell;
	for(nFrame=0;nFrame<list.Num_Frame;nFrame++){
		if(list.Array_Frame[nFrame].num_Cell == 1){
			if(map.Array[X(nFrame, 0, list)][Y(nFrame, 0, list)] != list.Array_Frame[nFrame].Result)
				return 0;
		}
		else if(list.Array_Frame[nFrame].num_Cell == 2){
			int tmp = OPT(list.Array_Frame[nFrame].opt, 
				map.Array[X(nFrame, 0 , list)][Y(nFrame, 0, list)], 
				map.Array[X(nFrame, 1 , list)][Y(nFrame, 1, list)]);
			tmp = abs(tmp);
			if(tmp != list.Array_Frame[nFrame].Result)
				return 0;
		}
		else if(list.Array_Frame[nFrame].num_Cell == 3){
			int tmp1 = OPT(list.Array_Frame[nFrame].opt, 
				map.Array[X(nFrame, 0 , list)][Y(nFrame, 0, list)], 
				map.Array[X(nFrame, 1 , list)][Y(nFrame, 1, list)]);
			int tmp2 = OPT(list.Array_Frame[nFrame].opt, tmp1, 
				map.Array[X(nFrame, 2 , list)][Y(nFrame, 2, list)]);
			tmp2 = abs(tmp2);
			if(tmp2 != list.Array_Frame[nFrame].Result)
				return 0;
		}
		else if(list.Array_Frame[nFrame].num_Cell == 4){
			int tmp1 = OPT(list.Array_Frame[nFrame].opt, 
				map.Array[X(nFrame, 0 , list)][Y(nFrame, 0, list)], 
				map.Array[X(nFrame, 1 , list)][Y(nFrame, 1, list)]);
			int tmp2 = OPT(list.Array_Frame[nFrame].opt, tmp1, 
				map.Array[X(nFrame, 2 , list)][Y(nFrame, 2, list)]);
			int tmp3 = OPT(list.Array_Frame[nFrame].opt, tmp2, 
				map.Array[X(nFrame, 3 , list)][Y(nFrame, 3, list)]);
			tmp3 = abs(tmp3);
			if(tmp3 != list.Array_Frame[nFrame].Result)
				return 0;
		}
	}
	return 1;
}


int Duyet_TT(int i, int j, int x, List list, MAP map){
	int row, col;
	//Duyet hang ngang
	for(row=0;row<map.m;row++){
		if(row != j){
			if(map.Array[i][row] == x)
				return 1;
		}
	}

	for(col=0;col<map.m;col++){
		if(col != i)
		if(map.Array[col][j] == x)
			return 1;
	}
	return 0;	
}


void pourFrame(int x, int i, int j, List list, MAP *map){
	int nFrame;
	for(nFrame=0;nFrame<list.Num_Frame;nFrame++){
		if(list.Array_Frame[nFrame].num_Cell == 1){
			if(X(nFrame, 0, list)==i && Y(nFrame, 0, list)==j)
				map->Array[X(nFrame, 0, list)][Y(nFrame, 0, list)] = x;
		}
		else if(list.Array_Frame[nFrame].num_Cell == 2){
			if(X(nFrame, 0, list)==i && Y(nFrame, 0, list)==j)
				map->Array[X(nFrame, 0, list)][Y(nFrame, 0, list)] = x;
			else if(X(nFrame, 1, list)==i && Y(nFrame, 1, list)==j)
				map->Array[X(nFrame, 1, list)][Y(nFrame, 1, list)] = x;		
		}
		else if(list.Array_Frame[nFrame].num_Cell == 3){
			if(X(nFrame, 0, list)==i && Y(nFrame, 0, list)==j)
				map->Array[X(nFrame, 0, list)][Y(nFrame, 0, list)] = x;
			else if(X(nFrame, 1, list)==i && Y(nFrame, 1, list)==j)
				map->Array[X(nFrame, 1, list)][Y(nFrame, 1, list)] = x;
			else if(X(nFrame, 2, list)==i && Y(nFrame, 2, list)==j)
				map->Array[X(nFrame, 2, list)][Y(nFrame, 2, list)] = x;	
		}
		else if(list.Array_Frame[nFrame].num_Cell == 4){
			if(X(nFrame, 0, list)==i && Y(nFrame, 0, list)==j)
				map->Array[X(nFrame, 0, list)][Y(nFrame, 0, list)] = x;
			else if(X(nFrame, 1, list)==i && Y(nFrame, 1, list)==j)
				map->Array[X(nFrame, 1, list)][Y(nFrame, 1, list)] = x;
			else if(X(nFrame, 2, list)==i && Y(nFrame, 2, list)==j)
				map->Array[X(nFrame, 2, list)][Y(nFrame, 2, list)] = x;
			else if(X(nFrame, 3, list)==i && Y(nFrame, 3, list)==j)
				map->Array[X(nFrame, 3, list)][Y(nFrame, 3, list)] = x;
		}
	}
}


void PrintMap(List list, MAP map){
	int i, j, k;
	printf("\t\t\t\t\t\t\t\t     ");
	for(j=0;j<map.m;j++)
		printf("%d    ", j%10);
	printf("\n");
	
	for(i=0;i<map.Num_row;i++){
		printf("\t\t\t\t\t\t\t\t  ");
		for(j=0;j<map.Array_row[i].so_PT;j++){
			if(map.Array_row[i].Array_PT[j]==1){
				for(k=0;k<4;k++)
					printf("%c", 205);
			}
			else if(map.Array_row[i].Array_PT[j]==2){
				for(k=0;k<4;k++)
					printf("%c", 196);
			}
			else
				printf("%c", map.Array_row[i].Array_PT[j]);
		}
		printf("\n");
		if(i == map.m)
			break;
		
		for(j=0;j<map.m;j++){
			if(j==0)
				printf("\t\t\t\t\t\t\t\t  ");
			if(KT_Toado(i, j, list)){
				if(map.Array_col[i].Array_PT[j] == 2){
					printf(" ");
					inOpt(i, j, list);
				}
				else{
					printf("%c", map.Array_col[i].Array_PT[j], map.Array[i][j]);
					inOpt(i, j, list);
				}
			}	
			else{
				if(map.Array_col[i].Array_PT[j] == 2)
					printf("     ");
				else
					printf("%c    ", map.Array_col[i].Array_PT[j], map.Array[i][j]);
			}
		}
		printf("%c",map.Array_col[i].Array_PT[j]);
		printf("\n");
		
		printf("\t\t\t\t\t\t\t\t%d ", i%10);
		for(j=0;j<map.n;j++){
			if(map.Array[i][j] == 0){
				if(map.Array_col[i].Array_PT[j] == 2)
					printf("%c    ", 179, map.Array[i][j]);
				else
					printf("%c    ", map.Array_col[i].Array_PT[j], map.Array[i][j]);		
			}
			else{
				if(map.Array_col[i].Array_PT[j] == 2)
					printf("%c  %2d",179, map.Array[i][j]);
				else
					printf("%c%2d  ", map.Array_col[i].Array_PT[j], map.Array[i][j]);	
			}
		}
		printf("%c",map.Array_col[i].Array_PT[j]);
		printf("\n");	
	}
}	


void Print_KenKen(){
	printf("\t\t\t\t\t\t%c%c      %c%c  %c%c%c%c%c%c%c  %c%c%c%c        %c%c     %c%c      %c%c  %c%c%c%c%c%c%c  %c%c%c%c        %c%c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	printf("\t\t\t\t\t\t%c%c    %c%c    %c%c       %c%c%c%c        %c%c     %c%c    %c%c    %c%c       %c%c%c%c        %c%c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	printf("\t\t\t\t\t\t%c%c  %c%c      %c%c       %c%c  %c%c      %c%c     %c%c  %c%c      %c%c       %c%c  %c%c      %c%c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	printf("\t\t\t\t\t\t%c%c%c%c        %c%c%c%c%c%c%c  %c%c    %c%c    %c%c     %c%c%c%c        %c%c%c%c%c%c%c  %c%c    %c%c    %c%c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	printf("\t\t\t\t\t\t%c%c  %c%c      %c%c       %c%c      %c%c  %c%c     %c%c  %c%c      %c%c       %c%c      %c%c  %c%c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	printf("\t\t\t\t\t\t%c%c    %c%c    %c%c       %c%c        %c%c%c%c     %c%c    %c%c    %c%c       %c%c        %c%c%c%c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	printf("\t\t\t\t\t\t%c%c      %c%c  %c%c%c%c%c%c%c  %c%c        %c%c%c%c     %c%c      %c%c  %c%c%c%c%c%c%c  %c%c        %c%c%c%c\n\n\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
}


void Print_You_Win(){
	printf("\t\t\t\t\t\t %c%c      %c%c    %c%c%c%c%c     %c%c     %c%c       %c%c          %c%c   %c%c%c%c  %c%c%c%c      %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t  %c%c    %c%c   %c%c     %c%c   %c%c     %c%c       %c%c          %c%c    %c%c   %c%c%c%c      %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t   %c%c  %c%c    %c%c     %c%c   %c%c     %c%c       %c%c    %c%c    %c%c    %c%c   %c%c  %c%c    %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t    %c%c%c%c     %c%c     %c%c   %c%c     %c%c       %c%c  %c%c  %c%c  %c%c    %c%c   %c%c    %c%c  %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t    %c%c%c%c     %c%c     %c%c   %c%c     %c%c       %c%c %c%c    %c%c %c%c    %c%c   %c%c      %c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t    %c%c%c%c       %c%c%c%c%c       %c%c%c%c%c         %c%c%c        %c%c%c   %c%c%c%c  %c%c      %c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);  		
}


void Print_You_Lose(){
	printf("\t\t\t\t\t\t %c%c      %c%c    %c%c%c%c%c     %c%c     %c%c     %c%c        %c%c%c%c%c      %c%c%c%c    %c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t  %c%c    %c%c   %c%c     %c%c   %c%c     %c%c     %c%c      %c%c     %c%c  %c%c    %c%c  %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t   %c%c  %c%c    %c%c     %c%c   %c%c     %c%c     %c%c      %c%c     %c%c    %c%c      %c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t    %c%c%c%c     %c%c     %c%c   %c%c     %c%c     %c%c      %c%c     %c%c      %c%c    %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t    %c%c%c%c     %c%c     %c%c   %c%c     %c%c     %c%c      %c%c     %c%c  %c%c    %c%c  %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("\t\t\t\t\t\t    %c%c%c%c       %c%c%c%c%c       %c%c%c%c%c       %c%c%c%c%c%c    %c%c%c%c%c      %c%c%c%c    %c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);			
}


int BuildMap1(List *list, MAP *map){
	char StateName[] = "KenKen1.txt";
	char MapName[] = "Map1.txt";
	MakeNull_List(list);
	Read_File(list, StateName);
	Read_Map(map, MapName);
	Print_KenKen();
	PrintMap(*list, *map);
	return 1;
}


int BuildMap2(List *list, MAP *map){
	char StateName[] = "KenKen2.txt";
	char MapName[] = "Map2.txt";
	MakeNull_List(list);
	Read_File(list, StateName);
	Read_Map(map, MapName);
	Print_KenKen();
	PrintMap(*list, *map);
	return 2;
}


int BuildMap3(List *list, MAP *map){
	char StateName[] = "KenKen3.txt";
	char MapName[] = "Map3.txt";
	MakeNull_List(list);
	Read_File(list, StateName);
	Read_Map(map, MapName);
	Print_KenKen();
	PrintMap(*list, *map);
	return 3;
}


int BuildMap4(List *list, MAP *map){
	char StateName[] = "KenKen4.txt";
	char MapName[] = "Map4.txt";
	MakeNull_List(list);
	Read_File(list, StateName);
	Read_Map(map, MapName);
	Print_KenKen();
	PrintMap(*list, *map);
	return 4;
}


int Color(int n){
	switch(n){
		case 1: return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
		case 2: return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 241);
	}
	return 0;
}


void SetUp(int n){
	if(n==1){
		printf("\t\t\t\t\t\t\t\t0 - 1 - 2 - 3 - 4 - 5 \n");
		printf("\t\t\t\t\t\t\t\tNHAP 0 NEU BAN MUON THOAT.\n");
	}
	else if(n==2){
		printf("\t\t\t\t\t\t\t\t0 - 1 - 2 - 3 - 4 - 5 - 6 \n");
		printf("\t\t\t\t\t\t\t\tNHAP 0 NEU BAN MUON THOAT.\n");
	}
	else if(n==3){
		printf("\t\t\t\t\t\t\t\t0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9\n");
		printf("\t\t\t\t\t\t\t\tNHAP 0 NEU BAN MUON THOAT.\n");
	}
	else{
		printf("\t\t\t\t\t\t\t\t0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 \n");
		printf("\t\t\t\t\t\t\t\tNHAP 0 NEU BAN MUON THOAT.\n");
	}	
}


Player Nhap_Player(int s){
	Player a;
	char name[6];
	printf("\n\n\n");
	printf("\t\t\t\t\t\tNHAP TEN DE LUU KET QUA(Toi da 5 ki tu): ");
	scanf("\n");
	fgets(name, 6, stdin);
	int len = strlen(name);
	if(name[len - 1] == '\n')
		name[len - 1] = '\0';
	a.Name = strdup(name);
	a.Num_sec = s;
	return a;
}


void Save_PLayer(Player a){
	ListPlay L;
	MakeNull_List(&L);
	char fname[] = { "DanhSachPlayer.txt" };
	Read_File(&L, fname);
	Insert_List(a, &L);
	system("cls");
	Print_KenKen();
	Print_List(L);
	Write_File(L, fname);	
}


int Level(List *list, MAP *map){
	int n;
	Print_KenKen();
	printf("\t\t\t\t\t\t1. 3x3\n");
	printf("\t\t\t\t\t\t2. 4x4\n");
	printf("\t\t\t\t\t\t3. 6x6\n");
	printf("\t\t\t\t\t\t4. 9x9\n");
	printf("\t\t\t\t\t\tCHON MAP DE BAT DAU: ");
	scanf("%d", &n);
	system("cls");
	switch(n){
		case 1: return BuildMap1(list, map);
		case 2: return BuildMap2(list, map);
		case 3: return BuildMap3(list, map);
		case 4: return BuildMap4(list, map);
		default: return Level(list, map);
	}
	return 0;		
}

 int Sound(int n){
	switch(n){
		case 1: return PlaySound(TEXT("D:\\Project\\KenKen\\Sound\\INTRO-SOUND-EFFECT.wav"),NULL,SND_SYNC);	
		case 2: return PlaySound(TEXT("D:\\Project\\KenKen\\Sound\\SPONGEBOB-TIME-CARDS-A-FEW-MOMENTS-LATER.wav"),NULL,SND_SYNC);
		case 3: return PlaySound(TEXT("D:\\Project\\KenKen\\Sound\\CARTOON-POP.wav"),NULL,SND_SYNC);
		case 4: return PlaySound(TEXT("D:\\Project\\KenKen\\Sound\\DUN-DUN-DUNNN.wav"),NULL,SND_SYNC);
		case 5: return PlaySound(TEXT("D:\\Project\\KenKen\\Sound\\YAY.wav"),NULL,SND_SYNC);
		case 6: return PlaySound(TEXT("D:\\Project\\KenKen\\Sound\\FAIL-_2.wav"),NULL,SND_SYNC);
	}
	return 0;
}

int main(){
	List list;
	MAP map;
	Player a;
	int Found, flag = 0, setup, s1, s2;
	s1 = time();
	Print_KenKen();
	Sound(1);
	system("cls");
	setup = Level(&list, &map);
	Sound(2);
	Found = KT_Frame(list, map);
	while(Found != 1){
		int x, i, j;
		SetUp(setup);
		printf("\t\t\t\t\t\t\t\tCHON SO DE NHAP VAO O: ");
		scanf("%d",&x);
		if(x == 0)
			break;
		else{
			printf("\t\t\t\t\t\t\t\tVI TRI CAN DUA(cach nhau boi khoang trang): ");
			scanf("%d %d", &i, &j);
		}
		pourFrame(x, i, j, list, &map);
		if(Duyet_TT(i, j, x, list, map)){
			Color(1);
			system("cls");
			Print_KenKen();
			PrintMap(list, map);
			Sound(4);
			Found = KT_Frame(list, map);
			flag = 1;
		}
		else{
			Color(2);
			system("cls");
			Print_KenKen();
			PrintMap(list, map);
			Sound(3);
			Found = KT_Frame(list, map);
			flag = 0;
		}
		if(Found==1 && flag == 1)
			Found = 0;
	}
	if(KT_Frame(list, map)){
		system("cls");
		Print_KenKen();
		printf("\n\n\n");
		Print_You_Win();
		s2 = time();
		Sound(5);
		a = Nhap_Player(s2 - s1);
		Save_PLayer(a);
	} 
	else{
		system("cls");
		Print_KenKen();
		printf("\n\n\n");
		Print_You_Lose();
		Sound(6);
	}
	return 0;
}

