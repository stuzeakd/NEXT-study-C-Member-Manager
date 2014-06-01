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
	insertNode(&(oBST->root), pvValue);
}
void	BST_replace(BST oBST, int iKey, int *compare(void *pvValue, char *pcData), char *pcData){


}
void	BST_remove(BST oBST, int iKey){


}
void	BST_get(BST oBST, int iKey){


}
Node*	BST_search_key(BST oBST, int iKey){


}
void	BST_search_value(BST oBST, Node *nodearr[], int *compare(void *pvValue, char *pcData), char *pcData){

}
void	BST_map(BST oBST, void(*pfApply)(void *pvValue, void *pvExtra, FILE *fp), void *pvExtra, FILE *fp){
	mapNode(oBST->root, pfApply, pvExtra, fp);
}


