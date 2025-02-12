#define _CRT_SECURE_NO_WARNINGS		//visual studio noi' fopen khong bao? mat va` yeu cau` dung` fopen_s

#include <stdio.h>
#include "datatype.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>


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

//ham in menu quan? li' danh muc.
void printManagementCategoryMenu()
{
	printf("\n***Management Category Menu***\n");
	printf("%5s\n", "CHOOSE YOUR ROLE");
	printf("================================\n");
	printf("[1] Show Category List\n");
	printf("[2] Add Category\n");
	printf("[3] Edit Category\n");	//khong sua id
	printf("[4] Delete Category\n");
	printf("[5] Search Category By Name\n");
	printf("[6] Arrange Category By Name\n");
	printf("[7] Save Data\n");
	printf("[8] Exit This Interface\n");
	printf("================================\n");
	printf("Enter The Choice: ");
};


//ham in mwenu quan? li' san? pham?
void printManagementProductMenu()
{
	printf("\n***Management Product Menu***\n");
	printf("%5s\n", "CHOOSE YOUR ROLE");
	printf("===============================\n");
	printf("[1] Show Product List\n");
	printf("[2] Add Product\n");
	printf("[3] Edit Product Information\n");
	printf("[4] Delete Product\n");
	printf("[5] Search Product By Name\n");
	printf("[6] Arrange Product By Price\n");
	printf("[7] Filter Product\n");
	printf("[8] Save Data\n");
	printf("[9] Exit This Interface\n");
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





//---------------------Quan? li' danh muc.----------------------------------





//ham` hien. danh sach' danh muc.
void printCategoryList(struct category* _category, int size)
{
	if (size == 0) {
		printf("Category is not exist\n");
	}
	else {
		printf("\n%s\n", "******Category List******");
		printf("\n");
		printf("|----------|----------|\n");
		printf("|%-10s|%-10s|\n", "Id", "Name");
		printf("|----------|----------|\n");
		for (int i = 0; i < size; i++) {
			printf("|%-10s|%-10s|\n", _category[i].categoryId, _category[i].categoryName);
			printf("|----------|----------|\n");
		} 
	}
};

//ham` them danh muc.
void addCategory(struct category* _category, int* size)
{
	int quantity;
	printf("Enter number of category to add: ");
	while (scanf_s("%d", &quantity) <= 0) {
		printf("Invalid input! Enter again: ");
		//fflush(stdin);
		while (getchar() != '\n');		//xoa' bo. nho' dem
	}
	getchar();
	for (int i = 0; i < quantity; i++) {
		struct category temp;
		int isValid = 0;
		while (!isValid) {
			isValid = 1;	//gia? su? DL hop. le. otherwise =0
			printf("Category Id: ");
			scanf_s(" %[^\n]", temp.categoryId, (unsigned)sizeof(temp.categoryId));	
			getchar();
			printf("Category Name: ");
			scanf_s(" %[^\n]", temp.categoryName, (unsigned)sizeof(temp.categoryName));
			//fgets(temp.categoryName, sizeof(temp.categoryName), stdin);
			getchar();
			/*int length = (int)strlen(temp.categoryName);
			if (length > 0 && temp.categoryName[length - 1] == '\n') {
				temp.categoryName[len - 1] = '\0';
			}*/
			
			//kiem? tra rong~
			if (strlen(temp.categoryId) == 0 || strlen(temp.categoryName) == 0) {
				isValid=0; 
				printf("Id or Name invalid!!\n");
				continue;
			}

			//kiem? tra trung` id
			for (int j = 0;j < *size;j++) {
				if (isFounded(temp.categoryId, _category[j].categoryId)) {
					printf("Category Id already exist!!\n");
					isValid = 0;
					break;
				}
				if (isFounded(temp.categoryName, _category[j].categoryName)) {
					printf("Category name already exist!!\n");
					isValid = 0;
					break;
				}
			}
		}
		_category[*size] = temp;
		(*size)++;
		printf("ADD SUCCESS!\n");
		printf("\n");
	}			
};


//ham` chinh? sua? danh muc.
void editCategory(struct category* _category, int size)
{
	int flag = 1;
	printf("Enter ID to edit: ");
	char identify[10];
	scanf_s(" %[^\n]", identify, 10);
	getchar();
	for (int i = 0; i < size; i++) {
		if (isFounded(identify, _category[i].categoryId)) {
			flag = 0;
			printf("ID: %s, Name: %s\n", _category[i].categoryId, _category[i].categoryName); //hien thong tin dah muc hien tai va sua
			printf("Name to change: ");
			scanf_s(" %[^\n]", _category[i].categoryName, 10);
			break;
		}
	} if (flag) {
		printf("Cannot found the ID in category\n");
	}
};

//ham` xoa' san? pham?
void delCategory(struct category* _category, int* size)
{
	int flag = 1;
	printf("Enter ID to delete: ");
	char identify[10];
	scanf_s(" %[^\n]", identify, 10);
	getchar();
	for (int i = 0;i < *size; i++) {
		if (isFounded(identify, _category[i].categoryId)) {
			int choice;
			flag = 0;
			printf("1. Agree to delete\t2. Disagree to delete\n");
			printf("Enter your choice: ");
			scanf_s("%d", &choice);
			getchar();
			switch (choice)
			{
			case 1:
				for (int i = 0;i < *size; i++) {
					if (isFounded(identify, _category[i].categoryId)) {
						for (int j = i;j < *size - 1;j++) {
							_category[j] = _category[j + 1];
						}
						(*size)--;
						printf("Delete success!!!\n");
						break;
					}
				}
				break;
			case 2:
				printf("Out of this script without doing anything\n");
				return;
			default:
				printf("Wrong choice! Out of this script\n");	//nhap. sai thi` khong cho xoa' nua~
			}
		}
		if (flag) {
			printf("ID not exist!!\n");
		}
	}
};

//ham` tim` kiem' danh muc. theo ten
void searchByName(struct category* _category, int size)	//truyen` tham tri. vao _category vi` ham` isFounded can truyen con tro?
{
	char name[10];
	int flag = 1;
	printf("Enter name of category to find: ");
	scanf_s(" %[^\n]", name, 10);
	for (int i = 0;i < size;i++) {
		if (isFounded(name, _category[i].categoryName)) {
			flag = 0;
			printf("Information about %s:\n", name);
			printf("ID: %s, Name: %s\n", _category[i].categoryId, _category[i].categoryName);
			break;
		}
	}
	if (flag) {
		printf("Cannot found category!!\n");
	}
};

//ham` sap' theo ten
void arrangeByName(struct category* $category, int size)
{
	for (int i = 0;i < size - 1;i++) {
		for (int j = 0;j < size - i - 1;j++) {
			if (strcmp($category[j].categoryName, $category[j+1].categoryName) > 0) {
				struct category temp = $category[j];
				$category[j] = $category[j + 1];
				$category[j + 1] = temp;
			}
		}
	}
	printf("Arrange Success!\n");
};

//ham` luu du~ lieu. danh muc. vao` file
void saveCategoryData(struct category* _category, int* size)
{
	int choice;
	printf("1. Load data from file\t2. Save data to file\t0. Back\nEnter your choice: ");
	scanf_s("%d", &choice);
	getchar();
	switch(choice)
	{
		case 1:	//mo? file va` lay' du~ lieu. tu` file
		{
			FILE* file = fopen("category.bin", "rb");		//a declaration cannot have a label: khong cho khai bao' trong case nen them {}
			if (file == NULL) {
				printf("Cannot open file!!!\n");
				break;
			}
			int count;
			fread(&count, sizeof(int), 1, file);
			fread(_category, sizeof(struct category), count, file);
			*size = count;
			fclose(file);
			printf("Load category to file success!!\n");
			break;
		}
		case 2:	//mo? file va` luu du~ lieu vao` file, neu' file chua tao. thi` tao moi' file 
		{
			FILE* file = fopen("D:\\PTIT2024B EXCERCISE\\C\\store_management\\category.bin", "ab");
			if (file == NULL) {
				file = fopen("D:\\PTIT2024B EXCERCISE\\C\\store_management\\category.bin", "wb");
				if (file == NULL) {
					printf("Error creating file\n");
					break;
				}
				printf("File created!\n");
			}
			fwrite(size, sizeof(int), 1, file);
			fwrite(_category, sizeof(struct category), *size, file);
			fclose(file);
			printf("Add data to file success!\n");
			break;
		}
		case 0:
			printf("Back to previous\n");
			return;
		default:
			printf("Out this script without doing anything\n");
			return;
	}
};




//--------------------------------------Quan? li' san? pham?-----------------------------

//ham` hien. danh sach' san? pham?
void printProductList(struct product* _product, int size)
{
	if (size == 0) {
		printf("No product exist\n");
	}
	else {
		printf("\n%17s\n", "****** Product List *****");
		printf("\n");
		printf("|------------|------------|------------|----------|-------|\n");
		printf("|%-12s|%-12s|%-12s|%-10s|%-7s|\n", "Product Id", "Category Id", "Product Name", "Quantity", "Price");
		printf("|------------|------------|------------|----------|-------|\n");
		for (int i = 0; i < size; i++) {
			printf("|%-12s|%-12s|%-12s|%10d|%7d|\n", _product[i].productId, _product[i].categoryId, _product[i].productName, _product[i].quantity, _product[i].price);
			printf("|------------|------------|------------|----------|-------|\n");
		}
	}
};

//ham` them san? pham? vao` 
void addProduct(struct product* $product, int* size)
{
	int quantity;
	
	printf("Enter quantity of product: ");
	while (scanf_s("%d", &quantity) <= 0) {
		printf("Invalid. Enter again: ");
		while (getchar() != '\n');
	}
	getchar();
	for (int i = 0;i < quantity;i++) {
		struct product temp;
		int isValid = 0;
		while (!isValid) {
			isValid = 1;
			printf("Enter product Id: ");
			scanf_s(" %[^\n]", temp.productId, (unsigned)sizeof(temp.productId));
			getchar();
			printf("Enter product name: ");
			scanf_s(" %[^\n]", temp.productName, (unsigned)sizeof(temp.productName));
			getchar();
			if (strlen(temp.productId) == 0 || strlen(temp.productName) == 0) {
				printf("ID or name invalid\n");
				isValid = 0;
				continue;
			}

			for (int j = 0;j < *size;j++) {
				if (isFounded(temp.productId, $product[j].productId)) {
					isValid = 0;
					printf("Id product already exist. Other choice to edit\n");
					break;
				}
				if (isFounded(temp.productName, $product[j].productName)) {
					isValid = 0;
					printf("Product already exist. Other choice to edit\n");
					break;
				}
			}
			printf("Enter category Id: ");
			scanf_s(" %[^\n]", temp.categoryId, (unsigned)sizeof(temp.categoryId));
			getchar();
			printf("Enter quantity of product: ");
			//while (!isdigit(scanf_s("%d", &temp.quantity))) {
			while (scanf_s("%d", &temp.quantity) != 1 || quantity < 0) {
				printf("Invalid! Please enter a digit: ");
				while (getchar() != '\n');
			}
			getchar();
			printf("Enter price of product: ");
			//while (!isdigit(scanf_s("%d", &temp.price))) {
			while (scanf_s("%d", &temp.price) != 1 || quantity < 0) {
				printf("Invalid! Please enter a digit: ");
				while (getchar() != '\n');
			}
			getchar();
			
		}
		printf("ADD SUCESS\n");
		$product[*size] = temp;
		(*size)++;
		printf("\n");
	}
	
}










//-------------------------------------Ham` dieu` huong' danh muc., san? pham?------------------

//ham quan li danh muc
void manageCategory(int* command, struct category* _categoryList, int* size)
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
				printCategoryList(_categoryList, *size);
				break;
			case 2:
				system("cls");
				addCategory(_categoryList, size);
				break;
			case 3:
				system("cls");
				editCategory(_categoryList, *size);
				break;
			case 4:
				system("cls");
				delCategory(_categoryList, size);
				break;
			case 5:
				system("cls");
				searchByName(_categoryList, *size);
				break;
			case 6:
				system("cls");
				arrangeByName(_categoryList, *size);
				break;
			case 7:
				system("cls");
				saveCategoryData(_categoryList, size);
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
void manageProduct(int* command, struct product* _productList, int* size)
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
				printProductList(_productList, *size);
				break;
			case 2:
				system("cls");
				addProduct(_productList, size);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
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