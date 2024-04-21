#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>


struct product {
    char productName[50];
    int quantity;
    double price;
};

struct Order {
    struct product products;
    int num_products;
    float total_price;
    char buyer_name;
    char address;
    char phone;
    char payment_method;
    char payment_status;
};

struct Cart {
    struct product products;
    int num_products;
    float total_price;
    char customer_id;
};

void work_with_cart() { // Tạo menu làm việc với giỏ hàng
    int choice;
    do {
    printf("Vui lòng chọn!");
    printf("1. Tạo giỏ hàng");
    printf("2. Thêm giỏ hàng");
    printf("3. Xóa giỏ hàng");
    printf("4. Sửa giỏ hàng");
    printf("5. Hoàn tất mua sắm và thanh toán");
    scanf("%d",&choice);
    switch (choice) {
            case 1:
                create_cart(&cart);
                break;
            case 2:
                add_to_cart(&cart);
                break;
            case 3:
                delete_from_cart(&cart);
                break;
            case 4:
                modify_cart(&cart);
                break;
            case 5:
                checkout(&cart);
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    } while (choice != 0);
}


void create_cart(struct Cart *cart) { // Hàm tạo giỏ hàng
    cart->num_products = 0; // Init 2 phần tử ban đầu bằng 0
    cart->total_price = 0;
    printf("Giỏ hàng đã được tạo!");
}

void add_to_cart(struct pro, struct Cart *cart) { // Hàm thêm sản phẩm vào giỏ hàng
    int amount;
    if (cart -> num_products == 0) {
        printf("Chưa có sản phẩm nào! ");
    }
    while (true) {
        products_list();
        printf("Nhập tên sản phẩm muốn thêm: ");
        scanf("%d", )
        printf("Nhập số lượng: ");
        scanf("%d", &amount);
        
        printf("Nhập mã sản phẩm: ");

    }
}

void delete_from_cart(struct Cart *cart) { // Hàm xóa sản phẩm từ giỏ hàng
    int msp;
    while (cart -> num_products > 0) {
        products_list();
        printf("Nhập mã sản phẩm muốn xóa: ");

    }

}

void modify_cart(struct *cart) { // Hàm chỉnh sửa giỏ hàng (Hàm này bao gồm hai hàm xóa và thêm sản phẩm vào giỏ hàng)
    int choice;
    do {
        printf("1. Thêm sản phẩm");
        printf("2. Xóa sản phẩm");
        printf("3. Hoàn tất chỉnh sửa");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                add_to_cart();
                break;
            case 2:
                delete_from_cart();
                break;
            case 3:
                exit(0);
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    } while (1);
}

int main() {

    return 0;
}
