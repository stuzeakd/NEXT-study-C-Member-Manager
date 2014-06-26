/******************************************************/
/* NHNNEXT Programming Practice Final Assignment      */
/* ID   : 141011                                      */
/* Name : Kim Deok Seong                              */
/* File : BSTsub.c                                    */
/* Member Manager                                     */
/******************************************************/

#include <stdio.h>
#include "BSTnode.h"
Node* leftMostNode(Node *node){
	Node *temp;
	if (!node) return NULL;
	for (temp = node; temp->leftchild != NULL; temp = temp->leftchild){
		//printf("%d %s\n", temp->value->key, temp->value->name);
	}

	return temp;
}
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
Node* getNode(Node *node, int iKey){
	if (!node) return NULL;
	if (node->value->key == iKey) return node;
	else if (node->value->key > iKey) return getNode(node->leftchild, iKey);
	else return getNode(node->rightchild, iKey);
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

void mapNode(Node *node, void(*pfApply)(void *pvValue, void *pvExtra, FILE *fp), void *pvExtra, FILE *fp){
	if (node == NULL) return;
	if (node->leftchild != NULL)
		mapNode(node->leftchild, pfApply, pvExtra, fp);
	pfApply(node->value, pvExtra, fp);
	if (node->rightchild != NULL)
		mapNode(node->rightchild, pfApply, pvExtra, fp);
}