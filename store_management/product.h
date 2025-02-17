#pragma once
#include "datatype.h"

//ham in mwenu quan? li' san? pham?
void printManagementProductMenu();


//ham` hien. danh sach' san? pham?
void printProductList(struct product* _product, int size, int status);

//ham` them san? pham? vao` 
void addProduct(struct product* $product, int* size, struct category* _category, int* length, int status);

//ham` chinh? sua? thong tin san? pham? (khong sua? id)
void editProduct(struct product* _product, int size, int status);

//ham` tim` kiem' san? pham? theo ten
void searchProductByName();

//ham` xoa' san? pham? 
void delProduct(struct product* _product, int* size, int status);

//sap' xep' san? pham? theo gia'
void arrangeProductByPrice(struct product* _product, int size, int status);

//ham` loc san? pham?
void filterProduct();

//ham` luu, lay' du~ lieu. san? pham? tu` file
void saveProductData(struct product* _product, int* size, int status);