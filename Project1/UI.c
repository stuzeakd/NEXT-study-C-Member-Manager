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
int animationSleep(int xPos){
	return (xPos - 35)*(xPos - 35)/ 150;
}
//세로로 이동하는 Cursor로 메뉴 선택후 위치에 해당하는 option 리턴.
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
//가로로 이동하는 Cursor로 메뉴 선택후 위치에 해당하는 option 리턴.
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

//상단 메인 메뉴바.
void mainMenu(int select){
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	Point pos = { 0,0 };
	int i;
	GetConsoleScreenBufferInfo(hC, &csbi);

	gotoxy(pos);
	printf(WIDTHUP);
	printf("\n    │        │        │        │        │        │        │        │   \n");
	printf(WIDTHDOWN);

	pos.x = 6; pos.y = 1;
	SetConsoleTextAttribute(hC, 14);
	for (i = 0; i < 7; i++){
		gotoxy(pos);
		pos.x = pos.x + HORIZMOVE_START;
		printf("%s", mainOptionStr[i]);
	}

	SetConsoleTextAttribute(hC, 31);
	if (select != 0){
		pos.x = 6 + (select - 1) * HORIZMOVE_START;
		gotoxy(pos);
		printf("%s", mainOptionStr[select - 1]);

	}
	SetConsoleTextAttribute(hC, 7);
	pos.x = 6;
	pos.y = 4;
	gotoxy(pos);
}

//Form에 맞춰 Value Data출력
void printSelectedValue(Point pos, Value *selectedValues[], int selectedValuesSize){
	int i;
	for (i = 0; i < selectedValuesSize; i++){
		gotoxy(pos); printf(FORM_PRINT_SELECTED_VALUES_1, selectedValues[i]->key, selectedValues[i]->name, selectedValues[i]->phone);
		pos.y++; 
		gotoxy(pos); printf(FORM_PRINT_SELECTED_VALUES_2, selectedValues[i]->address);
		pos.y += SPACE_BETWEEN_EDIT_EACHVALUES - 1;
	}
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
	printf("학번 | 이름    |               주소                 | 전화번호\n");

}
void registerForm(int state){
	//해당 Value Data 위치를 비워준후 커서를 맨앞으로 이동.
	Point pos = { REGISTER_X_POS+INDENT_EACHVALUEDATA, REGISTER_Y_POS
		+ state*VERTIMOVE_REGI + SPACE_BETWEEN_REGISTER_EACHVALUEDATA };
	gotoxy(pos); printf(ERASE); printf(ERASE); printf(ERASE);
	gotoxy(pos);
}
void registerMessage(){
	Point pos = { REGISTER_X_POS, REGISTER_Y_POS };
	system("cls");
	mainMenu(2);
	printf("학생데이터를 입력하세요");
	gotoxy(pos); printf(REGIMENU_0);
	pos.y += VERTIMOVE_REGI; gotoxy(pos); printf(REGIMENU_1);
	pos.y += VERTIMOVE_REGI; gotoxy(pos); printf(REGIMENU_2);
	pos.y += VERTIMOVE_REGI; gotoxy(pos); printf(REGIMENU_3);
	pos.x += INDENT_EACHVALUEDATA; pos.y = REGISTER_Y_POS + SPACE_BETWEEN_REGISTER_EACHVALUEDATA;
	gotoxy(pos);
	


}
int selectValueMessage(Value *selectedValues[], int selectedValuesSize){
	int i;
	int selectedValueNum;
	Point pos = { SUBMENU_MAIN_X_POS + INDENT_EACHVALUES, SUBMENU_MAIN_Y_POS + SPACE_BETWEEN_SEARCH_BAR };
	
	//각 Value들을 출력
	printSelectedValue(pos, selectedValues, selectedValuesSize);
	
	//Cursor 시작
	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS + SPACE_BETWEEN_SEARCH_BAR;
	selectedValueNum = cursorPosVerti(pos, selectedValuesSize, SPACE_BETWEEN_EDIT_EACHVALUES, 0);

	//맨위로 되돌아가서 ERASE.
	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS + SPACE_BETWEEN_SEARCH_BAR;
	
	for (i = 0; i < selectedValuesSize*SPACE_BETWEEN_EDIT_EACHVALUES; i++){
		gotoxy(pos);
		printf(ERASE); printf(ERASE); printf(ERASE);
		pos.y += 1;
	}


	return selectedValueNum;
}

int deleteMessage(int state){
	Point pos = { SUBMENU_TEXT_X_POS, SUBMENU_TEXT_Y_POS };
	system("cls");
	mainMenu(3);
	//각 서브메뉴 출력 (ID, 이름, 전화번호, 취소)
	gotoxy(pos); printf(SUBMENU_1);
	pos.y += VERTIMOVE_DELETE;
	gotoxy(pos); printf(SUBMENU_2);
	pos.y += VERTIMOVE_DELETE;
	gotoxy(pos); printf(SUBMENU_3);
	pos.y += VERTIMOVE_DELETE;
	gotoxy(pos); printf(SUBMENU_4);

	//Cursor 시작
	pos.x -= SUBMENU_TEXT_X_POS - SUBMENU_CURSOR_X_POS;
	pos.y -= (MENUSIZE_DELETE - 1) * VERTIMOVE_DELETE;

	state = cursorPosVerti(pos, MENUSIZE_DELETE, VERTIMOVE_DELETE, state);

	//맨위로 복귀후 종료
	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS;
	gotoxy(pos);

	return state;

}
int editValueMessage(void* selectedValue, int state){
	Point pos = { SUBMENU_MAIN_X_POS, SUBMENU_MAIN_Y_POS };

	//ID출력
	gotoxy(pos); printf(ERASE);
	gotoxy(pos); printf(SUBMENU_EDIT_0);
	pos.y += SPACE_BETWEEN_EDIT_EACHVALUEDATA;
	pos.x += INDENT_EACHVALUEDATA;
	gotoxy(pos); printf("%d", ((Value*)selectedValue)->key);
	pos.y += VERTIMOVE_EDITMAIN - SPACE_BETWEEN_EDIT_EACHVALUEDATA;
	pos.x -= INDENT_EACHVALUEDATA;
	//이름출력
	gotoxy(pos); printf(SUBMENU_EDIT_1);
	pos.y += SPACE_BETWEEN_EDIT_EACHVALUEDATA;
	pos.x += INDENT_EACHVALUEDATA;
	gotoxy(pos); printf("%s", ((Value*)selectedValue)->name);
	pos.y += VERTIMOVE_EDITMAIN - SPACE_BETWEEN_EDIT_EACHVALUEDATA;
	pos.x -= INDENT_EACHVALUEDATA;
	//주소출력
	gotoxy(pos); printf(SUBMENU_EDIT_2);
	pos.y += SPACE_BETWEEN_EDIT_EACHVALUEDATA;
	pos.x += INDENT_EACHVALUEDATA;
	gotoxy(pos); printf("%s", ((Value*)selectedValue)->address);
	pos.y += VERTIMOVE_EDITMAIN - SPACE_BETWEEN_EDIT_EACHVALUEDATA;
	pos.x -= INDENT_EACHVALUEDATA;
	//전화번호출력
	gotoxy(pos); printf(SUBMENU_EDIT_3);
	pos.y += SPACE_BETWEEN_EDIT_EACHVALUEDATA;
	pos.x += INDENT_EACHVALUEDATA;
	gotoxy(pos); printf("%s", ((Value*)selectedValue)->phone);
	pos.y += VERTIMOVE_EDITMAIN - SPACE_BETWEEN_EDIT_EACHVALUEDATA;
	pos.x -= INDENT_EACHVALUEDATA;
	//취소출력
	gotoxy(pos); printf(SUBMENU_EDIT_4);

	//Cursor 시작
	pos.x -= SPACE_BETWEEN_CURSOR;
	pos.y -= (MENUSIZE_EDITMAIN-1) * VERTIMOVE_EDITMAIN;
	state = cursorPosVerti(pos, MENUSIZE_EDITMAIN, VERTIMOVE_EDITMAIN, state);

	//시작점으로 올라간후 리턴.
	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS;
	gotoxy(pos);

	return state;
}
void editForm(int state){
	//해당 Value Data 위치를 비워준후 커서를 맨앞으로 이동.
	Point pos = { SUBMENU_MAIN_X_POS + INDENT_EACHVALUEDATA, SUBMENU_MAIN_Y_POS
		+ (state + 1) * VERTIMOVE_EDITMAIN + SPACE_BETWEEN_EDIT_EACHVALUEDATA };
	gotoxy(pos); printf(ERASE); printf(ERASE); printf(ERASE);
	gotoxy(pos);
}
int editMessage(int state){
	Point pos = { SUBMENU_TEXT_X_POS, SUBMENU_TEXT_Y_POS };
	system("cls");
	mainMenu(4);

	//메뉴 출력 (ID, 이름, 전화번호, 취소)
	gotoxy(pos); printf(SUBMENU_1);
	pos.y += VERTIMOVE_EDIT;
	gotoxy(pos); printf(SUBMENU_2);
	pos.y += VERTIMOVE_EDIT;
	gotoxy(pos); printf(SUBMENU_3);
	pos.y += VERTIMOVE_EDIT;
	gotoxy(pos); printf(SUBMENU_4);

	//Cursor 시작
	pos.x -= SUBMENU_TEXT_X_POS - SUBMENU_CURSOR_X_POS;
	pos.y -= (MENUSIZE_EDIT - 1) * VERTIMOVE_EDIT;
	state = cursorPosVerti(pos, MENUSIZE_EDIT, VERTIMOVE_EDIT, state);

	//맨위로 올린후 리턴.
	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS;
	gotoxy(pos);

	return state;
}
void printSearchResult(Value* selectedValues[], int selectedValuesSize){
	Point pos = { SUBMENU_MAIN_X_POS, SUBMENU_MAIN_Y_POS + SPACE_BETWEEN_SEARCH_BAR};
	printSelectedValue(pos, selectedValues, selectedValuesSize);
	getchar();
}
int searchMessage(int state){
	Point pos = { SUBMENU_TEXT_X_POS, SUBMENU_TEXT_Y_POS };
	system("cls");
	mainMenu(5);

	//메뉴 출력 (ID, 이름, 전화번호, 취소)
	gotoxy(pos); printf(SUBMENU_1);
	pos.y += VERTIMOVE_SEARCH;
	gotoxy(pos); printf(SUBMENU_2);
	pos.y += VERTIMOVE_SEARCH;
	gotoxy(pos); printf(SUBMENU_3);
	pos.y += VERTIMOVE_SEARCH;
	gotoxy(pos); printf(SUBMENU_4);

	//Cursor 시작
	pos.x -= SUBMENU_TEXT_X_POS - SUBMENU_CURSOR_X_POS;
	pos.y -= (MENUSIZE_SEARCH - 1) * VERTIMOVE_SEARCH;
	state = cursorPosVerti(pos, MENUSIZE_SEARCH, VERTIMOVE_SEARCH, state);

	//맨위로 올린후 리턴.
	pos.x = SUBMENU_MAIN_X_POS;
	pos.y = SUBMENU_MAIN_Y_POS;
	gotoxy(pos);

	return state;
}
void saveMessage(){


	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hC, &csbi);
	Point pos = { 0, 22 };
	int i;
	mainMenu(6);
	SetConsoleTextAttribute(hC, 177);
	gotoxy(pos); for (i = 0; i <= strlen(WIDTHUP); i++){
		Sleep(animationSleep(i));
		printf(" ");
	}
	pos.x = (strlen(WIDTHUP) - strlen(MESSAGE_SAVE)) / 2; gotoxy(pos); printf(MESSAGE_SAVE);
	SetConsoleTextAttribute(hC, 7);
	getchar();


}
int quitMessage(){
	Point pos = {(strlen(WIDTHUP) - strlen(MESSAGE_END_BEFORE_SAVE))/2, END_Y_POS};
	int state;
	system("cls");
	mainMenu(7);

	gotoxy(pos); printf(MESSAGE_END_BEFORE_SAVE);
	pos.y += 2; 
	

	pos.x = (strlen(WIDTHUP)  + SPACE_BETWEEN_END_MENU - strlen(ENDMENU_2) -2) / 2; gotoxy(pos);
	printf(ENDMENU_2);
	pos.x = strlen(WIDTHUP) / 2 - strlen(ENDMENU_1) - SPACE_BETWEEN_END_MENU / 2; gotoxy(pos);
	printf(ENDMENU_1);

	pos.y++;
	state = cursorPosHoriz(pos, MENUSIZE_END, SPACE_BETWEEN_END_MENU, 0);

	return state;
}

void mismatchmMessage(){
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hC, &csbi);
	Point pos = { 0, 23 };
	int i;
	SetConsoleTextAttribute(hC, 199);
	gotoxy(pos); for (i = 0; i <= strlen(WIDTHUP); i++){
		Sleep(animationSleep(i));  printf(" ");
	}
	pos.x = (strlen(WIDTHUP) - strlen(MESSAGE_MISMATCH)) / 2; gotoxy(pos); printf(MESSAGE_MISMATCH);
	SetConsoleTextAttribute(hC, 7);
	getchar();
}
void invalidInputMessage(){
	printf(MESSAGE_INVALIDINPUT);
	getchar();
}
void byeMessage(){
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hC, &csbi);
	Point pos = { 0, 23 };
	int i;

	SetConsoleTextAttribute(hC, 241);
	gotoxy(pos); for (i = 0; i <= strlen(WIDTHUP); i++){
		Sleep( animationSleep(i) );
		printf(" ");
	}
	pos.x = (strlen(WIDTHUP) - strlen(MESSAGE_BYE)) / 2; gotoxy(pos); printf(MESSAGE_BYE);
	SetConsoleTextAttribute(hC, 7);
}
void registerFinishMessage(){
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hC, &csbi);
	Point pos = { 0, 23 };
	int i;

	SetConsoleTextAttribute(hC, 151);
	gotoxy(pos); for (i = 0; i <= strlen(WIDTHUP); i++){
		Sleep(animationSleep(i));
		printf(" ");
	}
	pos.x = (strlen(WIDTHUP) - strlen(MESSAGE_REGISTERFINISH)) / 2; gotoxy(pos); printf(MESSAGE_REGISTERFINISH);
	SetConsoleTextAttribute(hC, 7);
	getchar();
}

void removeFinishMessage(){
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hC, &csbi);
	Point pos = { 0, 23 };
	int i;

	SetConsoleTextAttribute(hC, 132);
	gotoxy(pos); for (i = 0; i <= strlen(WIDTHUP); i++){
		Sleep(animationSleep(i));
		printf(" ");
	}
	pos.x = (strlen(WIDTHUP) - strlen(MESSAGE_REMOVEFINISH)) / 2; gotoxy(pos); printf(MESSAGE_REMOVEFINISH);
	SetConsoleTextAttribute(hC, 7);
	getchar();
}