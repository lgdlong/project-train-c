#include "../include/libaries_and_define.h"
#include "../include/products.h"

struct product {
    char productName[MAX_NAME_LENGTH];
    int quantity;
    double price;
    int code; // Mã sản phẩm
};

// WORK WITH PRODUCTS
void displayProducts(struct product *products, int product_count) {
    printf("\nDanh sach san pham:\n");
    for (int i = 0; i < product_count; i++) {
        printf("Ma san pham: %d | Ten san pham: %s | So luong: %d | Gia: %.3lf\n", products[i].code, products[i].productName, products[i].quantity, products[i].price);
    }
}

void addProduct(struct product *products, int *product_count) {
    static int last_product_code = 0;
    
    printf("\nNhap ten san pham: ");
    getchar(); 
    fgets(products[*product_count].productName, sizeof(products[*product_count].productName), stdin);
    products[*product_count].productName[strcspn(products[*product_count].productName, "\n")] = '\0';

    printf("Nhap so luong: ");
    scanf("%d", &products[*product_count].quantity);

    printf("Nhap gia san pham: ");
    scanf("%lf", &products[*product_count].price);

    last_product_code++; // Tăng giá trị của mã sản phẩm cuối cùng
    products[*product_count].code = last_product_code;

    (*product_count)++;
}

void fixProducts(struct product *products, int product_count){
	int i;
	displayProducts(products, product_count);
	printf("Nhap ma san pham muon thay doi: ");
	scanf("%d", &i);
	
	int j=i-1;
	
	if(j>=0 && j< product_count) {
	printf("Nhap ten moi cho san pham: ");
	getchar();
        fgets(products[j].productName, sizeof(products[j].productName), stdin);
        products[j].productName[strcspn(products[j].productName, "\n")] = '\0';

        printf("Nhap so luong moi: ");
        scanf("%d", &products[j].quantity);

        printf("Nhap gia moi: ");
        scanf("%lf", &products[j].price);

        printf("Thong tin san pham da cap nhat thanh cong!\n");
    }
    else {
        printf("So nay khong phu hop!\n");
    }
}
