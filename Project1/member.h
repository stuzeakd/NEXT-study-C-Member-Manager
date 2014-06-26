/******************************************************/
/* NHNNEXT Programming Practice Final Assignment      */
/* ID   : 141011                                      */
/* Name : Kim Deok Seong                              */
/* File : member.h                                    */
/* Member Manager                                     */
/******************************************************/

#ifndef __MEMBER_H__
#define __MEMBER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "BST.h"

#define BUF 35
#define FILEBUF 255
#define PRINTFORM "    %d | %-8s| %-35s| %-15s\n"
#define SAVEFORM "%d\t%s\t%s\t%s\n"

void getMember(BST oBST, FILE *dataFile);
void printMember(BST oBST);
void registerMember(BST oBST);
void deleteMember(BST oBST);
void editMember(BST oBST);
void saveMember(BST oBST);
void searchMember(BST oBST);
void quitMember(BST oBST);


#endif 