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
	struct node *parent;
}Node;

Node* leftMostNode(Node *node);
Node* rightMostNode(Node *node);

void freeValue(Value* value);
void freeNode(Node *node);
Node* getNode(Node *node, int iKey);
void* getValueFromNode(Node* node, int iKey);
void getValueFromValue(Node *node, Value* valueArr[], int valueArrSize, int *compare(void* pvValue, void* pvData), void* pvData);
void mapNode(Node *node, void(*pfApply)(void *pvValue, void *pvExtra, FILE *fp), void *pvExtra, FILE *fp);
#endif