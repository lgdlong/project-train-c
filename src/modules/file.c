#include "../../include/libaries_and_define.h"
#include "../../include/file.h"
#include "../../include/products.h"
#include "../../include/carts.h"
#include "../../include/orders.h"
#include "../../include/check.h"

struct product {
    char productName[MAX_NAME_LENGTH];
    int quantity;
    double price;
    int code; // Mã sản phẩm
};

struct cart {
    struct product products[MAX_PRODUCTS];
    struct customer_inf *customer;
    int num_products;
    float total_price;
    int payment_status; // Trạng thái thanh toán (0: Chưa thanh toán, 1: Đã thanh toán)
};


// WORK WITH FILE
void readProductsFromFile(struct product *products, int *product_count) { // Hàm đọc sản phẩm của Trân
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    while (fscanf(file, "%99[^,], %d, %lf, %d\n", products[*product_count].productName, &products[*product_count].quantity, &products[*product_count].price, &products[*product_count].code) == 4) {
        (*product_count)++;
    }

    fclose(file);
}

void writeProductsToFile(struct product *products, int product_count) { //Hàm viết sản phẩm của Trân
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    for (int i = 0; i < product_count; i++) {
        fprintf(file, "%s, %d, %.2lf, %d\n", products[i].productName, products[i].quantity, products[i].price, products[i].code);
    }

    fclose(file);
}

void deleteFileContents(const char *filename) { //Hàm xóa tất cả dữ liệu trong file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    fclose(file);
}

void updateProductsFile(struct product *products, int product_count) { //Hàm cập nhật lại số lượng sản phẩm sau khi thêm hoặc bớt sản phẩm
    deleteFileContents("products.txt");
    writeProductsToFile(products, product_count);
}

void ExportOrderIntoFile(struct cart *cart) {
    if (isPaymentComplete(*cart) == true) {
        FILE *file = fopen("order.txt", "w");
        if (file == NULL) {
            printf("Khong the mo file.\n");
            return;
        }
        for (int i = 0; i < cart->num_products; i++) {
            fprintf(file, "%s, %d, %.2lf\n", cart->products[i].productName, cart->products[i].quantity, cart->products[i].price);
        }
        fclose(file);
    } else {
        printf("Khong the xuat don hang vi chua thanh toan!\n");
    }
}
