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
	if (!node) return NULL;
	for (temp = node; temp->rightchild != NULL; temp = temp->rightchild){
		//printf("%d %s\n", temp->value->key, temp->value->name);
	}

	return temp;
}

void freeValue(Value* value){
	if (value != NULL){
		free(value->name);
		free(value->address);
		free(value->phone);
		free(value);
	}
}

void freeNode(Node *node){
	if (node != NULL){
		freeNode(node->leftchild);
		freeNode(node->rightchild);
		freeValue(node->value);
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
void removeNode(Node *node, int iKey){
	Node **tmpNode = NULL;
	Node *freeNode;
	if (node->value->key == iKey) {
		freeValue(node->value);
		if (node->leftchild) {
			*tmpNode = rightMostNode(node->leftchild);
			node->value = (*tmpNode)->value;
			freeNode = *tmpNode;
			*tmpNode = NULL;
			free(freeNode);
		}
	}
}
void* getValueFromNode(Node* node, int iKey){
	if (!node) return NULL;
	if (node->value->key == iKey) return node->value;
	else if (node->value->key > iKey) return getValueFromNode(node->leftchild, iKey);
	else return getValueFromNode(node->rightchild, iKey);
}
void getValueFromValue(Node *node, Value* valueArr[], int *valueArrSize, int *compare(void* pvValue, void* pvData), void* pvData){
	if (!node) return;

	getValueFromValue(node->leftchild, valueArr, valueArrSize, compare, pvData);
	if (!compare(node->value, pvData)) valueArr[(*valueArrSize)++] = node->value;
	getValueFromValue(node->rightchild, valueArr, valueArrSize, compare, pvData);


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