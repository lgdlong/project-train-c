// #include "include/libaries_and_define.h"
// Divided into modules
#include "../include/libaries_and_define.h"
#include "../include/products.h"
#include "../include/file.h"
#include "../include/carts.h"
#include "../include/orders.h"
#include "../include/menu.h"

struct product {
    char productName[MAX_NAME_LENGTH];
    int quantity;
    double price;
    int code; // Mã sản phẩm
};
struct customer_inf{ // Thông tin cá nhân của người mua
    int customer_id;
    char customer_name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char payment_method[MAX_PAYMENT_METHOD_LENGTH];
    
};
struct cart {
    struct product products[MAX_PRODUCTS];
    struct customer_inf *customer;
    int num_products;
    float total_price;
    int payment_status; // Trạng thái thanh toán (0: Chưa thanh toán, 1: Đã thanh toán)
};
struct order {
    struct product products[MAX_PRODUCTS];
    struct customer_inf *customer;
    int num_products;
    float total_price;
    int payment_status; // Trạng thái thanh toán (0: Chưa thanh toán, 1: Đã thanh toán)
};
struct customer_cart {
    struct customer_inf *customer;
    struct cart cart;
};

struct customer_cart customer_carts[MAX_CUSTOMERS];

int num_customer_carts = 0;
int order_count = 0;
int product_count = 0;


int main() {
	struct product products[MAX_PRODUCTS];
    struct cart cart[MAX_PRODUCTS];
    struct order orders[MAX_PRODUCTS];

    readProductsFromFile(products, &product_count);

    work_with_produts(products, cart, orders, product_count);

    return 0;
}