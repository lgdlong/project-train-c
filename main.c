#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 

#define MAX_PRODUCTS 50

struct Product {
    char productName[50];
    int quantity;
    double price;
};

struct Cart {
    struct Product products[MAX_PRODUCTS];
    int num_products;
    float total_price;
    char customer_id;
};

void create_cart(struct Cart *cart) { // Hàm tạo giỏ hàng
    cart->num_products = 0;
    cart->total_price = 0;
    printf("Giỏ hàng đã được tạo!\n");
}

void add_to_cart(struct Product *products, struct Cart *cart, int product_count) { // Hàm thêm sản phẩm vào giỏ hàng
    displayProducts();
    char name_of_product[50];
    int quantity;
    printf("Nhập tên sản phẩm muốn thêm: ");
    scanf("%s", name_of_product);

    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].productName, name_of_product) == 0) {
            printf("Nhập số lượng: ");
            scanf("%d", &quantity);
            if (quantity > products[i].quantity) {
                printf("Số lượng không đủ trong kho!\n");
                return;
            }
            cart->products[cart->num_products] = products[i];
            cart->products[cart->num_products].quantity = quantity;
            cart->total_price += products[i].price * quantity;
            cart->num_products++;
            products[i].quantity -= quantity;
            printf("Sản phẩm đã được thêm vào giỏ hàng!\n");
            return;
        }
    }
    printf("Không tìm thấy sản phẩm trong danh sách!\n");
}

void delete_from_cart(struct Product *products, struct Cart *cart, int product_count) { // Hàm xóa sản phẩm từ giỏ hàng
    if (cart->num_products == 0) {
        printf("Giỏ hàng trống!\n");
        return;
    }

    displayProducts();
    char name_of_product[50];
    int quantity;
    printf("Nhập tên sản phẩm muốn xóa: ");
    scanf("%s", name_of_product);

    for (int i = 0; i < cart->num_products; i++) {
        if (strcmp(cart->products[i].productName, name_of_product) == 0) {
            printf("Nhập số lượng: ");
            scanf("%d", &quantity);
            if (quantity > cart->products[i].quantity) {
                printf("Số lượng nhập vào lớn hơn số lượng trong giỏ hàng!\n");
                return;
            }
            cart->total_price -= cart->products[i].price * quantity;
            products[i].quantity += quantity;

            for (int j = i; j < cart->num_products - 1; j++) {
                cart->products[j] = cart->products[j + 1];
            }
            cart->num_products--;
            printf("Sản phẩm đã được xóa khỏi giỏ hàng!\n");
            return;
        }
    }
    printf("Không tìm thấy sản phẩm trong giỏ hàng!\n");
}

void modify_cart(struct Product *products, struct Cart *cart, int product_count) { // Hàm chỉnh sửa giỏ hàng
    int choice;
    do {
        printf("\n1. Thêm sản phẩm\n");
        printf("2. Xóa sản phẩm\n");
        printf("3. Hoàn tất chỉnh sửa\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_to_cart(products, cart, product_count);
                break;
            case 2:
                delete_from_cart(products, cart, product_count);
                break;
            case 3:
                return;
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    } while (true);
}

void checkout(struct Cart *cart) { // Hàm thanh toán
    printf("\n======== Vui lòng điền thông tin khách hàng ========");
    printf("\nTên: ");
    printf("\nĐịa chỉ: ");
    printf("\nHình thức thanh toán: ");
}



void display_cart(struct Cart *cart) {
    /*
    Cái này của Long thêm vào
    */
    for (int i = 0; i < sizeof(cart); i++) {
        printf("%s\n", cart[i].products->productName);
    }
}


void work_with_cart(struct Product *products, struct Cart *cart, int product_count) { // Hàm làm việc với giỏ hàng
    int choice;
    do {
        printf("\n======== MENU ========");
        printf("\n1. Tạo giỏ hàng");
        printf("\n2. Thêm sản phẩm vào giỏ hàng");
        printf("\n3. Xóa sản phẩm khỏi giỏ hàng");
        printf("\n4. Chỉnh sửa giỏ hàng");
        printf("\n5. Hoàn tất mua sắm và thanh toán");
        printf("\n0. Thoát");
        printf("\nNhập lựa chọn: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                create_cart(cart);
                break;
            case 2:
                add_to_cart(products, cart, product_count);
                break;
            case 3:
                delete_from_cart(products, cart, product_count);
                break;
            case 4:
                modify_cart(products, cart, product_count);
                break;
            case 5:
                checkout(cart);
                break;
            case 0:
                printf("Cảm ơn bạn đã sử dụng dịch vụ!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    } while (choice != 0);
}
