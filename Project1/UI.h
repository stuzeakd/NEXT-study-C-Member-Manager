

#ifndef __UI_H__
#define __UI_H__

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

//#define WIDTH "================================================================================"
#define WIDTHUP		"    ┌────┬────┬────┬────┬────┬────┬────┐   "
#define WIDTHDOWN	"    └────┴────┴────┴────┴────┴────┴────┘   "

#define SHAPE_HORIZCURSOR		"▲"
#define SHAPE_VERTICURSOR		"▶"

#define SUBMENU_1				"ID"
#define SUBMENU_2				"주소"
#define SUBMENU_3				"전화번호"
#define SUBMENU_4				"취소"

#define SUBMENU_EDIT_0			"회원ID"
#define SUBMENU_EDIT_1			"회원이름"
#define SUBMENU_EDIT_2			"회원주소"
#define SUBMENU_EDIT_3			"회원전화번호"
#define SUBMENU_EDIT_4			"수정취소"

#define ERASE					"               "

#define SPACE_BETWEEN_CURSOR	4
#define SPACE_BETWEEN_EDIT_EACHVALUE 2
#define SPACE_BETWEEN_EDIT_EACHVALUE_INDENT 3


#define SUBMENU_TEXT_X_POS		8
#define SUBMENU_TEXT_Y_POS		5
#define SUBMENU_CURSOR_X_POS	5
#define SUBMENU_MAIN_X_POS		30
#define SUBMENU_MAIN_Y_POS		5

#define HORIZMOVE_START		10
#define VERTIMOVE_DELETE	2
#define VERTIMOVE_EDIT		2
#define VERTIMOVE_SEARCH	2
#define VERTIMOVE_EDITMAIN	4

#define MENUSIZE_START		7
#define MENUSIZE_DELETE		4
#define MENUSIZE_EDIT		4
#define MENUSIZE_SEARCH		4
#define MENUSIZE_EDITMAIN	4


typedef struct point{
	int x;
	int y;
}Point;
void gotoxy(Point pos);
int cursorPosHoriz(Point std, int range, int interval, int cursorPos);
int cursorPosVerti(Point std, int range, int interval);
void printWithSpace(int num, char *str);
void printCenter(char *str);


void mainMenu(int select);
int startMessage(int state);
void wrongMessage();
void getMessage();
void printMessage();
void registerMessage();
int deleteMessage(int state);
int editValueMessage(void* selectedValue, int state);
void editForm(int state);
int editMessage(int state);
int searchMessage(int state);
void saveMessage();
void quitMessage();

void mismatchmMessage();
void invalidInput();

#endif