#include <stdio.h>
#include <stdlib.h>
#include "datatype.h"
#include "function.h"
#define MAX 100 


int main(int argc, char *argv[]) 
{
	int command, countCategory=0, countProduct=0;
	struct category categoryList[MAX];
	struct product productList[MAX];
	while(1)
	{
		printMainMenu();
		scanf("%d", &command);
		fflush(stdin);
		if(command>=1 && command<=4){
			switch(command)
			{
				case 1:
					manageCategory(&command, categoryList, &countCategory);
					break;
				case 2:
					manageProduct(&command, productList, &countProduct);
					break;
				case 3:
					break;
				case 4:
					printf("Out Of Program\n");
					return 0;
			}
		} else {
				printf("Please Enter Again\n");
		}
	}
	return 0;
}
