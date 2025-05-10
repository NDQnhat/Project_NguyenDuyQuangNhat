#define _CRT_SECURE_NO_WARNINGS		//visual studio noi' fopen khong bao? mat va` yeu cau` dung` fopen_s

#include <stdio.h>
#include "datatype.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "category.h"
#include "product.h"
#include <time.h>

#define MAX 100

//ham` an' de? thoat'
void pressEnterToExit()
{
	printf("\nPRESS 'ENTER' TO EXIT...........");
	getchar();
	system("cls");
}


//ham in menu chinh'
void printMainMenu()
{
	printf("\n***Store Management Using C***\n");
	printf("%5s\n", "CHOOSE YOUR ROLE");
	printf("===============================\n");
	printf("[1] Management Category\n");
	printf("[2] Management Product\n");
	printf("[3] Identify Admin (Otherwise uses with guest)\n");
	printf("[4] Exit The Program\n");
	printf("[0] View lists of bill (Must be admin!!)\n");
	printf("===============================\n");
	printf("Enter The Choice: ");
};


//ham` tim` kiem' ton` tai.
bool isFounded(char a[10], char b[10])
{
	if (strcmp(a, b) == 0) {
		return true;
	} return false;
};


//ham` chon. san? pham? mua cua? khach' hang`
void buyProduct()
{
	struct product temp;
	struct product $product[MAX];
	int size = 0;
	FILE* f = fopen("product.bin", "rb");
	while (fread(&temp, sizeof(struct product), 1, f)) {
		$product[size] = temp;
		size++;
	}
	fclose(f);

	printf("Enter Id product to buy: ");
	char Id[10];
	int flag = 1;
	while (scanf_s(" %[^\n]", Id, 10) != 1 || strlen(Id)==0) {
		printf("Invalid! Enter again: ");
		while (getchar() != '\n');
	}
	getchar();
	for (int i = 0;i < size;i++) {
		if (isFounded(Id, $product[i].productId)) {
			flag = 0;
			printf("Information about product has Id '%s':\n", Id);
			printf("Name: %s\t\tQuantity: %d\t\tPrice: %d\n", $product[i].productName, $product[i].quantity, $product[i].price);
			if ($product[i].quantity == 0) {
				printf("OUT OF STOCK!!\n");
				return;
			}
			else {
				printf("Sure to buy this??\t1. YES\t2. NO\n");
				int choice;
				printf("Enter your choice: ");
				while (scanf_s("%d", &choice) != 1 || (choice < 1 || choice >2)) {
					printf("Invalid!!Enter again: ");
					while (getchar() != '\n');
				}
				getchar();
				switch (choice)
				{
				case 1:
				{
					struct order _order;
					FILE* file = fopen("order.bin", "rb");
					if (file == NULL) {
						file = fopen("order.bin", "wb");
						fclose(file);
						file = fopen("order.bin", "rb");
					}
					struct order temporary;
					struct order list[MAX];
					int count = 0;
					int max = 0;
					while (fread(&temporary, sizeof(struct order), 1, file)) {
						list[count] = temporary;
						count++;
						int num;
						sscanf(temporary.customerId, "CUS%d", &num);
						if (num > max) {
							max = num;
						}
					}
					fclose(file);
					int num = max + 1;
					//int num = 0;
					//char cusId[10];
					//char orderId[10];
					//sprintf(_order.customerId, "CUS%06d", num);
					//for (int j = 0;j < count;j++) {
					//	if (isFounded(_order.customerId, list[j].customerId)) {
					//		num++;
					//		//j = -1;
					//	}
					//}

					sprintf(_order.customerId, "CUS%06d", num);
					sprintf(_order.orderId, "ORD%06d", num);
					//xong khuc' nay` la` da~ co' cusId va` orderID cua? struct order
					time_t now;
					struct tm* local;
					time(&now);
					local = localtime(&now);

					_order._date.hour = local->tm_hour;
					_order._date.minute = local->tm_min;
					_order._date.second = local->tm_sec;
					_order._date.day = local->tm_mday;
					_order._date.month = local->tm_mon + 1;
					_order._date.year = local->tm_year + 1900;

					strcpy(_order._product.productId, $product[i].productId);
					strcpy(_order._product.productName, $product[i].productName);
					strcpy(_order._product.categoryId, $product[i].categoryId);
					//_order._product.quantity = 1;
					_order._product.quantity = ($product[i].quantity) / ($product[i].quantity);
					_order._product.price = $product[i].price;

					file = fopen("order.bin", "ab");
					fwrite(&_order, sizeof(struct order), 1, file);
					fclose(file);

					printf("\n\n");
					printf("\t\t\tTHIS IS YOUR BILL\n");
					printf("Customer Id: %s\t\tOrder Id: %s\n", _order.customerId, _order.orderId);
					printf("Time: %d:%02d:%02d\t%d/%d/%d\n", _order._date.hour, _order._date.minute, _order._date.second, _order._date.day, _order._date.month, _order._date.year);
					printf("Product:  %s\tProduct Id: %s\tCategory Id: %s\n", _order._product.productName, _order._product.productId, _order._product.categoryId);
					printf("Quantity: 1\tTotal amount: %d\n", _order._product.price);
					pressEnterToExit();
					break;
				}
				case 2:
					printf("Why don’t you make a little purchase to cheer yourself up? //(^\/^)//\n");
					pressEnterToExit();
					break;
				//default: khong can` nua~
				}
			}
			break;
		}
	}
	if (flag) {
		printf("Id no exist!!\n");
		pressEnterToExit();
	}
}


//ham quan li danh muc
void manageCategory(int* command, struct category* _categoryList, int* size, int status)
{
	while (1)
	{
		printManagementCategoryMenu();
		scanf_s("%d", command);
		getchar();
		if (*command >= 1 && *command <= 8) {
			switch (*command)
			{
			case 1:
				system("cls");
				printCategoryList(_categoryList, *size, status);
				break;
			case 2:
				system("cls");
				addCategory(_categoryList, size, status);
				break;
			case 3:
				system("cls");
				editCategory(_categoryList, *size, status);
				break;
			case 4:
				system("cls");
				delCategory(_categoryList, size, status);
				break;
			case 5:
				system("cls");
				searchByName();
				break;
			case 6:
				system("cls");
				arrangeByName(_categoryList, *size, status);
				break;
			case 7:
				system("cls");
				saveCategoryData(_categoryList, size, status);
				break;
			case 8:
				printf("Out Of Interface\n");
				pressEnterToExit();
				return;
			}
		}
		else {
			printf("Please Enter Again\n");
		}
	}
};



//ham` quan? li' san? pham?
void manageProduct(int* command, struct product* _productList, int* size, struct category* _categoryList, int* length, int status)
{
	while (1)
	{
		printManagementProductMenu();
		scanf_s("%d", command);
		getchar();
		if (*command >= 1 && *command <= 9) {
			switch (*command)
			{
			case 1:
				system("cls");
				printProductList(_productList, *size, status);
				break;
			case 2:
				system("cls");
				addProduct(_productList, size, _categoryList, length, status);
				break;
			case 3:
				system("cls");
				editProduct(_productList, *size, status);
				break;
			case 4:
				system("cls");
				delProduct(_productList, size, status);
				break;
			case 5:
				system("cls");
				searchProductByName();
				break;
			case 6:
				system("cls");
				arrangeProductByPrice(_productList, *size, status);
				break;
			case 7:
				system("cls");
				filterProduct(_productList, *size);
				break;
			case 8:
				system("cls");
				saveProductData(_productList, size, status);
				break;
			case 9:
				printf("Out Of Interface\n");
				pressEnterToExit();
				return;
			}
		}
		else {
			printf("Please Enter Again\n");
		}
	}
};


//======================================================================
// ham` hien. "*" cho pass
void getPassword(char* pass, int length)
{
	int i = 0;
	char c;
	while (1)
	{
		c = _getch();	//lay' ki' tu. khong hien. ten man` hinh`
		if (c == 13) {	//xu? li' enter
			pass[i] = '\0';
			break;
		}
		else if (c == 8) {	//xu? li' backspace
			if (i > 0) {
				i--;
				printf("\b \b");
			}
		}
		else if (i < length - 1) {
			pass[i] = c;
			i++;
			printf("*");
		}
	}
}


//ham` cac' thuc. admin
void identifyAdmin(int* status)
{
	if (*status) {
		printf("ALREADY LOG IN!!!\n");
		pressEnterToExit();
	}
	else {
		int choice, size = 0, isValid = 0, flag = 1;
		printf("1. Log in\t2. Register\t3. Log out\tOther: Exit this interface\n");
		printf("Enter your choice: ");
		while (scanf_s("%d", &choice) != 1) {
			printf("Invalid. Enter again: ");
			while (getchar() != '\n');
		}
		getchar();
		struct account accountList[MAX];
		struct account temp;
		struct account input;
		FILE* file = fopen("account.bin", "rb");
		if (file == NULL) {
			file = fopen("account.bin", "wb");
			fclose(file);
			file = fopen("account.bin", "rb");
		}
		while (fread(&temp, sizeof(struct account), 1, file)) {
			accountList[size] = temp;
			size++;
		}
		fclose(file);
		switch (choice)
		{
		case 1:
			isValid = 0;
			while (!isValid) {
				printf("Username: ");
				scanf_s(" %[^\n]", input.userName, 20);
				getchar();
				printf("Password: ");
				getPassword(input.password, 20);
				getchar();
				for (int i = 0;i < size;i++) {
					if (isFounded(accountList[i].userName, input.userName) && isFounded(accountList[i].password, input.password)) {
						printf("Log in success!!\n");
						isValid = 1;
						*status = 1;
						flag = 0;
						break;
					}
				}
				if (isValid)	break;
				if (flag) {
					printf("Login failed\n");
					printf("\n");
					pressEnterToExit();
					return;
				}
			}
			pressEnterToExit();
			break;
		case 2:
			isValid = 0;
			while (!isValid) {
				isValid = 1;
				printf("Username: ");
				scanf_s(" %[^\n]", input.userName, 20);
				getchar();
				printf("Password: ");
				getPassword(input.password, 20);
				getchar();
				for (int i = 0;i < size;i++) {
					if (isFounded(accountList[i].userName, input.userName) || isFounded(accountList[i].password, input.password)) {
						printf("Username or Password already exist!!\n");
						isValid = 0;
						break;
					}
				}
				if (!isValid)	continue;
				file = fopen("account.bin", "ab");
				fwrite(&input, sizeof(struct account), 1, file);
				printf("Create account success!! Log in to use\n");
				fclose(file);
			}
			pressEnterToExit();
			break;
		case 3:
			*status = 0;
			printf("Log out success\n");
			pressEnterToExit();
			break;
		default:
			printf("Exit interface without doing anything\n");
			pressEnterToExit();
			break;
		}
	}
}

//ham` xem danh sach' hoa' don
void viewBillList(struct order* _order, int* size)
{
	int first = 0;
	FILE* file = fopen("order.bin", "rb");
	if (file == NULL) {
		printf("NO BILL IN FILE\n");
		file = fopen("order.bin", "wb");
		fclose(file);
		return;
	}
	struct order temp;
	while (fread(&temp, sizeof(struct order), 1, file)) {
		_order[*size] = temp;
		(*size)++;
	}
	fclose(file);
	printf("\t\t\t*****BILL LIST*****\n");
	for (int i = 0;i < *size;i++) {
		printf("\n==============================================================\n");
		printf("\t\tOrder Id: %s\n", _order[i].orderId);
		printf("Time: %d:%02d:%02d - %d/%d/%d\n", _order[i]._date.hour, _order[i]._date.minute, _order[i]._date.second, _order[i]._date.day, _order[i]._date.month, _order[i]._date.year);
		printf("Customer Id: %s\n", _order[i].customerId);
		printf("Product Id: %s\t\tCategory Id: %s\n", _order[i]._product.productId, _order[i]._product.categoryId);
		printf("Product name: %s\t\tQuantity: %d\n", _order[i]._product.productName, _order[i]._product.quantity);
		printf("TOTAL AMOUNT: %d\n", _order[i]._product.price);
	}
	pressEnterToExit();
}