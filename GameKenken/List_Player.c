#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	char *Name;
	int Num_sec;
}Player;

typedef struct Node{
	Player Element;
	struct Node* Next;
}Node;

typedef Node* Position;
typedef Position ListPlay;

void MakeNull_List(ListPlay *L){
	(*L) = (Node*)malloc(sizeof(Node));
	(*L)->Next = NULL;	
}

int Empty_List(ListPlay L){
	return L->Next==NULL;	
}

Position First(ListPlay L){
	return L;	
}	


void Insert_List(Player x, ListPlay *L){
	Position p = First(*L);
	Position tmp;
	tmp = (Node*)malloc(sizeof(Node));
	tmp->Element = x;
	while(p->Next != NULL){
		if(p->Next->Element.Num_sec >= x.Num_sec){
			tmp->Next = p;
			break;
		}
		else
			p = p->Next;
	}
	tmp->Next = p->Next;
	p->Next = tmp;	
}

void sort(ListPlay *L){
	Position p = First(*L);
	while(p->Next != NULL){
		Position q = p->Next;
		while(q->Next != NULL){
			if(p->Next->Element.Num_sec > q->Next->Element.Num_sec){
				Player tmp = p->Next->Element;
				p->Next->Element = q->Next->Element;
				q->Next->Element = tmp;
			}
			q = q->Next;
		}
		p = p->Next;
	}
}

int count(ListPlay L){
	Position p = First(L);
	int count = 0;
	while(p->Next != NULL){
		count++;
		p = p->Next;
	}
	return count;	
}

void Print_List(ListPlay L){
	Position p = First(L);
	int i= 1;
	printf("\t\t\t\t\t\t\t\t        ===&&===| Bang Xep Hang |===&&===\n\n");
	printf("\t\t\t\t\t\t\t\tXepHang\t     TenNguoichoi\t  Tongthoigianchoi\n");
	while(p->Next != NULL){
		if(p->Next->Element.Num_sec >= 60){
			printf("\t\t\t\t\t\t\t\t  %d \t\t%s\t\t\t%dm%ds\n", i, p->Next->Element.Name, p->Next->Element.Num_sec/60, p->Next->Element.Num_sec%60);
			p = p->Next;
			i++;
		}
		else{
			printf("\t\t\t\t\t\t\t\t  %d \t\t%s\t\t\t%ds\n", i, p->Next->Element.Name, p->Next->Element.Num_sec);
			p = p->Next;
			i++;
		}
	}	
}

void Write_File(ListPlay L, char fname[]){
	FILE *file = fopen(fname, "w");
	fprintf(file, "%d\n", count(L));
	Position p = First(L);
	while(p->Next != NULL){
		fprintf(file, "%s", p->Next->Element.Name);
		fprintf(file, "\n%d\n", p->Next->Element.Num_sec);	
		p = p->Next;
	}	
	fclose(file);
}

void Read_File(ListPlay *L, char fname[]){
	FILE *file = fopen(fname, "r");
	int n, i;
	Player a;
	char Name_tmp[6];
	fscanf(file, "%d\n", &n);
	if(n==0)
		return;
	else{
		for(i=0;i<n;i++){
			fgets(Name_tmp, 6, file);
			int len = strlen(Name_tmp);
			if(Name_tmp[len - 1] == '\n')
				Name_tmp[len - 1] = '\0';
			a.Name = strdup(Name_tmp);
			fscanf(file, "\n");
			fscanf(file, " %d\n", &a.Num_sec);
			Insert_List(a, L);		
		}	
	}
	fclose(file);	
}


