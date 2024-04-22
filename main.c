#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

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
    int maxproducts = 50;

    int choice; // menu mẹ
    // int choice1; // menu con cấp 1
    // int choice2; // menu con cấp 2
    
    int n; // số lượng sản phẩm trong 
    
    struct order *ord = (struct order *)malloc(maxproducts * sizeof(struct order));

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
/*
- bản chất giỏ hàng là một kho lưu tạm dữ liệu đơn hàng trước khi chọn mua
- đơn mua xuất hiện sau khi đã có giỏ hàng
- thông tin về địa chỉ và số điện thoại được lưu ở bên

Thêm, hủy, sửa đơn mua (đơn hàng):

    Thêm một đơn mua
        Chọn số thứ tự
        Thêm món đó từ giỏ hàng vào container đơn mua
    Hủy một đơn mua (vì một lí do nào đó)
        Chọn số thứ tự
        Xóa dữ liệu của đơn mua ĐÃ THÊM từ trước
    Sửa đơn mua
        Sửa lại địa chỉ nhận hàng


Khi mình truy cứu một đơn mua thì in ra danh sách gồm có:
    Tên
    Số lượng sản phẩm
    Giá đơn, giá tổng
    Id, địa chỉ, Sđt
    Hình thức thanh toán
    Trạng thái thanh toán
*/

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

int main() {
    menu();

    return 0;
}

/*
Đơn mua là sau khi thêm vào giỏ hàng và nhấn mua
*/