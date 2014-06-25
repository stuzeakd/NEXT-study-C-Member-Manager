/******************************************************/
/* NHNNEXT Programming Practice Final Assignment      */
/* ID   : 141011                                      */
/* Name : Kim Deok Seong                              */
/* File : main.c                                      */
/* Member Manager                                     */
/******************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"
#include "BST.h"
#include "UI.h"
#define BUF 255

enum mainOption { PRINT, REGISTER, DEL, EDIT, SEARCH, SAVE, QUIT };


int main(void){
	BST member = BST_create();
	FILE *dataFile;
	enum mainOption state = PRINT;
	dataFile = fopen("data.txt", "rt");
	if (dataFile == NULL){
		fprintf(stderr, "\n\t\t\t- 파일을 찾을 수 없습니다. -\n\n");
		getchar();
		return -1;
	}
	getMember(member, dataFile);

	while (state != QUIT){
		state = (enum mainOption)startMessage((int)state);

		switch (state){
		case PRINT:
			printMember(member);
			break;

		case REGISTER:
			registerMember(member);
			break;

		case DEL:
			deleteMember(member);
			break;

		case EDIT:
			editMember(member);
			break;

		case SEARCH:
			searchMember(member);
			break;

		case SAVE:
			saveMember(member);
			break;

		case QUIT:
			quitMember(member);
			break;

		default:
			wrongMessage();

		}
	}
	return 0;
}