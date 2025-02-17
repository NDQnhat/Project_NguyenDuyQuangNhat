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

#define MAX 100

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
	int choice, size = 0, isValid = 0, flag = 1;
	printf("1. Log in\t2. Register\t3. Log out\tOther: Exit this interface\n");
	printf("Enter your choice: ");
	while (scanf_s("%d", &choice) != 1) {
		printf("Invalid. Enter again: ");
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
			}
		}
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
		break;
	case 3:
		*status = 0;
		printf("Log out success\n");
		return;
	default:
		printf("Exit interface without doing anything\n");
		return;
	}
}