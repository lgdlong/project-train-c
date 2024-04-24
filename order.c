#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#define MAX_PRODUCTS 50

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
    struct product products[MAX_PRODUCTS];
    int num_products;
    float total_price;
};

void lua_chon(int *choice) {
    printf("Moi nhap lua chon: ");
    scanf("%d", choice);
    printf("\n");
}

void work_with_order(struct product *products) {
    int maxproducts = 50;

    int choice;

    do {
        ds_1();
        lua_chon(&choice);

        switch (choice) {
            case 1: // Làm việc với sản phẩm
                work_with_san_pham();
                break;
            case 2: // Giỏ hàng: thêm, xóa, sửa số lượng
                work_with_gio_hang();
                break;
            case 3:
            // Đơn mua: thông tin cá nhân, xuất đơn mua

                // BẮT ĐẦU CODE
                int num, choice1;
                printf("1. Them don mua\n");
                printf("2. Xoa don mua\n");
                printf("3. Sua don mua\n");
                printf("4. Quay ve danh sach lua chon truoc do\n");
                printf("\n");

                lua_chon(&choice1);

                do {
                    switch (choice1) {
                        case 1:
                            // --> in ra giỏ hàng

                            // lấy num xong check qua giỏ hàng
                            printf("Moi nhap so thu tu cua san pham can them trong gio hang: ");
                            scanf("%d", num);
                            printf("\n");

                            // thêm product đã check bằng num vào trong container
                        
                        case 2:
                            // chọn product từ trong container
                            printf("Moi nhap so thu tu cua san pham can xoa: ");
                            scanf("%d", num);
                            printf("\n");

                            // xóa product
                        
                        case 3:
                            // chọn product từ trong container
                            printf("Moi nhap so thu tu cua san pham can sua: ");
                            scanf("%d", num);
                            printf("\n");

                            // chỉnh sửa địa chỉ nhận hàng
                        
                        case 4:
                            break;

                        default:
                            printf("Invalid choice!\n");
                    }
                }
                while (choice1 != 4);
                break;

            case 4:
                return;
            
            default:
                printf("Invalid choice!\n");

        }
    } while (choice != 4);
}