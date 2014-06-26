/******************************************************/
/* NHNNEXT Programming Practice Final Assignment      */
/* ID   : 141011                                      */
/* Name : Kim Deok Seong                              */
/* File : BST.c                                       */
/* Member Manager                                     */
/******************************************************/

#include "BST.h"


BST		BST_create(void){
	BST oBST;
	oBST = (BST)malloc(sizeof(struct bst));
	oBST->root = NULL;
	return oBST;
}
void	BST_free(BST oBST){
	freeNode(oBST->root);
}
void	BST_insert(BST oBST, void *pvValue){
	Node *parentNode, *curNode, *newNode;

	if (!oBST) return;
	parentNode = NULL;
	curNode = oBST->root;
	while (curNode){
		parentNode = curNode;
		if (((Value*)pvValue)->key < curNode->value->key)
			curNode = curNode->leftchild;
		else
			curNode = curNode->rightchild;
	}
	newNode = (Node*)malloc(sizeof(Node));
	newNode->parent = parentNode;
	newNode->value = pvValue;
	if (parentNode == NULL) oBST->root = newNode;
	else if (newNode->value->key < parentNode->value->key)
		parentNode->leftchild = newNode;
	else
		parentNode->rightchild = newNode;
	newNode->leftchild = newNode->rightchild = NULL;
}

void BST_transplant(BST oBST, Node * rmNode, Node * mvNode){

	if (!rmNode->parent) oBST->root = mvNode;
	else if (rmNode->parent->leftchild == rmNode)
		rmNode->parent->leftchild = mvNode;
	else if (rmNode->parent->rightchild == rmNode)
		rmNode->parent->rightchild = mvNode;
	if (mvNode)
		mvNode->parent = rmNode->parent;
}
void	BST_remove(BST oBST, int iKey){
	Node * successor;
	Node * node;
	node = getNode(oBST->root, iKey);

	if (!node) return;
	if (!node->leftchild) BST_transplant(oBST, node, node->rightchild);
	else if (!node->rightchild) BST_transplant(oBST, node, node->leftchild);
	else{
		successor = leftMostNode(node->rightchild);
		if (node->rightchild != successor){
			BST_transplant(oBST, successor, successor->rightchild);
			successor->rightchild = node->rightchild;
			successor->rightchild->parent = successor;
		}
		BST_transplant(oBST, node, successor);
		successor->leftchild = node->leftchild;
		successor->leftchild->parent = successor;
	}

}
void*	BST_get_value_from_key(BST oBST, int iKey){
	return getValueFromNode(oBST->root, iKey);
}
int	BST_get_value_from_value(BST oBST, Value *valueArr[], int *compare(void *pvValue, void *pvData), void *pvData){
	int arrSize = 0;
	getValueFromValue(oBST->root, valueArr, &arrSize, compare, pvData);
	return arrSize;
}
void	BST_map(BST oBST, void(*pfApply)(void *pvValue, void *pvExtra, FILE *fp), void *pvExtra, FILE *fp){
	mapNode(oBST->root, pfApply, pvExtra, fp);
}


