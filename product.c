#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Product{
	char name[50];
	int quantity;
	float price;
};

void addProduct(struct Product *products, int *product_count)
{
	printf("Nhap ten san pham: ");
	getchar();
	fgets(products[*product_count].name, sizeof(products[*product_count].name, stdin));
	products[*product_count].name[strcspn(products[*product_count].name,"\n")]='\0';
	
	printf("Nhap so luong san pham: ");
	scanf("%d", &products[product_count].quantity);
	
	printf("Nhap gia cua san pham: ");
	scanf("%d", &products[product_count].price);
	
	(*product_count)++;
}
