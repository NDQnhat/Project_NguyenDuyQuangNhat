#pragma once


#include "datatype.h"
#include <stdbool.h>

//ham in menu chinh'
void printMainMenu();

//ham` tim` kiem ton` tai.
bool isFounded(char a[10], char b[10]);

//ham quan li danh muc
void manageCategory(int* command, struct category* _categoryList, int* size, int status);

//ham` quan? li' san? pham?
void manageProduct(int* command, struct product* _productList, int* size, struct category* _categoryList, int* length, int status);

//===========================================================//

//ham` in * cho pass
void getPassword(char* pass, int length);

//ham` xac' thuc. admin
void identifyAdmin(int* status);