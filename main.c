#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Product {
    char productName[100];
    int quantity;
    double price;
};

void readProductsFromFile(struct Product *products, int *product_count) {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    while (fscanf(file, "%99[^,], %d, %lf\n", products[*product_count].productName, &products[*product_count].quantity, &products[*product_count].price) == 3) {
        (*product_count)++;
    }

    fclose(file);
}

void writeProductsToFile(struct Product *products, int product_count) {
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }
	int i;
    for (i = 0; i < product_count; i++) {
        fprintf(file, "%s, %d, %.2lf\n", products[i].productName, products[i].quantity, products[i].price);
    }

    fclose(file);
}

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

    writeProductsToFile(products, *product_count);
}

void displayProducts(struct Product *products, int product_count) {
    printf("\nDanh sach san pham:\n");
    int i;
    for (i = 0; i < product_count; i++) {
        printf("San pham %d:\n", i + 1);
        printf("Ten: %s\n", products[i].productName);
        printf("So luong: %d\n", products[i].quantity);
        printf("Gia: %.2lf\n\n", products[i].price);
    }
}

void editProduct(struct Product *products, int product_count) {
    int index;
    displayProducts(products, product_count);

    printf("Nhap so thu tu cua san pham muon sua: ");
    scanf("%d", &index);
    index--;

    if (index >= 0 && index < product_count) {
        printf("Ten san pham moi: ");
        getchar();
        fgets(products[index].productName, sizeof(products[index].productName), stdin);
        products[index].productName[strcspn(products[index].productName, "\n")] = '\0';

        printf("So luong moi: ");
        scanf("%d", &products[index].quantity);

        printf("Gia moi: ");
        scanf("%lf", &products[index].price);

        printf("Cap nhat san pham thanh cong!\n");

        writeProductsToFile(products, product_count);
    } else {
        printf("So thu tu khong hop le!\n");
    }
}

void deleteProduct(struct Product *products, int *product_count) {
    int index;
    displayProducts(products, *product_count);

    printf("Nhap so thu tu cua san pham muon xoa: ");
    scanf("%d", &index);
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

int main() {
    struct Product products[50];
    int product_count = 0;
    int choice;

    readProductsFromFile(products, &product_count);

    do {
        printf("\nMenu:\n");
        printf("1. Them san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Chinh sua thong tin san pham\n");
        printf("4. Xoa san pham\n");
        printf("5. Thoat chuong trinh\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(products, &product_count);
                break;
            case 2:
                displayProducts(products, product_count);
                break;
            case 3:
                editProduct(products, product_count);
                break;
            case 4:
                deleteProduct(products, &product_count);
                break;
            case 5:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while (choice != 5);

    return 0;
}

