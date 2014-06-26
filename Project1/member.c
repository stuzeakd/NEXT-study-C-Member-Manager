/******************************************************/
/* NHNNEXT Programming Practice Final Assignment      */
/* ID   : 141011                                      */
/* Name : Kim Deok Seong                              */
/* File : member.c                                    */
/* Member Manager                                     */
/******************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include "member.h"
#include "BST.h"
#include "UI.h"

enum subOption { ID, NAME, PHONE, CANCEL };
enum subOptionOfEdit { EDITNAME, EDITADDRESS, EDITPHONE, EDITCANCEL};
enum registerOption {REGIID, REGINAME, REGIADDRESS, REGIPHONE};
enum quitOption {YES, NO};
/************************************************************************/
/* Utility                                                              */
/*                                                                      */
/*                                                                      */
/************************************************************************/
void fflushStdin(){
	while (getchar() != '\n');
}
int newlineToNull(char* str){
	int n = strlen(str);
	if (n > 0 && (str[n - 1] == '\n' || str[n - 1] == '\r')){
		str[n - 1] = '\0'; // change 'newline' character to '\0'
		return 1;
	}
	return 0;
}
int isNumber(char ch){
	if ('0' <= ch && ch <= '9')
		return 1;
	else
		return 0;
}
int isValidName(char* str){
	if (strlen(str) == 0 || strlen(str) > 10){
		
		return 0;
	}
	for (; *str != '\0' ; str++) {
		if (isNumber(*str)) return 0;
	}
	return 1;
}
int isValidPhone(char* str){
	char *temp;
	char buf[BUF];

	if (strlen(str) != 12 && strlen(str) != 13) return 0;
	if (strlen(str) == 12 && (str[3] != '-' || str[7] != '-')) return 0;
	if (strlen(str) == 13 && (str[3] != '-' || str[8] != '-')) return 0;
	
	strcpy(buf, str);
	for (temp = strtok(buf, "-"); *temp != '\0'; temp++){
		if (!isNumber(*temp)) return 0;
	}
	for (temp = strtok(NULL, "-"); *temp != '\0'; temp++){
		if (!isNumber(*temp)) return 0;
	}
	for (temp = strtok(NULL, "-"); *temp != '\0'; temp++){
		if (!isNumber(*temp)) return 0;
	}

	return 1;
}
/************************************************************************/
/* Define Function                                                      */
/*                                                                      */
/*                                                                      */
/************************************************************************/
void applyMapPrint(void *pvValue, void *pvExtra, FILE *fp){
	Value *pValue = (Value*)pvValue;
	char *pcExtra = (char*)pvExtra;
	printf(pcExtra, pValue->key, pValue->name, pValue->address, pValue->phone);

}
void applyMapSave(void *pvValue, void *pvExtra, FILE *fp){
	Value *pValue = (Value*)pvValue;
	char *pcExtra = (char*)pvExtra;
	fprintf(fp, pcExtra, pValue->key, pValue->name, pValue->address, pValue->phone);
}
int compareName(void *pvValue, void *pvData){
	Value *pValue = (Value*)pvValue;
	char *pcData = (char*)pvData;
	return strcmp(pValue->name, pcData);
}
int comparePhone(void *pvValue, void *pvData){
	Value *pValue = (Value*)pvValue;
	char *pcData = (char*)pvData;
	return strcmp(pValue->phone, pcData);
}
 
/************************************************************************/
/* Get Member                                                           */
/*                                                                      */
/* Make Member list from rawdata                                        */
/************************************************************************/
void getMember(BST oBST, FILE *dataFile){
	char buf[FILEBUF];
	char *token;
	Value *value;
	fgets(buf, FILEBUF, dataFile);
	while (fgets(buf, FILEBUF, dataFile)){
		newlineToNull(buf);

		value = (Value*)malloc(sizeof(Value));
		token = strtok(buf, "\t");
		value->key = atoi(token);
		
		token = strtok(NULL, "\t");
		value->name = (char*)malloc(strlen(token) + 1);
		strcpy(value->name, token);
		
		token = strtok(NULL, "\t");
		value->address = (char*)malloc(strlen(token) + 1);
		strcpy(value->address, token);
		
		token = strtok(NULL, "\t");
		value->phone = (char*)malloc(strlen(token) + 1);
		strcpy(value->phone, token);
		
		BST_insert(oBST, value);
	}
	getchar();
}

/************************************************************************/
/* Print Member                                                         */
/*                                                                      */
/* Print all member list                                                */
/************************************************************************/
void printMember(BST oBST){
	printMessage();
	BST_map(oBST, applyMapPrint, PRINTFORM, NULL);
	getchar();
}

/************************************************************************/
/* Register Member                                                      */
/*                                                                      */
/* Register new member                                                  */
/************************************************************************/
void registerMember(BST oBST){
	Value *pValue;
	char buf[BUF];
	enum subOptionEdit state = REGIID;
	registerMessage();
	//initial
	pValue = (Value*)malloc(sizeof(Value));
	pValue->key = (rightMostNode(oBST->root)->value->key) + 1;
	printf("%d", pValue->key);
	
	state = REGINAME;
	registerForm((int)state);
	fgets(buf, BUF, stdin);
	newlineToNull(buf);
	while (!isValidName(buf)){
		registerForm((int)state);
		invalidInputMessage();
		registerForm((int)state);
		fgets(buf, BUF, stdin);
		newlineToNull(buf);
	}
	pValue->name = (char*)malloc(strlen(buf) + 1);
	strcpy(pValue->name, buf);
	
	state = REGIADDRESS;
	registerForm((int)state);
	fgets(buf, BUF, stdin);
	newlineToNull(buf);
	pValue->address = (char*)malloc(strlen(buf) + 1);
	strcpy(pValue->address, buf);
	
	state = REGIPHONE;
	registerForm((int)state);
	fgets(buf, BUF, stdin);
	newlineToNull(buf);
	while (!isValidPhone(buf)){
		registerForm((int)state);
		invalidInputMessage();
		registerForm((int)state);
		fgets(buf, BUF, stdin);
		newlineToNull(buf);
	}
	pValue->phone = (char*)malloc(strlen(buf) + 1);
	strcpy(pValue->phone, buf);

	BST_insert(oBST, pValue);
	registerFinishMessage();
}

/************************************************************************/
/* Delete Member                                                        */
/*                                                                      */
/* Delete a member                                                      */
/************************************************************************/
void deleteMember(BST oBST){
	enum subOption state = ID;
	enum subOptionOfEdit substate = NAME;
	int key;
	int selectedValuesSize;
	int selectedValueNum = 0;
	char buf[BUF];
	Value *selectedValue;
	Value *selectedValues[BUF];
	while (state != CANCEL){
		state = (enum subOption) deleteMessage((int)state);
		switch (state){
		case ID:
			printf("ID : ");

			fgets(buf, BUF, stdin);
			newlineToNull(buf);
			key = atoi(buf);

			selectedValue = getValueFromNode(oBST->root, key);
			if (!selectedValue) mismatchmMessage();
			else {
				BST_remove(oBST, selectedValue->key);
				removeFinishMessage();
				state = CANCEL;
			}
			break;
		case NAME:
			printf("NAME : ");

			fgets(buf, BUF, stdin);
			newlineToNull(buf);
			selectedValuesSize = BST_get_value_from_value(oBST, selectedValues, compareName, buf);
			if (!selectedValuesSize) mismatchmMessage();
			else{
				if (selectedValuesSize != 1) selectedValueNum = selectValueMessage(selectedValues, selectedValuesSize);
				BST_remove(oBST, selectedValues[selectedValueNum]->key);
				removeFinishMessage();
				state = CANCEL;
			}
			break;
		case PHONE:
			printf("PHONE : ");

			fgets(buf, BUF, stdin);
			newlineToNull(buf);
			selectedValuesSize = BST_get_value_from_value(oBST, selectedValues, comparePhone, buf);
			if (!selectedValuesSize) mismatchmMessage();
			else{
				if (selectedValuesSize != 1) selectedValueNum = selectValueMessage(selectedValues, selectedValuesSize);
				BST_remove(oBST, selectedValues[selectedValueNum]->key);
				removeFinishMessage();
				state = CANCEL;
			}
			break;
		case CANCEL:
			break;
		default:
			wrongMessage();
		}
	}
}

/************************************************************************/
/* Edit Member                                                          */
/*                                                                      */
/* Edit a member data                                                   */
/************************************************************************/
int editMemberValue(void *selectedValue){
	char buf[BUF];
	enum SubOptionOfEdit state = EDITNAME;
	state = (enum subOptionOfEdit) editValueMessage(selectedValue, (int)state);
		
	switch (state){
	case EDITNAME:
		editForm((int)state);
		fgets(buf, BUF, stdin);
		newlineToNull(buf);
		while (!isValidName(buf)){
			editForm((int)state);
			invalidInputMessage();
			editForm((int)state);
			fgets(buf, BUF, stdin);
			newlineToNull(buf);
		}
		strcpy(((Value*)selectedValue)->name, buf);
		break;

	case EDITADDRESS:
		editForm((int)state);
		fgets(buf, BUF, stdin);
		newlineToNull(buf);
		strcpy(((Value*)selectedValue)->address, buf);
		break;

	case EDITPHONE:
		editForm((int)state);
		fgets(buf, BUF, stdin);
		newlineToNull(buf);
		while (!isValidPhone(buf)){
			editForm((int)state);
			invalidInputMessage();
			editForm((int)state);
			fgets(buf, BUF, stdin);
			newlineToNull(buf);
		};
		strcpy(((Value*)selectedValue)->phone, buf);
		break;

	case EDITCANCEL:
		break;
	default:
		wrongMessage();

	}
	return (int)state;
}
void editMember(BST oBST){
	enum subOption state = ID;
	enum subOptionOfEdit substate = NAME;
	int key;
	int selectedValuesSize;
	int selectedValueNum = 0;
	char buf[BUF];
	Value *selectedValue;
	Value *selectedValues[BUF];

	while (state != CANCEL){
		state = (enum subOption)editMessage((int)state);

		switch (state){
		case ID:
			printf("ID : ");

			fgets(buf, BUF, stdin);
			newlineToNull(buf);
			key = atoi(buf);

			selectedValue = getValueFromNode(oBST->root, key);
			if (!selectedValue) mismatchmMessage();
			else {
				substate = (enum substate)editMemberValue(selectedValue);
				if (substate != EDITCANCEL) state = CANCEL;
			}
			break;
		case NAME:
			printf("NAME : ");

			fgets(buf, BUF, stdin);
			newlineToNull(buf);
			selectedValuesSize = BST_get_value_from_value(oBST, selectedValues, compareName, buf);
			if (!selectedValuesSize) mismatchmMessage();
			else{
				if (selectedValuesSize != 1) selectedValueNum = selectValueMessage(selectedValues, selectedValuesSize);
				substate = (enum substate)editMemberValue(selectedValues[selectedValueNum]);
				if (substate != EDITCANCEL) state = CANCEL;
			}
			break;
		case PHONE:
			printf("PHONE : ");

			fgets(buf, BUF, stdin);
			newlineToNull(buf);
			selectedValuesSize = BST_get_value_from_value(oBST, selectedValues, comparePhone, buf);
			if (!selectedValuesSize) mismatchmMessage();
			else{
				if (selectedValuesSize != 1) selectedValueNum = selectValueMessage(selectedValues, selectedValuesSize);
				substate = (enum substate)editMemberValue(selectedValues[selectedValueNum]);
				if (substate != EDITCANCEL) state = CANCEL;
			}
			break;
		case CANCEL:
			break;
		default:
			wrongMessage();
		}
	}
}

/************************************************************************/
/* Search Member                                                        */
/*                                                                      */
/* Search a member                                                      */
/************************************************************************/
void searchMember(BST oBST){
	enum subOption state = ID;
	int key;
	int selectedValuesSize;
	int selectedValueNum = 0;
	char buf[BUF];
	Value *selectedValues[BUF];
	while (state != CANCEL){
		state = (enum subOption)searchMessage((int)state);
		switch (state){
		case ID:
			printf("ID : ");

			fgets(buf, BUF, stdin);
			newlineToNull(buf);
			key = atoi(buf);

			selectedValues[0] = getValueFromNode(oBST->root, key);
			if (!selectedValues[0]) mismatchmMessage();
			else {
				printSearchResult(selectedValues, 1);
			}
			break;
		case NAME:
			printf("NAME : ");
			fgets(buf, BUF, stdin);
			newlineToNull(buf);

			selectedValuesSize = BST_get_value_from_value(oBST, selectedValues, compareName, buf);
			if (!selectedValuesSize) mismatchmMessage();
			else{
				printSearchResult(selectedValues, selectedValuesSize);
			}
			break;
		case PHONE:
			printf("PHONE : ");
			fgets(buf, BUF, stdin);
			newlineToNull(buf);

			selectedValuesSize = BST_get_value_from_value(oBST, selectedValues, comparePhone, buf);
			if (!selectedValuesSize) mismatchmMessage();
			else{
				printSearchResult(selectedValues, selectedValuesSize);
			}
			break;
		case CANCEL:
			break;
		default:
			wrongMessage();
		}
	}
}

/************************************************************************/
/* Save Member                                                          */
/*                                                                      */
/* Save all member list to dataFile                                     */
/************************************************************************/
void saveMember(BST oBST){
	FILE *writeFile;
	writeFile = fopen("out.txt", "wt");
	fprintf(writeFile, "회원 아이디\t회원이름\t회원주소\t핸드폰 번호\n");
	BST_map(oBST, applyMapSave, SAVEFORM, writeFile);
	fclose(writeFile);
	saveMessage();
}

/************************************************************************/
/* Quit Member                                                          */
/*                                                                      */
/* Quit the member program                                              */
/************************************************************************/
void quitMember(BST oBST){
	enum quitOption state;

	state = (enum quitOption)quitMessage();
	switch (state){
	case YES:
		saveMember(oBST);
		break;
	case NO:
		break;
	}
	BST_free(oBST);
	byeMessage();
	getchar();
}

