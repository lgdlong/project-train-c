#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Product {
    char productName[50];
    int quantity;
    double price;
};

void addProduct(struct Product *products, int *product_count) {
    printf("Nhap ten san pham: ");
    getchar(); 
    fgets(products[*product_count].productName, sizeof(products[*product_count].productName), stdin);
    products[*product_count].productName[strcspn(products[*product_count].productName, "\n")] = '\0';

    printf("Nhap so luong: ");
    scanf("%d", &products[*product_count].quantity);

    printf("Nhap gia san pham: ");
    scanf("%lf", &products[*product_count].price);

    (*product_count)++;
}

void displayProducts(struct Product *products, int product_count) {
    printf("\nSan pham:\n");
    int i;
    for (i = 0; i < product_count; i++) {
    	int j=i+1;
        printf("So: %d | ", j);
        printf("Ten san pham: %s | ", products[i].productName);
        printf("So luong: %d | ", products[i].quantity);
        printf("Gia: %.3lf | ", products[i].price);
        printf("\n");
    }
}

void fixProducts(struct Product *products, int product_count){
	int i;
	printf("Nhap so cua san pham muon thay doi: ");
	scanf("%d", &i);
	
	int j=i-1;
	
	if(j>0 && i<= product_count)
	{
	printf("Nhap ten moi cho san pham: ");
	getchar();
        fgets(products[j].productName, sizeof(products[j].productName), stdin);
        products[j].productName[strcspn(products[j].productName, "\n")] = '\0';

        printf("Nhap so luong moi: ");
        scanf("%d", &products[j].quantity);

        printf("Nhap gia moi: ");
        scanf("%lf", &products[j].price);

        printf("Thong tin san pham da cap nhat thanh cong!\n");
    } else {
        printf("So nay khong phu hop!\n");
    }
}

int main() {
    struct Product products[50];
    int product_count = 0;
    int choice;

    do {
        printf("\n1. Them san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Chinh sua san pham da them\n");
        printf("4. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addProduct(products, &product_count);
                break;
            case 2:
                displayProducts(products, product_count);
                break;
            case 3:
                fixProducts(products, product_count);
                break;
            case 4:
            	printf("Ket thuc chuong trinh.\n");
            	break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while(choice != 4);

    return 0;
}

