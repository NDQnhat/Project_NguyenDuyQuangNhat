#pragma once
// kieu? du~ lieu. ngay` thang' nam
struct date{
	int month, day, year;
};
//kieu? du~ lieu. ten danh muc.
struct category{
	char categoryId[10];
	char categoryName[10];
};
//san? pham?
struct product{
	char productId[10];
	char categoryId[10];
	char productName[10];
	int quantity;	//so' luong.
	int price;
};
//don hang`
struct order{
	char orderId[10];
	char customerId[20];
	struct date _date;
	struct product _product;
};
