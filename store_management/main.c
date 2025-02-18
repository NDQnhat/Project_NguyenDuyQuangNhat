#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "function.h"
#include "category.h"
#include "product.h"

#define MAX 100 


int main(int argc, char* argv[])
{
	int command, countCategory = 0, countProduct = 0, status=0, countOrder=0;
	const char* checkCode = "WhyDoBirdsFly?";
	struct category categoryList[MAX];
	struct product productList[MAX];
	struct order orderList[MAX];
	while (1)
	{
		printMainMenu();
		scanf_s("%d", &command);
		getchar();
		if (command >= 0 && command <= 4) {	//du. tinh' lam` 1 bien' command de? dieu` huong' tat' ca? cac' ham`
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
					pressEnterToExit();
				}
				break;
			}
			case 4:
				printf("Out Of Program\n");
				return 0;
			case 0:
				system("cls");
				if (status) {
					viewBillList(orderList, &countOrder);
				}
				else {
					printf("MUST BE ADMIN TO DO THIS!!!\n");
					pressEnterToExit();
				}
				break;
			}
		}
		else {
			printf("Please Enter Again\n");
		}
	}
	return 0;
}