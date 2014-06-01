#include "UI.h"

char *mainOptionStr[] = {
	"  보기  "
	, "  등록  "
	, "  삭제  "
	, "  수정  "
	, "  검색  "
	, "  저장  "
	, "  종료  "
};

void gotoxy(Point pos){
	COORD Cur;
	Cur.X = pos.x;
	Cur.Y = pos.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

}
int cursorPos(Point std, int range){
	int opt = 0;
	char ch = 0;
	Point pos = { std.x, std.y };

	while (ch != '\r'){
		gotoxy(pos);
		printf("->");
		ch = _getch();
		if (ch == -32){
			ch = _getch();
		}
		if (ch == 72 || ch == 80){
			gotoxy(pos);
			printf("  ");
		}
		if (ch == 72 && pos.y > std.y){
			pos.y--;
			opt--;
		}
		else if (ch == 80 && pos.y < std.y + range){
			pos.y++;
			opt++;
		}
	}
	return opt;
}
int cursorPosVerti(Point std, int range){
	int opt = 0;
	char ch = 0;
	Point pos = { std.x, std.y };

	while (ch != '\r'){
		gotoxy(pos);
		printf("▲");
		ch = _getch();
		if (ch == -32){
			ch = _getch();
		}
		if (ch == 75 || ch == 77){
			gotoxy(pos);
			printf("  ");
		}
		if (ch == 75 && pos.x > std.x){
			pos.x = pos.x - 10;
			opt--;
		}
		else if (ch == 77 && pos.x < std.x + range*10){
			pos.x = pos.x +10;
			opt++;
		}
	}
	return opt;
}
void printWithSpace(int num, char *str){
	int i;
	for (i = 0; i < num; i++){
		printf(" ");
	}
	printf(str);
}
void printCenter(char *str){
	int i;
	printWithSpace((strlen(WIDTHUP) - strlen(str)) / 2, "");
	printf(str);
	printf("\n");
}

void mainMenu(int select){
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	Point pos = { 6, 1 };
	int i;
	GetConsoleScreenBufferInfo(hC, &csbi);


	printf(WIDTHUP);
	printf("\n    │        │        │        │        │        │        │        │   \n");
	printf(WIDTHDOWN);

	SetConsoleTextAttribute(hC, 14);
	for (i = 0; i < 7; i++){
		gotoxy(pos);
		pos.x = pos.x + 10;
		printf("%s", mainOptionStr[i]);
	}

	SetConsoleTextAttribute(hC, 31);
	if (select != 0){
		pos.x = 6 + (select-1) * 10;
		gotoxy(pos);
		printf("%s", mainOptionStr[select - 1 ]);

	}
	SetConsoleTextAttribute(hC, 7);
	pos.x = 6;
	pos.y = 4;
	gotoxy(pos);
}






/************************************************************************/
/* Start Message                                                        */
/*                                                                      */
/* Give a message and options to user                                   */
/************************************************************************/
int startMessage(){
	Point pos = { 9, 4 };
	int opt;
	system("cls");
	mainMenu(0);
/*
	printWithSpace(30, "1. 보기\n");
	printWithSpace(30, "2. 등록\n");
	printWithSpace(30, "3. 삭제\n");
	printWithSpace(30, "4. 수정\n");
	printWithSpace(30, "5. 검색\n");
	printWithSpace(30, "6. 저장\n");
	printWithSpace(30, "7. 종료\n");
*/
	opt = cursorPosVerti(pos, 6);
	return opt;
}

/************************************************************************/
/* Wrong Message                                                        */
/*                                                                      */
/* Notice user choose wrong option                                      */
/************************************************************************/
void wrongMessage(){
	system("cls");
	printf(WIDTHUP);
	printf("\n\n");
	printCenter("잘못된 옵션입니다.");
}

void getMessage(){
	system("cls");

}
void printMessage(){
	system("cls");
	mainMenu(1);


}
void registerMessage(){
	system("cls");
	mainMenu(2);

}
void deleteMessage(){
	system("cls");
	mainMenu(3);

}
void editMessage(){
	system("cls");
	mainMenu(4);

}
void searchMessage(){
	system("cls");
	mainMenu(5);

}
void saveMessage(){
	system("cls");
	mainMenu(6);

}
void quitMessage(){
	system("cls");
	mainMenu(7);
	printCenter("Thanks");

}
