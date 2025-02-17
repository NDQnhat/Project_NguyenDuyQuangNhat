#define _CRT_SECURE_NO_WARNINGS		//visual studio noi' fopen khong bao? mat va` yeu cau` dung` fopen_s

#include <stdio.h>
#include "datatype.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "function.h"

#define MAX 100


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


//ham` hien. danh sach' san? pham?
void printProductList(struct product* _product, int size, int status)
{
	if (status) {
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
	}
	else {
		FILE* file = fopen("product.bin", "rb");
		struct product temp;
		int length = 0;
		struct product list[MAX];
		while (fread(&temp, sizeof(struct product), 1, file)) {
			list[length] = temp;
			length++;
		}
		printf("\n%17s\n", "****** Product List *****");
		printf("\n");
		printf("|------------|------------|------------|----------|-------|\n");
		printf("|%-12s|%-12s|%-12s|%-10s|%-7s|\n", "Product Id", "Category Id", "Product Name", "Quantity", "Price");
		printf("|------------|------------|------------|----------|-------|\n");
		for (int i = 0; i < length; i++) {
			printf("|%-12s|%-12s|%-12s|%10d|%7d|\n", list[i].productId, list[i].categoryId, list[i].productName, list[i].quantity, list[i].price);
			printf("|------------|------------|------------|----------|-------|\n");
		}
	}
};

//ham` them san? pham? vao` 
void addProduct(struct product* $product, int* size, struct category* _category, int* length, int status)
{
	if (status) {
		struct product temporary;
		struct product list[MAX];
		int count = 0;
		FILE* file = fopen("product.bin", "rb");
		while (fread(&temporary, sizeof(struct product), 1, file)) {
			list[count] = temporary;
			count++;
		}
		fclose(file);
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
						printf("Id product already exist in RAM. \n");
						break;
					}
					if (isFounded(temp.productName, $product[j].productName)) {
						isValid = 0;
						printf("Product already exist in RAM. \n");
						break;
					}
				}
				for (int j = 0;j < count;j++) {
					if (isFounded(temp.productId, list[i].productId)) {
						isValid = 0;
						printf("Id product already exist in file\n");
						break;
					}
					if (isFounded(temp.productName, list[i].productName)) {
						isValid = 0;
						printf("Product already exist in file\n");
						break;
					}
				}

				if (!isValid)	continue;
				printf("Enter category Id: ");
				scanf_s(" %[^\n]", temp.categoryId, (unsigned)sizeof(temp.categoryId));
				getchar();
				printf("Enter quantity of product: ");
				//while (!isdigit(scanf_s("%d", &temp.quantity))) {
				while (scanf_s("%d", &temp.quantity) != 1 || temp.quantity < 0) {
					printf("Invalid! Please enter a digit: ");
					while (getchar() != '\n');
				}
				getchar();
				printf("Enter price of product: ");
				//while (!isdigit(scanf_s("%d", &temp.price))) {
				while (scanf_s("%d", &temp.price) != 1 || temp.price < 0) {
					printf("Invalid! Please enter a digit: ");
					while (getchar() != '\n');
				}
				getchar();
			}
			//kiem? tra ton` tai. cua? danh muc., neu' chua thi them vao` danh muc. moi'
			int flag = 1;
			for (int t = 0;t < *length;t++) {
				if (strcmp(temp.categoryId, _category[t].categoryId) == 0 && strcmp(temp.categoryId, list[i].categoryId) == 0) {
					flag = 0;	//vao` if tuc' la` category da~ ton` tai.
				}
			}
			if (flag) {		//category Id chua ton` tai. thi` them moi' vao`
				printf("Category does not exist! Need to add!!\n");
				struct category temp;
				struct category _temp;
				struct category _list[MAX];
				int _size = 0;
				FILE* file = fopen("category.bin", "rb");
				while (fread(&_temp, sizeof(struct category), 1, file)) {
					_list[_size] = _temp;
					_size++;
				}
				fclose(file);
				int isTrue = 0;
				while (!isTrue) {
					isTrue = 1;	//gia? su? DL hop. le. otherwise =0
					printf("Category Id: ");
					scanf_s(" %[^\n]", temp.categoryId, (unsigned)sizeof(temp.categoryId));
					getchar();
					printf("Category Name: ");
					scanf_s(" %[^\n]", temp.categoryName, (unsigned)sizeof(temp.categoryName));
					getchar();
					if (strlen(temp.categoryId) == 0 || strlen(temp.categoryName) == 0) {
						isTrue = 0;
						printf("Id or Name invalid!!\n");
						continue;
					}
					for (int j = 0;j < *size;j++) {
						if (isFounded(temp.categoryId, _category[j].categoryId)) {
							printf("Category Id already exist!!\n");
							isTrue = 0;
							break;
						}
						if (isFounded(temp.categoryName, _category[j].categoryName)) {
							printf("Category name already exist!!\n");
							isTrue = 0;
							break;
						}
					}
					for (int j = 0;j < _size;j++) {
						if (isFounded(temp.categoryId, _list[i].categoryId)) {
							isValid = 0;
							printf("Id of category already exist in file\n");
							break;
						}
						if (isFounded(temp.categoryName, _list[i].categoryName)) {
							isValid = 0;
							printf("Category already exist in file\n");
							break;
						}
					}
				}
				_category[*length] = temp;
				(*length)++;
			}
			printf("ADD SUCESS\n");
			$product[*size] = temp;
			(*size)++;
			printf("\n");
		}
	}
	else {
		printf("Must be admin to acess!!\n");
		return;
	}
};

//ham` chinh? sua? thong tin san? pham? (khong sua? id)
void editProduct(struct product* _product, int size, int status)
{
	if (status) {
		struct product temporary;
		struct product list[MAX];
		int count = 0;
		FILE* file = fopen("product.bin", "rb");
		while (fread(&temporary, sizeof(struct product), 1, file)) {
			list[count] = temporary;
			count++;
		}
		fclose(file);
		int index = -1;
		char Id[10];
		printf("Enter product Id to edit: ");
		scanf_s(" %[^\n]", Id, 10);
		getchar();
		struct product temp;
		for (int i = 0;i < size;i++) {
			if (isFounded(Id, _product[i].productId)) {
				index = i;
				int isValid = 0;
				while (!isValid) {
					isValid = 1;
					strcpy(temp.productId, Id);
					printf("Enter product name: ");
					scanf_s(" %[^\n]", temp.productName, (unsigned)sizeof(temp.productName));
					getchar();
					if (strlen(temp.productName) == 0) {
						printf("Name invalid\n");
						isValid = 0;
						continue;
					}

					for (int j = 0;j < size;j++) {
						if (isFounded(temp.productName, _product[j].productName)) {
							isValid = 0;
							printf("Product already exist. Other choice to edit\n");
							break;
						}
					}
					for (int j = 0;j < count;j++) {
						if (isFounded(temp.productId, list[i].productId)) {
							isValid = 0;
							printf("Id product already exist in file\n");
							break;
						}
						if (isFounded(temp.productName, list[i].productName)) {
							isValid = 0;
							printf("Product already exist in file\n");
							break;
						}
					}
					if (!isValid)	continue;
					printf("Enter category Id: ");
					scanf_s(" %[^\n]", temp.categoryId, (unsigned)sizeof(temp.categoryId));
					getchar();
					printf("Enter quantity of product: ");
					while (scanf_s("%d", &temp.quantity) != 1) {
						printf("Invalid! Please enter a digit: ");
						while (getchar() != '\n');
					}
					getchar();
					printf("Enter price of product: ");
					while (scanf_s("%d", &temp.price) != 1) {
						printf("Invalid! Please enter a digit: ");
						while (getchar() != '\n');
					}
					getchar();

				}
				_product[index] = temp;
				printf("EDIT SUCCESS!!!\n");
				printf("\n");
				break;
			}
		}
		if (!index) {
			printf("Cannot found Id!!\n");
		}
	}
	else {
		printf("Must be admin to acess!!\n");
		return;
	}
}

//ham` xoa' san? pham? 
void delProduct(struct product* _product, int* size, int status)
{
	if (status) {
		char Id[10];
		int flag = 1;
		printf("Enter product Id to delete: ");
		scanf_s(" %[^\n]", Id, 10);
		getchar();
		for (int i = 0;i < *size;i++) {
			if (isFounded(Id, _product[i].productId)) {
				flag = 0;
				for (int j = i;j < *size - 1;j++) {
					_product[j] = _product[j + 1];
				}
				(*size)--;
				printf("Deleted successfully!!!\n");
			}
		}
		if (flag) {
			printf("Cannot found Id!!!\n");
		}
	}
	else {
		printf("Must be admin to acess!!\n");
		return;
	}
};


//ham` tim` kiem' san? pham? theo ten
void searchProductByName()
{
	//giong' nhu ben tren logic dau` hoi sai sai
	//lay' tu` file ra de? tim kiem'
	FILE* file = fopen("product.bin", "rb");
	if (file == NULL) {
		printf("No product exist\n");
		return;
	}
	int size = 0;
	struct product temp1;
	struct product temp2[MAX];
	while (fread(&temp1, sizeof(struct product), 1, file)) {
		temp2[size] = temp1;
		size++;
	}
	fclose(file);

	char name[10];
	printf("Enter part of product name  to find: ");
	int flag = 1, first = 1;
	scanf_s(" %[^\n]", name, 10);
	getchar();
	for (int i = 0;i < size;i++) {
		//if (isFounded(name, _product[i].productName)) {		tim` kiem' tuyet. doi'
		//	flag = 0;
		//	printf("Founded! Here is information about product\n");
		//	printf("|------------|------------|------------|----------|-------|\n");
		//	printf("|%-12s|%-12s|%-12s|%-10s|%-7s|\n", "Product Id", "Category Id", "Product Name", "Quantity", "Price");
		//	printf("|------------|------------|------------|----------|-------|\n");
		//	printf("|%-12s|%-12s|%-12s|%10d|%7d|\n", _product[i].productId, _product[i].categoryId, _product[i].productName, _product[i].quantity, _product[i].price);
		//	printf("|------------|------------|------------|----------|-------|\n");
		//	break;
		//}
		if (strstr(temp2[i].productName, name) != NULL) {	//tim` kiem tuong doi'
			flag = 0;
			if (first) {
				first = 0;
				printf("Founded! Here is information about product\n");
				printf("|------------|------------|------------|----------|-------|\n");
				printf("|%-12s|%-12s|%-12s|%-10s|%-7s|\n", "Product Id", "Category Id", "Product Name", "Quantity", "Price");
				printf("|------------|------------|------------|----------|-------|\n");
			}
			printf("|%-12s|%-12s|%-12s|%10d|%7d|\n", temp2[i].productId, temp2[i].categoryId, temp2[i].productName, temp2[i].quantity, temp2[i].price);
			printf("|------------|------------|------------|----------|-------|\n");
		}
	}
	if (flag) {
		printf("Cannot found product!!\n");
	}
}

//sap' xep' san? pham? theo gia'
void arrangeProductByPrice(struct product* _product, int size, int status)
{
	int command;
	printf("1. Ascending\t2. Decreasing\tOther. Out\n");
	printf("your choice: ");
	scanf_s("%d", &command);
	getchar();
	switch (command)
	{
	case 1:
	{
		for (int i = 0;i < size - 1;i++) {
			if (_product[i].price > _product[i + 1].price) {
				struct product temp;
				temp = _product[i];
				_product[i] = _product[i + 1];
				_product[i + 1] = temp;
			}
		}
		printf("Sorted sucessfully!!\n");
		break;
	}
	case 2:
	{
		for (int i = 0;i < size - 1;i++) {
			if (_product[i].price < _product[i + 1].price) {
				struct product temp;
				temp = _product[i];
				_product[i] = _product[i + 1];
				_product[i + 1] = temp;
			}
		}
		printf("Sorted sucessfully!!\n");
		break;
	}
	default:
		printf("Out without doing anything\n");
		return;
	}
	if (status) {

		printProductList(_product, size, 1);
	}
	else {
		printProductList(_product, size, 0);
	}
};


//ham` loc san? pham?
void filterProduct()
{
	//hoi sai sai phai? lay' du~ lieu. tu` file ma` loc. chu'
	int command;
	printf("1. Filter by category\t2. Filter by price\tOther input: Out\n");
	printf(">>Your choice: ");
	scanf_s("%d", &command);
	getchar();
	int start, end, flag = 1, first = 1;
	char Id[10];
	FILE* file = fopen("product.bin", "rb");
	if (file == NULL) {
		printf("No data for you to find\n");
		return;
	}
	int size = 0;
	struct product temp;
	struct product $product[MAX];
	while (fread(&temp, sizeof(struct product), 1, file)) {
		$product[size] = temp;
		size++;
	}
	fclose(file);

	switch (command)
	{
	case 1:	//loc. danh muc.
		printf("Enter part of category Id to filter: ");
		scanf_s(" %[^\n]", Id, 10);
		for (int i = 0;i < size;i++) {
			if (strstr($product[i].productId, Id) != NULL) {
				flag = 0;
				if (first) {
					first = 0;
					printf("Here is information about product:\n");
					printf("|------------|------------|------------|----------|-------|\n");
					printf("|%-12s|%-12s|%-12s|%-10s|%-7s|\n", "Product Id", "Category Id", "Product Name", "Quantity", "Price");
				}
				printf("|------------|------------|------------|----------|-------|\n");
				printf("|%-12s|%-12s|%-12s|%10d|%7d|\n", $product[i].productId, $product[i].categoryId, $product[i].productName, $product[i].quantity, $product[i].price);
				printf("|------------|------------|------------|----------|-------|\n");
			}
		}
		if (flag) {
			printf("Id not exist\n");
			return;
		}
		break;
	case 2:
		printf("Enter the price range\n");
		printf("Start price: ");
		scanf_s("%d", &start);
		getchar();
		printf("End price: ");
		scanf_s("%d", &end);
		getchar();
		for (int i = 0;i < size;i++) {
			if ($product[i].price >= start && $product[i].price <= end) {
				if (first) {
					first = 0;
					flag = 0;
					printf("Here is information about product in range %d - %d:\n", start, end);
					printf("|------------|------------|------------|----------|-------|\n");
					printf("|%-12s|%-12s|%-12s|%-10s|%-7s|\n", "Product Id", "Category Id", "Product Name", "Quantity", "Price");
				}
				printf("|------------|------------|------------|----------|-------|\n");
				printf("|%-12s|%-12s|%-12s|%10d|%7d|\n", $product[i].productId, $product[i].categoryId, $product[i].productName, $product[i].quantity, $product[i].price);
				printf("|------------|------------|------------|----------|-------|\n");
			}
		}
		if (flag) {
			printf("No products are avaiable in selected range!!\n");
		}
		break;
	default:
		printf("Out without doing anything!\n");
		return;
	}
};

//ham` luu, lay' du~ lieu. san? pham? tu` file
void saveProductData(struct product* _product, int* size, int status)
{
	if (status) {
		int choice;
		printf("1. Load data from file\t2. Save data to file\t0. Back\nEnter your choice: ");
		scanf_s("%d", &choice);
		getchar();

		switch (choice)
		{
		case 1: //mo? file va` lay' du~ lieu. tu` file
		{
			FILE* file = fopen("product.bin", "rb");
			if (file == NULL)
			{
				printf("Cannot open file!!!\n");
				break;
			}
			//fread(size, sizeof(int), 1, file);
			*size = 0;
			struct product temp;
			while (fread(&temp, sizeof(struct product), 1, file)) {
				_product[*size] = temp;
				(*size)++;
			}
			fclose(file);
			printf("Load category from file success!!\n");
			break;
		}
		case 2: //mo? file va` luu du~ lieu vao` file, neu' file chua tao. thi` tao moi' file
		{
			printf("1. Continue wite to file\t2. Write new\tOther: Out\n");
			printf("Enter your choice: ");
			int choose;
			scanf_s("%d", &choose);
			getchar();
			FILE* file;
			switch (choose)
			{
			case 1:
				file = fopen("product.bin", "ab");
				break;
			case 2:
				file = fopen("product.bin", "wb");
				break;
			default:
				printf("Out of command\n");
				return;
			}
			if (file == NULL)
			{
				printf("Error opening file\n");
				break;
			}
			//fwrite(size, sizeof(int), 1, file);
			fwrite(_product, sizeof(struct product), *size, file);
			fclose(file);
			printf("Save category to file success!\n");
			break;
		}
		case 0:
			printf("Back to previous\n");
			return;
		default:
			printf("Out this script without doing anything\n");
			return;
		}
	}
	else {
		printf("Must be admin to acess!!\n");
		return;
	}
};