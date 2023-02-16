#include <D:\thay thuc\Game\KenKen\thuvien\List_Player.c>

void Save_PLayer(int s){
	ListPlay L;
	Player a;
	MakeNull_List(&L);
	char fname[] = { "DanhSachPlayer_test.txt" };
	char name[6];
	Read_File(&L, fname);
	printf("NHAP TEN DE LUU KET QUA(Toi da 5 ki tu): ");
	fgets(name, 6, stdin);
	int len = strlen(name);
	if(name[len - 1] == '\n')
		name[len - 1] = '\0';
	a.Name = strdup(name);
	a.Num_sec = s;
	Insert_List(a, &L);
	system("cls");
//	Print_KenKen();
	Print_List(L);
	Write_File(L, fname);	
}

int main(){
	ListPlay L;
	Player a, b;
	Save_PLayer(44);
	return 0;
}






