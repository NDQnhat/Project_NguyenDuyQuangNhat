#define _CRT_SECURE_NO_WARNINGS		//visual studio noi' fopen khong bao? mat va` yeu cau` dung` fopen_s

#include <stdio.h>
#include "datatype.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

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
void addCategory(struct category* _category, int* size, int status)
{
	if (status) {
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
					isValid = 0;
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
	}
	else {
		printf("Must be admin to access!!\n");
		return;
	}
};


//ham` chinh? sua? danh muc.
void editCategory(struct category* _category, int size, int status)
{
	if (status) {
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
	}
	else {
		printf("Must be admin to acess!!\n");
		return;
	}
};

//ham` xoa' san? pham?
void delCategory(struct category* _category, int* size, int status)
{
	if (status) {
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
		}
		if (flag) {
			printf("ID not exist!!\n");
		}
	}
	else {
		printf("Must be admin to acess!!\n");
		return;
	}
};

//ham` tim` kiem' danh muc. theo ten
void searchByName()	//truyen` tham tri. vao _category vi` ham` isFounded can truyen con tro?
{
	//hoi sai sai nen tim` tu` trong file neu' khong user lai. mau thuan~ voi' admin

	//lay' tu` file ra de? tim kiem'
	FILE* file = fopen("category.bin", "rb");
	if (file == NULL) {
		printf("No category exist\n");
		return;
	}
	int size = 0;
	struct category temp1;
	struct category temp2[MAX];
	while (fread(&temp1, sizeof(struct category), 1, file)) {
		temp2[size] = temp1;
		size++;
	}
	fclose(file);

	char name[10];
	int flag = 1, _flag = 1;
	printf("Enter a part of category name to find: ");
	scanf_s(" %[^\n]", name, 10);
	for (int i = 0;i < size;i++) {
		//if (isFounded(name, _category[i].categoryName)) {		//tim` tuyet. doi'
		//	flag = 0;
		//	printf("Information about %s:\n", name);
		//	printf("ID: %s, Name: %s\n", _category[i].categoryId, _category[i].categoryName);
		//	break;
		//}
		if (strstr(temp2[i].categoryName, name) != NULL) {		//tim` tuong doi', chi? can` nhap. 1 phan` ten
			flag = 0;
			if (_flag) {
				printf("Information about '%s':\n", name);	//kiem? tra lan` dau`
				_flag = 0;
			}
			printf("ID: %s, Name: %s\n", temp2[i].categoryId, temp2[i].categoryName);
		}
	}
	if (flag) {
		printf("Cannot found category!!\n");
	}
};

//ham` sap' theo ten
void arrangeByName(struct category* $category, int size)
{
	printf("1. Ascending\t2. Decreasing\tOther: Out\n");
	printf("Enter your choice: ");
	int choice;
	scanf_s("%d", &choice);
	getchar();
	switch (choice)
	{
	case 1:
		for (int i = 0;i < size - 1;i++) {
			for (int j = 0;j < size - i - 1;j++) {
				if (strcmp($category[j].categoryName, $category[j + 1].categoryName) > 0) {
					struct category temp = $category[j];
					$category[j] = $category[j + 1];
					$category[j + 1] = temp;
				}
			}
		}
		printf("Arrange Success!\n");
		break;
	case 2:
		for (int i = 0;i < size - 1;i++) {
			for (int j = 0;j < size - i - 1;j++) {
				if (strcmp($category[j].categoryName, $category[j + 1].categoryName) < 0) {
					struct category temp = $category[j];
					$category[j] = $category[j + 1];
					$category[j + 1] = temp;
				}
			}
		}
		printf("Arrange Success!\n");
		break;
	default:
		printf("Out without doing anything\n");
		return;
	}
	printCategoryList($category, size);
};

//ham` lay' du~ lieu. tu` file
//void loadDataFromFile(const char* fileName, const char* mode, int *size, struct category* _category)
//{
//	FILE* file = fopen("fileName", "mode");
//	if (file == NULL)
//	{
//		printf("Cannot open file!!!\n");
//	}
//	//fread(size, sizeof(int), 1, file);
//	*size = 0;		//co' the? khong can` ??????, neu' da~ co' phan tu? trong ram???
//	struct category temp;
//	while (fread(&temp, sizeof(struct category), 1, file)) {
//		_category[*size] = temp;
//		(*size)++;
//	}
//	fclose(file);
//	printf("Load category from file success!!\n");
//}



//ham` luu du~ lieu. danh muc. vao` file
void saveCategoryData(struct category* _category, int* size, int status)
{
	if (status) {
		int choice;
		printf("1. Load data from file\t2. Save data to file\t0. Back\nEnter your choice: ");
		while (scanf_s("%d", &choice) != 1) {
			printf("Invalid input!!\n");
		}
		getchar();

		switch (choice)
		{
		case 1: //mo? file va` lay' du~ lieu. tu` file
		{
			//const char* fileName = "category.bin";
			//const char* mode = "rb";
			FILE* file = fopen("category.bin", "rb");
			if (file == NULL)
			{
				printf("Cannot open file!!!\n");
				break;
			}
			//fread(size, sizeof(int), 1, file);
			*size = 0;		//co' the? khong can` ??????, neu' da~ co' phan tu? trong ram???
			struct category temp;
			while (fread(&temp, sizeof(struct category), 1, file)) {
				_category[*size] = temp;
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
			int choose, count;
			scanf_s("%d", &choose);
			getchar();
			FILE* file;
			switch (choose)
			{
			case 1:
				file = fopen("category.bin", "ab");
				if (file == NULL)
				{
					printf("Error opening file\n");
					break;
				}
				//count = sizeof(struct category) / sizeof(_category);

				//fwrite(size, sizeof(int), 1, file);	ghi so' luong. vao` file 

				fwrite(_category, sizeof(struct category), *size, file);
				fclose(file);
				printf("Save category to file success!\n");
				break;
			case 2:
				file = fopen("category.bin", "wb");
				if (file == NULL)
				{
					printf("Error opening file\n");
					break;
				}
				//fwrite(size, sizeof(int), 1, file);

				fwrite(_category, sizeof(struct category), *size, file);
				fclose(file);
				printf("Save category to file success!\n");
				break;
			default:
				printf("Out of command\n");
				return;
			}
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
}





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
void addProduct(struct product* $product, int* size, struct category* _category, int* length, int status)
{
	if (status) {
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
				if (strcmp(temp.categoryId, _category[t].categoryId) == 0) {
					flag = 0;	//vao` if tuc' la` category da~ ton` tai.
				}
			}
			if (flag) {		//category Id chua ton` tai. thi` them moi' vao`
				printf("Category does not exist! Need to add!!\n");
				struct category temp;
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
void arrangeProductByPrice(struct product* _product, int size)
{
	int command;
	printf("1. Ascending\t2. Decreasing\tOther. Out\n");
	printf("your choice: ");
	scanf_s("%d", &command);
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
	break;
	default:
		printf("Out without doing anything\n");
		return;
	}
	printProductList(_product, size);
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





//-------------------------------------Ham` dieu` huong' danh muc., san? pham?------------------

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
				printCategoryList(_categoryList, *size);
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
				arrangeByName(_categoryList, *size);
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
				printProductList(_productList, *size);
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
				arrangeProductByPrice(_productList, *size);
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
			scanf_s(" %[^\n]", input.password, 20);
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
			scanf_s(" %[^\n]", input.password, 20);
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