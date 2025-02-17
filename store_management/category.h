#pragma once
#include "datatype.h"

//ham in menu quan? li' danh muc.
void printManagementCategoryMenu();

//ham` hien. danh sach' danh muc.
void printCategoryList(struct category* _category, int size, int status);

//ham` them danh muc.
void addCategory(struct category* _category, int* size, int status);

//ham` chinh? sua? danh muc.
void editCategory(struct category* _category, int size, int status);

//ham` xoa' san? pham?
void delCategory(struct category* _category, int* size, int status);

//ham` tim` kiem' danh muc. theo ten
void searchByName();

//ham` sap' theo ten
void arrangeByName(struct category* $category, int size, int status);

//ham` lay' du~ lieu. tu` file
//void loadDataFromFile(const char* fileName, const char* mode, int* size, struct category* _category);

//ham` luu du~ lieu. danh muc. vao` file
void saveCategoryData(struct category* _category, int* size, int status);