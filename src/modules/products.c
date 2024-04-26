#include "../../include/libaries_and_define.h"
#include "../../include/products.h"
#include "../../include/file.h"

struct product {
    char productName[MAX_NAME_LENGTH];
    int quantity;
    double price;
    int code; // Mã sản phẩm
};

// WORK WITH PRODUCTS
void displayProducts(struct product *products, int product_count) {
    printf("\nDanh sach san pham:\n");
    int i;
    for (i = 0; i < product_count; i++) {
        printf("San pham %d:\n", i + 1);
        printf("Ten: %s\n", products[i].productName);
        printf("So luong: %d\n", products[i].quantity);
        printf("Gia: %.2lf\n", products[i].price);
        printf("Ma san pham: %d\n\n", products[i].code); //Moi them dong nay
    }
}

void addProduct(struct product *products, int *product_count) {
    printf("Nhap ten san pham: ");
    getchar(); 
    fgets(products[*product_count].productName, sizeof(products[*product_count].productName), stdin);
    products[*product_count].productName[strcspn(products[*product_count].productName, "\n")] = '\0';

    int quantity;
    do {
        printf("Nhap so luong: ");
        if (scanf("%d", &quantity) != 1) {
            printf("Loi nhap! Vui long nhap lai.\n");
            while(getchar() != '\n');
            continue;
        }
        if (quantity <= 0) {
            printf("So luong phai la so duong. Vui long nhap lai.\n");
        }
    } while (quantity <= 0);

    products[*product_count].quantity = quantity;

    double price;
    char buffer[100];
    bool validPrice = false;
    while (!validPrice) {
        printf("Nhap gia san pham: ");
        if (scanf("%s", buffer) != 1 || sscanf(buffer, "%lf", &price) != 1) {
            printf("Loi nhap! Vui long nhap lai.\n");
            while(getchar() != '\n');
            continue;
        }
        if (price <= 0) {
            printf("Gia san pham phai la so duong. Vui long nhap lai.\n");
        } else {
            validPrice = true;
        }
    }

    products[*product_count].price = price;

    products[*product_count].code = *product_count; //Moi them dong nay
    
    (*product_count)++;

    writeProductsToFile(products, *product_count);
}

void editProduct(struct product *products, int product_count) {
    int index;
    displayProducts(products, product_count);

    printf("Nhap so thu tu cua san pham muon sua: ");
    if (scanf("%d", &index) != 1) {
        printf("Vui long nhap mot chu so!\n");
        while (getchar() != '\n');
        return;
    }
    index--;

    if (index >= 0 && index < product_count) {
        printf("Ten san pham moi: ");
        getchar();
        fgets(products[index].productName, sizeof(products[index].productName), stdin);
        products[index].productName[strcspn(products[index].productName, "\n")] = '\0';

        int quantity;
        do {
            printf("Nhap so luong moi: ");
            if (scanf("%d", &quantity) != 1) {
                printf("Loi nhap! Vui long nhap lai.\n");
                while (getchar() != '\n');
                continue;
            }
            if (quantity <= 0) {
                printf("So luong phai la so duong. Vui long nhap lai.\n");
            }
        } while (quantity <= 0);
        products[index].quantity = quantity;

    double price;
    char buffer[100];
    bool validPrice = false;
    while (!validPrice) {
        printf("Nhap gia san pham: ");
        if (scanf("%s", buffer) != 1 || sscanf(buffer, "%lf", &price) != 1) {
            printf("Loi nhap! Vui long nhap lai.\n");
            while(getchar() != '\n');
            continue;
        }
        if (price <= 0) {
            printf("Gia san pham phai la so duong. Vui long nhap lai.\n");
        } else {
            validPrice = true;
        }
    }
    products[index].price = price;
    printf("Cap nhat san pham thanh cong!\n");
    } else {
        printf("So thu tu khong hop le!\n");
    }
}

void deleteProduct(struct product *products, int *product_count) {
    int index;
    displayProducts(products, *product_count);

    printf("Nhap so thu tu cua san pham muon xoa: ");
    if(scanf("%d", &index) != 1) {
        printf("Vui long nhap mot chu so!\n");
        while(getchar() != '\n');
        return;
    }
    index--;
	int i;
    if (index >= 0 && index < *product_count) {
        for (i = index; i < *product_count - 1; i++) {
            products[i] = products[i + 1];
        }
        (*product_count)--;
        printf("Xoa san pham thanh cong!\n");

        writeProductsToFile(products, *product_count);
    } else {
        printf("So thu tu khong hop le!\n");
    }
}