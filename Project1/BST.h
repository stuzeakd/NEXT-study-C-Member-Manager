/******************************************************/
/* NHNNEXT Programming Practice Final Assignment      */
/* ID   : 141011                                      */
/* Name : Kim Deok Seong                              */
/* File : BST.h                                       */
/* Member Manager                                     */
/******************************************************/

#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BSTnode.h"

struct bst{
	Node *root;
};
typedef struct bst * BST;

BST		BST_create(void);
void	BST_free(BST oBST);

void	BST_insert(BST oBST, void *pvValue);
void	BST_replace(BST oBST, int iKey, int *compare(void *pvValue, char *pcData), char *pcData);
void	BST_remove(BST oBST, int iKey);
void	BST_get(BST oBST, int iKey);
Node*	BST_search_key(BST oBST, int iKey);
void	BST_search_value(BST oBST, Node *nodearr[], int *compare(void *pvValue, char *pcData), char *pcData);
void	BST_map(BST oBST, void(*pfApply)(void *pvValue, void *pvExtra, FILE *fp), void *pvExtra, FILE *fp);


#endif __BST_H__
