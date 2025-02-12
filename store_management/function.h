#pragma once


#include "datatype.h"
#include <stdbool.h>

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

//ham` tim` kiem ton` tai.
bool isFounded(char a[10], char b[10]);

//ham` chinh? sua? danh muc.
void editCategory(struct category* _category, int* size);

//ham` xoa' san? pham?
void delCategory(struct category* _category, int* size);

//ham` tim` kiem' danh muc. theo ten
void searchByName(struct category _category, int size);

//ham` sap' theo ten
void arrangeByName(struct category* $category, int size);

//ham` luu du~ lieu. danh muc. vao` file
void saveCategoryData(struct category* _category);	//can` sua? lai.






/*=======================================================================*/
//ham quan li danh muc
void manageCategory(int* command, struct category* _categoryList, int* size);

//ham` quan? li' san? pham?
void manageProduct(int* command, struct product* _productList, int* size);

