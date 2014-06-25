#include "UI.h"
#include "BSTnode.h"

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
int cursorPosVerti(Point std, int range, int interval, int state){
	int opt = state;
	char ch = 0;
	Point pos = { std.x, std.y + state*interval };
	while (ch != '\r'){
		gotoxy(pos);
		printf(SHAPE_VERTICURSOR);
		ch = _getch();
		if (ch == -32){
			ch = _getch();
		}
		if (ch == 72 || ch == 80){
			gotoxy(pos);
			printf("  ");
		}
		if (ch == 72 && pos.y > std.y){
			pos.y = pos.y - interval;
			opt--;
		}
		else if (ch == 80 && pos.y < std.y + (range-1) * interval){
			pos.y = pos.y + interval;
			opt++;
		}
	}
	return opt;
}
int cursorPosHoriz(Point std, int range, int interval, int state){
	int opt = state;
	char ch = 0;
	Point pos = { std.x + state * interval, std.y };

	while (ch != '\r'){
		gotoxy(pos);
		printf(SHAPE_HORIZCURSOR);
		ch = _getch();
		if (ch == -32){
			ch = _getch();
		}
		
		if (ch == 75 || ch == 77){
			gotoxy(pos);
			printf("  ");
		}
		if (ch == 75 && pos.x > std.x){
			pos.x = pos.x - interval;
			opt--;
		}
		else if (ch == 77 && pos.x < std.x + (range-1)*interval){
			pos.x = pos.x + interval;
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
int startMessage(int state){
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
	opt = cursorPosHoriz(pos, MENUSIZE_START, HORIZMOVE_START, state);
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
	printCenter("SOMETHING WRONG.\n");
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
int deleteMessage(int state){
	Point pos = { SUBMENU_TEXT_X_POS, SUBMENU_TEXT_Y_POS };
	system("cls");
	mainMenu(3);
	
	gotoxy(pos); printf(SUBMENU_1);
	pos.y += VERTIMOVE_DELETE;
	gotoxy(pos); printf(SUBMENU_2);
	pos.y += VERTIMOVE_DELETE;
	gotoxy(pos); printf(SUBMENU_3);
	pos.y += VERTIMOVE_DELETE;
	gotoxy(pos); printf(SUBMENU_4);

	pos.x -= SUBMENU_TEXT_X_POS - SUBMENU_CURSOR_X_POS;
	pos.y -= (MENUSIZE_DELETE - 1) * VERTIMOVE_DELETE;

	state = cursorPosVerti(pos, MENUSIZE_DELETE, VERTIMOVE_DELETE, state);

	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS;
	gotoxy(pos);

	return state;

}
int editValueMessage(void* selectedValue, int state){
	Point pos = { SUBMENU_MAIN_X_POS, SUBMENU_MAIN_Y_POS };

	gotoxy(pos); printf(ERASE);
	gotoxy(pos); printf(SUBMENU_EDIT_0);
	pos.y += SPACE_BETWEEN_EDIT_EACHVALUE;
	pos.x += SPACE_BETWEEN_EDIT_EACHVALUE_INDENT;
	gotoxy(pos); printf("%d", ((Value*)selectedValue)->key);
	pos.y += VERTIMOVE_EDITMAIN - SPACE_BETWEEN_EDIT_EACHVALUE;
	pos.x -= SPACE_BETWEEN_EDIT_EACHVALUE_INDENT;
	gotoxy(pos); printf(SUBMENU_EDIT_1);
	pos.y += SPACE_BETWEEN_EDIT_EACHVALUE;
	pos.x += SPACE_BETWEEN_EDIT_EACHVALUE_INDENT;
	gotoxy(pos); printf("%s", ((Value*)selectedValue)->name);
	pos.y += VERTIMOVE_EDITMAIN - SPACE_BETWEEN_EDIT_EACHVALUE;
	pos.x -= SPACE_BETWEEN_EDIT_EACHVALUE_INDENT;
	gotoxy(pos); printf(SUBMENU_EDIT_2);
	pos.y += SPACE_BETWEEN_EDIT_EACHVALUE;
	pos.x += SPACE_BETWEEN_EDIT_EACHVALUE_INDENT;
	gotoxy(pos); printf("%s", ((Value*)selectedValue)->address);
	pos.y += VERTIMOVE_EDITMAIN - SPACE_BETWEEN_EDIT_EACHVALUE;
	pos.x -= SPACE_BETWEEN_EDIT_EACHVALUE_INDENT;
	gotoxy(pos); printf(SUBMENU_EDIT_3);
	pos.y += SPACE_BETWEEN_EDIT_EACHVALUE;
	pos.x += SPACE_BETWEEN_EDIT_EACHVALUE_INDENT;
	gotoxy(pos); printf("%s", ((Value*)selectedValue)->phone);
	pos.y += VERTIMOVE_EDITMAIN - SPACE_BETWEEN_EDIT_EACHVALUE;
	pos.x -= SPACE_BETWEEN_EDIT_EACHVALUE_INDENT;
	gotoxy(pos); printf(SUBMENU_EDIT_4);

	pos.x -= SPACE_BETWEEN_CURSOR;
	pos.y -= (MENUSIZE_EDITMAIN-1) * VERTIMOVE_EDITMAIN;

	state = cursorPosVerti(pos, MENUSIZE_EDITMAIN, VERTIMOVE_EDITMAIN, state);

	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS;
	gotoxy(pos);

	return state;
}
void editForm(int state){
	Point pos = { SUBMENU_MAIN_X_POS + SPACE_BETWEEN_EDIT_EACHVALUE_INDENT, SUBMENU_MAIN_Y_POS
		+ (state + 1) * VERTIMOVE_EDITMAIN + SPACE_BETWEEN_EDIT_EACHVALUE };
	gotoxy(pos); printf(ERASE); printf(ERASE); printf(ERASE);
	gotoxy(pos);
}
int editMessage(int state){
	Point pos = { SUBMENU_TEXT_X_POS, SUBMENU_TEXT_Y_POS };
	system("cls");
	mainMenu(4);

	gotoxy(pos); printf(SUBMENU_1);
	pos.y += VERTIMOVE_EDIT;
	gotoxy(pos); printf(SUBMENU_2);
	pos.y += VERTIMOVE_EDIT;
	gotoxy(pos); printf(SUBMENU_3);
	pos.y += VERTIMOVE_EDIT;
	gotoxy(pos); printf(SUBMENU_4);

	pos.x -= SUBMENU_TEXT_X_POS - SUBMENU_CURSOR_X_POS;
	pos.y -= (MENUSIZE_EDIT - 1) * VERTIMOVE_EDIT;

	state = cursorPosVerti(pos, MENUSIZE_EDIT, VERTIMOVE_EDIT, state);

	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS;
	gotoxy(pos);

	return state;
}
int searchMessage(int state){
	Point pos = { SUBMENU_TEXT_X_POS, SUBMENU_TEXT_Y_POS };
	system("cls");
	mainMenu(5);

	gotoxy(pos); printf(SUBMENU_1);
	pos.y += VERTIMOVE_SEARCH;
	gotoxy(pos); printf(SUBMENU_2);
	pos.y += VERTIMOVE_SEARCH;
	gotoxy(pos); printf(SUBMENU_3);
	pos.y += VERTIMOVE_SEARCH;
	gotoxy(pos); printf(SUBMENU_4);

	pos.x -= SUBMENU_TEXT_X_POS - SUBMENU_CURSOR_X_POS;
	pos.y -= (MENUSIZE_SEARCH - 1) * VERTIMOVE_SEARCH;


	state = cursorPosVerti(pos, MENUSIZE_SEARCH, VERTIMOVE_SEARCH, state);

	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS;
	gotoxy(pos);

	return state;
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

void mismatchmMessage(){

	printf("We can't find");
	getchar();
}
void invalidInput(){
	printf("Not good Input. Try again <Enter>");
	getchar();
}