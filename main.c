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
    int choice, choice1, choice2;

    while(1) {
        ds_1();
        lua_chon(&choice);

        if (choice == 1) { // Làm việc với sản phẩm
            work_with_san_pham();
            lua_chon(&choice1);

            if (choice1 == 1) { // Thêm sản phẩm
                printf("Nhap so luong san pham can them: ");
                int productQuantity;
                scanf("%d", &productQuantity);

                for (int i = 0; i < productQuantity; i++) {
                    printf("SAN PHAM %d\n", i+1);
                    
                    printf("Nhap ten san pham\n");
                    printf("Nhap so luong san pham: \n");
                    printf("Nhap gia san pham: \n");
                    printf("\n");
                    /*
                    Gán số thứ tự cho sản phẩm ngay tại thời điểm nhập vào một sản phẩm có kiểu product
                    */
                }
            }

            else if (choice1 == 2) {
                printf("Lua chon so thu tu cua san pham can xoa: \n");
                printf("\n");
                /*
                Mỗi sản phẩm sẽ được gán một số thứ tự theo thời điểm nhập vào từ 1 -> productQuantity
                Khi xóa sản phẩm sẽ lựa chọn số thứ tự để xóa theo số thứ tự
                */
            }

            else { // choice1 == 3 -> Sua san pham
                printf("Lua chon so thu tu cua san pham can sua: \n");
                printf("Sua ten san pham: \n");
                printf("Sua so luong san pham: \n");
                printf("Sua gia san pham: \n");
                printf("\n");
            }
            
        }

        else if (choice == 2) {
            work_with_don_mua();
        }

        else if (choice == 3){
            work_with_gio_hang();
        }
        else { // choice == 4
            return;
        }
    }
}

void add_product(struct product prod) {

}

int main() {
    menu();

    return 0;
}
