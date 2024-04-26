#include "../../include/libaries_and_define.h"
#include "../../include/products.h"
#include "../../include/carts.h"
#include "../../include/orders.h"
#include "../../include/menu.h"

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
struct order {
    struct product products[MAX_PRODUCTS];
    struct customer_inf *customer;
    int num_products;
    float total_price;
    int payment_status; // Trạng thái thanh toán (0: Chưa thanh toán, 1: Đã thanh toán)
};
struct customer_inf{ // Thông tin cá nhân của người mua
    int customer_id;
    char customer_name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char payment_method[MAX_PAYMENT_METHOD_LENGTH];
};

// MAIN WORKING MENU


