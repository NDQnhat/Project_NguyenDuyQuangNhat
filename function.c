#include <stdio.h>
#include "datatype.h"


//ham in menu chinh'
void printMainMenu()
{
	printf("\n***Store Management Using C***\n");
	printf("%5s\n", "CHOOSE YOUR ROLE");
	printf("===============================\n");
	printf("[1] Management Category\n");
	printf("[2] Management Product\n");
	printf("[3] Identify Admin\n");
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

//ham` hien. danh sach' danh muc.
void printCategoryList(struct category *_category, int size)
{
	if(size==0){
		printf("Category is not exist\n");
	} else {
		printf("\n******Category List*****\n");
		int i=0;
		for(; i<size; i++){		//[Error] 'for' loop initial declarations are only allowed in C99 or C11 mode
			printf("ID: %s, Name: %s\n", _category[i].categoryId, _category[i].categoryName);
		}
	}
};

//ham` them danh muc.
void addCategory(struct category *_category, int *size)
{
	int quantity;
	printf("Enter number of category to add: ");
	scanf("%d", &quantity);
	fflush(stdin);
	int i=0;
	for(; i<quantity; i++){		//[Error] 'for' loop initial declarations are only allowed in C99 or C11 mode
		printf("Category Id: ");
		scanf(" %[^\n]", _category[i].categoryId);
		fflush(stdin);
		printf("Category Name: ");
		scanf(" %[^\n]", _category[i].categoryName);
		fflush(stdin);
		(*size)++;
	}	
};



//ham quan li danh muc
void manageCategory(int *command, struct category *_categoryList, int *size)
{
	while(1)
	{
		printManagementCategoryMenu();
		scanf("%d", command);
		if(*command>=1 &&*command<=8){
			switch(*command)
			{
				case 1:
					printCategoryList(_categoryList, *size);
					break;
				case 2:
					addCategory(_categoryList, size);
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
					printf("Out Of Interface\n");
					return;
			}
		} else{
			printf("Please Enter Again\n");
		}
	}
};




//ham` quan? li' san? pham?
void manageProduct(int *command, struct product *_productList, int *size)
{
	while(1)
	{
		printManagementProductMenu();
		scanf("%d", command);
		if(*command>=1 &&*command<=9){
			switch(*command)
			{
				case 1:
					break;
				case 2:
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
		} else{
			printf("Please Enter Again\n");
		}
	}
};
