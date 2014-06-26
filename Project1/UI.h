

#ifndef __UI_H__
#define __UI_H__

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "BSTnode.h"


//#define WIDTH "================================================================================"
#define WIDTHUP		"    ┌────┬────┬────┬────┬────┬────┬────┐   "
#define WIDTHDOWN	"    └────┴────┴────┴────┴────┴────┴────┘   "

#define SHAPE_HORIZCURSOR		"▲"
#define SHAPE_VERTICURSOR		"▶"

#define REGIMENU_0				"ID"
#define REGIMENU_1				"이름"
#define REGIMENU_2				"주소"
#define REGIMENU_3				"전화번호"

#define SUBMENU_1				"ID"
#define SUBMENU_2				"이름"
#define SUBMENU_3				"전화번호"
#define SUBMENU_4				"취소"

#define SUBMENU_EDIT_0			"회원ID"
#define SUBMENU_EDIT_1			"회원이름"
#define SUBMENU_EDIT_2			"회원주소"
#define SUBMENU_EDIT_3			"회원전화번호"
#define SUBMENU_EDIT_4			"수정취소"

#define ENDMENU_1				"예"
#define ENDMENU_2				"아니오"

#define ERASE					"              "

#define SPACE_BETWEEN_CURSOR	4
#define SPACE_BETWEEN_REGISTER_EACHVALUEDATA 2

#define SPACE_BETWEEN_EDIT_EACHVALUEDATA 2
#define SPACE_BETWEEN_EDIT_EACHVALUES 3
#define SPACE_BETWEEN_END_MENU	10

#define INDENT_EACHVALUES		3
#define INDENT_EACHVALUEDATA	3

#define SPACE_BETWEEN_SEARCH_BAR 3


#define SUBMENU_TEXT_X_POS		8
#define SUBMENU_TEXT_Y_POS		5
#define SUBMENU_CURSOR_X_POS	5
#define SUBMENU_MAIN_X_POS		30
#define SUBMENU_MAIN_Y_POS		5

#define REGISTER_X_POS		20
#define REGISTER_Y_POS		5
#define END_X_POS			
#define END_Y_POS			7

#define VERTIMOVE_REGI		4
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
#define MENUSIZE_END		2

#define FORM_PRINT_SELECTED_VALUES_1 "%d | %-10s | %-15s"
#define FORM_PRINT_SELECTED_VALUES_2 "%-35s"

#define MESSAGE_REGISTERFINISH		"등록되었습니다. <ENTER>"
#define MESSAGE_REMOVEFINISH		"삭제되었습니다. <ENTER>"
#define MESSAGE_SAVE				"저장되었습니다. <ENTER>"
#define MESSAGE_END_BEFORE_SAVE		"저장하고 종료하시겠습니까?"
#define MESSAGE_BYE					"BYE~"
#define MESSAGE_MISMATCH			"We Could't Find it <ENTER>"
#define MESSAGE_INVALIDINPUT		"Not good Input. Try again <Enter>"

typedef struct point{
	int x;
	int y;
}Point;
void gotoxy(Point pos);
int cursorPosHoriz(Point std, int range, int interval, int cursorPos);
int cursorPosVerti(Point std, int range, int interval);
void printWithSpace(int num, char *str);
void printCenter(char *str);

void printSearchResult(Value* selectedValues[], int selectedValuesSize);
int selectValueMessage(selectedValues, selectedValuesSize);
int editValueMessage(void* selectedValue, int state);
void editForm(int state);

void	mainMenu(int select);
int		startMessage(int state);
void	wrongMessage();

void	getMessage();
void	printMessage();
void	registerMessage();
int		deleteMessage(int state);
int		editMessage(int state);
int		searchMessage(int state);
void	saveMessage();
int		quitMessage();

void mismatchmMessage();
void invalidInputMessage();
void registerFinishMessage();
void removeFinishMessage();


#endif