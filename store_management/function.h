#pragma once


#include "datatype.h"

//ham in menu chinh'
void printMainMenu();

//ham in menu quan? li' danh muc.
void printManagementCategoryMenu();

//ham in mwenu quan? li' san? pham?
void printManagementProductMenu();

//ham` hien. danh sach' danh muc.
void printCategoryList(struct category* _category, int size);

//ham` them danh muc.
void addCategory(struct category* _category, int* size);



/*=======================================================================*/
//ham quan li danh muc
void manageCategory(int* command, struct category* _categoryList, int* size);

//ham` quan? li' san? pham?
void manageProduct(int* command, struct product* _productList, int* size);

