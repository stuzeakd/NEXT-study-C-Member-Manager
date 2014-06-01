

#ifndef __UI_H__
#define __UI_H__

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

//#define WIDTH "================================================================================"
#define WIDTHUP "    ������������������������������������������������������������������������   "
#define WIDTHDOWN "    ������������������������������������������������������������������������   "
typedef struct point{
	int x;
	int y;
}Point;
void gotoxy(Point pos);
int cursorPos(Point std, int range);
void printWithSpace(int num, char *str);
void printCenter(char *str);


void mainMenu(int select);
int startMessage();
void wrongMessage();
void getMessage();
void printMessage();
void registerMessage();
void deleteMessage();
void editMessage();
void searchMessage();
void saveMessage();
void quitMessage();


#endif