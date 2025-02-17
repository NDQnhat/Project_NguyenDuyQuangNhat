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

//ham` hien. danh sach' danh muc.
void printCategoryList(struct category* _category, int size, int status)
{
	if (status) {
		if (size == 0) {
			printf("Category is not exist\n");
		}
		else {
			printf("\n%s\n", "*******Category List******");
			printf("\n");
			printf("|----------|----------|\n");
			printf("|%-10s|%-10s|\n", "Id", "Name");
			printf("|----------|----------|\n");
			for (int i = 0; i < size; i++) {
				printf("|%-10s|%-10s|\n", _category[i].categoryId, _category[i].categoryName);
				printf("|----------|----------|\n");
			}
		}
	}
	else {
		int length = 0;
		FILE* file = fopen("category.bin", "rb");
		struct category temp;
		struct category list[MAX];
		while (fread(&temp, sizeof(struct category), 1, file)) {
			list[length] = temp;
			length++;
		}
		printf("\n%s\n", "*******Category List******");
		printf("\n");
		printf("|----------|----------|\n");
		printf("|%-10s|%-10s|\n", "Id", "Name");
		printf("|----------|----------|\n");
		for (int i = 0; i < length; i++) {
			printf("|%-10s|%-10s|\n", list[i].categoryId, list[i].categoryName);
			printf("|----------|----------|\n");
		}
	}
};

//ham` them danh muc.
void addCategory(struct category* _category, int* size, int status)
{

	if (status) {
		FILE* file = fopen("category.bin", "rb");
		struct category $temp;
		struct category list[MAX];
		int count = 0;
		while (fread(&$temp, sizeof(struct category), 1, file)) {
			list[count] = $temp;
			count++;
		}
		fclose(file);
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
						printf("Category Id already exist in RAM!!\n");
						isValid = 0;
						break;
					}
					if (isFounded(temp.categoryName, _category[j].categoryName)) {
						printf("Category name already exist in RAM!!\n");
						isValid = 0;
						break;
					}
				}
				for (int j = 0;j < count;j++) {
					if (isFounded(temp.categoryId, list[j].categoryId)) {
						printf("Category Id already exist in file!!\n");
						isValid = 0;
						break;
					}
					if (isFounded(temp.categoryName, list[j].categoryName)) {
						printf("Category name already exist in file!!\n");
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
		FILE* file = fopen("category.bin", "rb");
		struct category $temp;
		struct category list[MAX];
		int count = 0;
		while (fread(&$temp, sizeof(struct category), 1, file)) {
			list[count] = $temp;
			count++;
		}
		fclose(file);
		int flag = 1;
		printf("Enter ID to edit: ");
		char identify[10];
		scanf_s(" %[^\n]", identify, 10);
		getchar();
		for (int i = 0; i < size; i++) {
			if (isFounded(identify, _category[i].categoryId)) {
				flag = 0;
				int isValid = 0;
				printf("ID: %s, Name: %s\n", _category[i].categoryId, _category[i].categoryName); //hien thong tin dah muc hien tai va sua
				struct category temp;
				while (!isValid) {
					isValid = 1;
					printf("Name to change: ");
					scanf_s(" %[^\n]", temp.categoryName, 10);
					if (strlen(temp.categoryName) == 0) {
						isValid = 0;
						printf("Name invalid!!\n");
						continue;
					}
					for (int j = 0;j < size;j++) {
						if (isFounded(temp.categoryName, _category[j].categoryName)) {
							printf("Category name already exist in RAM!!\n");
							isValid = 0;
							break;
						}
					}
					for (int j = 0;j < count;j++) {
						if (isFounded(temp.categoryName, list[j].categoryName)) {
							printf("Category name already exist in file!!\n");
							isValid = 0;
							break;
						}
					}
				}
				strcpy(_category[i].categoryName, temp.categoryName);
				break;
			}
		} if (flag) {
			printf("Cannot found the ID in category in RAM\n");
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
void arrangeByName(struct category* $category, int size, int status)
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
	if (status) {
		printCategoryList($category, size, 1);
	}
	else {
		printCategoryList($category, size, 0);
	}
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
