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

//ham` tim` kiem ton` tai.
bool isFounded(char a[10], char b[10]);

//ham` them danh muc.
void addCategory(struct category* _category, int* size, int status);

//ham` chinh? sua? danh muc.
void editCategory(struct category* _category, int size, int status);

//ham` xoa' san? pham?
void delCategory(struct category* _category, int* size, int status);

//ham` tim` kiem' danh muc. theo ten
void searchByName();

//ham` sap' theo ten
void arrangeByName(struct category* $category, int size);

//ham` lay' du~ lieu. tu` file
//void loadDataFromFile(const char* fileName, const char* mode, int* size, struct category* _category);

//ham` luu du~ lieu. danh muc. vao` file
void saveCategoryData(struct category* _category, int* size, int status);	



//=====================================================================

//ham` hien. danh sach' san? pham?
void printProductList(struct product* _product, int size);

//ham` them san? pham? vao` 
void addProduct(struct product* $product, int* size, struct category* _category, int* length, int status);

//ham` chinh? sua? thong tin san? pham? (khong sua? id)
void editProduct(struct product* _product, int size, int status);

//ham` tim` kiem' san? pham? theo ten
void searchProductByName();

//ham` xoa' san? pham? 
void delProduct(struct product* _product, int* size, int status);

//sap' xep' san? pham? theo gia'
void arrangeProductByPrice(struct product* _product, int size);

//ham` loc san? pham?
void filterProduct(struct product* $product, int size);

//ham` luu, lay' du~ lieu. san? pham? tu` file
void saveProductData(struct product* _product, int* size, int status);






/*=======================================================================*/
//ham quan li danh muc
void manageCategory(int* command, struct category* _categoryList, int* size, int status);

//ham` quan? li' san? pham?
void manageProduct(int* command, struct product* _productList, int* size, struct category* _categoryList, int* length, int status);

//===========================================================//

//ham` in * cho pass
void getPassword(char* pass, int length);

//ham` xac' thuc. admin
void identifyAdmin(int* status);