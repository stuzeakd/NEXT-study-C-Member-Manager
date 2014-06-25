/******************************************************/
/* NHNNEXT Programming Practice Final Assignment      */
/* ID   : 141011                                      */
/* Name : Kim Deok Seong                              */
/* File : BSTsub.c                                    */
/* Member Manager                                     */
/******************************************************/

#include <stdio.h>
#include "BSTnode.h"

Node* rightMostNode(Node *node){
	Node *temp;

	for (temp = node; temp->rightchild != NULL; temp = temp->rightchild){
		printf("%d %s\n", temp->value->key, temp->value->name);
	}

	return temp;
}

void freeNode(Node *node){
	if (node != NULL){
		freeNode(node->leftchild);
		freeNode(node->rightchild);
		free(node);
	}
}

void insertNode(Node **node, void *pvValue){
	Value *pValue;
	if (*node == NULL){
		*node = (Node*)malloc(sizeof(Node));
		(*node)->value = (Value*)pvValue;
		(*node)->leftchild = NULL;
		(*node)->rightchild = NULL;
	}
	else{
		pValue = (Value*)pvValue;
		if ((*node)->value->key > pValue->key) insertNode(&((*node)->leftchild), pvValue);
		else insertNode(&((*node)->rightchild), pvValue);
	}
}
void* getValueFromNode(Node* node, int iKey){
	if (!node) return NULL;
	if (node->value->key == iKey) return node->value;
	else if (node->value->key > iKey) return getValueFromNode(node->leftchild, iKey);
	else return getValueFromNode(node->rightchild, iKey);
}

Node* searchNodeKey(Node *node, int iKey){
	if (!node) return NULL;
	if (node->value->key == iKey) return node;
	else if (node->value->key > iKey) return searchNodeKey(node->leftchild, iKey);
	else return searchNodeKey(node->rightchild, iKey);
}

void searchNodeValue(Node *node, Node* nodearr[], int *nodearrSize,int *compare(void* pvValue, char* pcData), char* pcData){
	if (node == NULL) return;
	
	if (node->leftchild != NULL)
		searchNodeValue(node->leftchild, nodearr, nodearrSize, compare, pcData);
	if (!compare(node->value, pcData)) nodearr[*nodearrSize++] = node;
	if (node->rightchild != NULL)
		searchNodeValue(node->rightchild, nodearr, nodearrSize, compare, pcData);

}

void mapNode(Node *node, void(*pfApply)(void *pvValue, void *pvExtra, FILE *fp), void *pvExtra, FILE *fp){
	if (node == NULL) return;
	if (node->leftchild != NULL)
		mapNode(node->leftchild, pfApply, pvExtra, fp);
	pfApply(node->value, pvExtra, fp);
	if (node->rightchild != NULL)
		mapNode(node->rightchild, pfApply, pvExtra, fp);
}