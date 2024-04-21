#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

#include "menu.c"

struct product {
    char productName[50];
    int quantity;
    double price;
};

struct order {
    struct product products;
    int num_products;
    float total_price;
    char buyer_name;
    char address;
    char phone;
    char payment_method;
    char payment_status;
};

struct cart {
    struct product products;
    int num_products;
    float total_price;
    char customer_id;
};

void menu() {
    int choice; // menu mẹ
    int choice1; // menu con cấp 1
    int choice2; // menu con cấp 2

    do {
        ds_1();
        lua_chon(&choice);

        switch (choice) {
            case 1: // Làm việc với sản phẩm
                work_with_san_pham(choice1);
            case 2: // Đơn mua: thông tin cá nhân, xuất đơn mua
                work_with_don_mua();
                break;

            case 3: // Giỏ hàng: thêm, xóa, sửa số lượng
                work_with_gio_hang();
                break;

            case 4:
                break;
            
            default:
                printf("Invalid choice!\n");

        }
    } while (1);
}

void add_product(struct product prod) {

}

int main() {
    menu();

    return 0;
}