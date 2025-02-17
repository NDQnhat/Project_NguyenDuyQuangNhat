#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "function.h"
#define MAX 100 


int main(int argc, char* argv[])
{
	int command, countCategory = 0, countProduct = 0, status=0;
	const char* checkCode = "storeManagement";
	struct category categoryList[MAX];
	struct product productList[MAX];
	while (1)
	{
		printMainMenu();
		scanf_s("%d", &command);
		fflush(stdin);
		if (command >= 1 && command <= 4) {
			switch (command)
			{
			case 1:
				system("cls");
				manageCategory(&command, categoryList, &countCategory, status);
				break;
			case 2:
				system("cls");
				manageProduct(&command, productList, &countProduct, categoryList, &countCategory, status);
				break;
			case 3:
			{
				system("cls");
				char code[20];
				printf("Enter authentication code: ");
				scanf_s(" %[^\n]", code, 20);
				getchar();
				if (strcmp(code, checkCode) == 0) {
					identifyAdmin(&status);
				}
				else {
					printf("Wrong!! Ask manager to know authentication code!!\n");
				}
				break;
			}
			case 4:
				printf("Out Of Program\n");
				return 0;
			}
		}
		else {
			printf("Please Enter Again\n");
		}
	}
	return 0;
}