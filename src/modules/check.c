#include "../../include/libaries_and_define.h"

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

bool isPaymentComplete(struct cart cart) {
    return cart.payment_status == 1;
}

bool isValidQuantity(int quantity) {
    return quantity > 0;
}

bool isValidIndex(int index, int array_size) {
    return index >= 0 && index < array_size;
}

int getIntegerInput() {
    int input;
    while (scanf("%d", &input) != 1) {
        printf("Nhap khong hop le! Moi nhap lai: ");
        scanf("%*s");
    }
    return input;
}

bool isProductInCart(int code_of_product, struct cart cart) {
    for (int i = 0; i < cart.num_products; i++) {
        if (cart.products[i].code == code_of_product) {
            return true;
        }
    }
    return false;
}

bool isValidCartInput(int code_of_product, int quantity, struct product *products, int product_count) {
    if (!isValidIndex(code_of_product - 1, product_count)) {
        printf("Ma san pham khong hop le!\n");
        return false;
    }
    if (!isValidQuantity(quantity)) {
        printf("So luong khong hop le!\n");
        return false;
    }
    if (quantity > products[code_of_product - 1].quantity) {
        printf("So luong khong du trong kho!\n");
        return false;
    }
    return true;
}
