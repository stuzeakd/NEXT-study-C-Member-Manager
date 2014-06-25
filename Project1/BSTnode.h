/******************************************************/
/* NHNNEXT Programming Practice Final Assignment      */
/* ID   : 141011                                      */
/* Name : Kim Deok Seong                              */
/* File : BSTsub.h                                    */
/* Member Manager                                     */
/******************************************************/

#ifndef __BSTsub_h__
#define __BSTsub_h__

typedef struct value{
	int key;
	char *name;
	char *address;
	char *phone;
}Value;

typedef struct node{
	Value *value;
	struct node *leftchild;
	struct node *rightchild;
}Node;

Node* rightMostNode(Node *node);

void freeNode(Node *node);
void insertNode(Node *node, void *pvValue);
void* getValueFromNode(Node* node, int iKey);
Node* searchNodeKey(Node *node, int iKey);
void searchNodeValue(Node *node, Node* nodearr[], int *nodearrSize, int *compare(void* pvValue, char* pcData), char* pcData);
void mapNode(Node *node, void(*pfApply)(void *pvValue, void *pvExtra, FILE *fp), void *pvExtra, FILE *fp);
#endif