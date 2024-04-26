#include "../../include/libaries_and_define.h"
#include "../../include/products.h"
#include "../../include/carts.h"
#include "../../include/orders.h"

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

extern struct customer_cart customer_carts[MAX_CUSTOMERS];



// WORK WITH ORDERS
void fill_customer_inf(struct customer_inf *customer) { // Intput customer_name, address, payment_method
    printf("\n======== Vui long dien thong tin khach hang ========\n");

    // Nhập tên người mua
    printf("Ten: ");
    fgets(customer->customer_name, sizeof(customer->customer_name), stdin);
    customer->customer_name[strcspn(customer->customer_name, "\n")] = '\0';

    // Nhập địa chỉ
    printf("Dia chi: ");
    fgets(customer->address, sizeof(customer->address), stdin);
    customer->address[strcspn(customer->address, "\n")] = '\0';

    // Nhập số điện thoại
    printf("So dien thoai: ");
    scanf("%s", &customer->phone); getchar();

    // Chọn phương thức thanh toán
    printf("\nHinh thuc thanh toan: \n");
    printf("\t1. Chuyen phat thanh thu ho (COD)\n");
    printf("\t2. Vi dien tu\n");
    printf("\t3. The tin dung/the ghi no\n");

    printf("\tMoi chon so thu tu hinh thuc thanh toan: ");

    int payment_method_choice;
    scanf("%d", &payment_method_choice); getchar();
    switch (payment_method_choice) {
    case 1:
        strcpy(customer->payment_method, "COD");
        printf("\nDa chon: Chuyen phat thanh thu ho (COD)!\n");
        break;
    case 2:
        strcpy(customer->payment_method, "Vi dien tu");
        printf("\nDa chon: Vi dien tu!\n");
        break;
    case 3:
        strcpy(customer->payment_method, "The tin dung/ghi no");
        printf("\nDa chon: The tin dung/the ghi no!\n");
        break;
    default:
        printf("Lua chon khong hop le!\n");
        break;
    }
}


void checkout(struct cart *cart) { // Thanh toán
    printf("\nTong gia tri gio hang: %.3lf\n", cart->total_price);

    if (cart->total_price == 0) {
        printf("Gio hang cua ban dang trong, vui long them san pham truoc khi thanh toan.\n");
        return;
    }

    struct customer_inf *customer = cart->customer;
    fill_customer_inf(customer);
    cart->payment_status = 1; // Đánh dấu đã thanh toán
    printf("\nCam on ban da mua hang! Thong tin don hang:\n");
    display_cart_contents(cart);
}

void createOrder(struct cart *cart, struct order *order) { // Tạo đơn mua

    order_count++;

    // Sao chép thông tin cá nhân của khách hàng từ giỏ hàng sang đơn mua
    strcpy(order[order_count].customer->customer_name, cart->customer->customer_name);
    strcpy(order[order_count].customer->address, cart->customer->address);
    strcpy(order[order_count].customer->phone, cart->customer->phone);
    strcpy(order[order_count].customer->payment_method, cart->customer->payment_method);
    order[order_count].payment_status = cart->payment_status;


    // Sao chép tổng giá và số lượng sản phẩm
    order[order_count].total_price = cart->total_price;
    order[order_count].num_products = cart->num_products;

    // Sao chép thông tin giỏ hàng
    for (int i = 0; i < cart->num_products; i++) {
        order[order_count].products[i].code = cart->products[i].code;
        strcpy(order[order_count].products[i].productName, cart->products[i].productName);
        order[order_count].products[i].quantity = cart->products[i].quantity;
        order[order_count].products[i].price = cart->products[i].price;
    }

    printf("\nDon hang da duoc tao!\n");
    printf("Thong tin don hang:\n");
    display_cart_contents(cart);
}

void cancelOrder(struct order *orders, int *order_count) { // hủy đơn mua
    if (*order_count == 0) {
        printf("Khong co don hang de huy!\n");
        return;
    }

    printf("Danh sach cac don hang:\n");
    for (int i = 0; i < *order_count; i++) {
        printf("%d. Don hang %d\n", i + 1, i + 1);
    }

    printf("Chon so thu tu cua don hang muon huy: ");
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > *order_count) {
        printf("Lua chon khong hop le!\n");
        return;
    }

    for (int i = choice - 1; i < *order_count - 1; i++) {
        orders[i] = orders[i + 1];
    }
    (*order_count)--;
    printf("Don hang da duoc huy!\n");
}

void modifyOrder(struct order *orders, int order_count) { // sửa đổi thông tin trong đơn mua
    if (order_count == 0) {
        printf("Khong co don hang de sua!\n");
        return;
    }

    printf("Danh sach cac don hang:\n");
    for (int i = 0; i < order_count; i++) {
        printf("%d. Don hang %d\n", i + 1, i + 1);
    }

    printf("Chon so thu tu cua don hang muon sua: ");
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > order_count) {
        printf("Lua chon khong hop le!\n");
        return;
    }

    printf("Sua thong tin cho don hang %d:\n", choice);
    // Thêm phần sửa thông tin địa chỉ nhận hàng ở đây
    printf("Sua thong tin thanh cong!\n");
}

void displayOrder(struct order *orders) {
    printf("\nDanh sach don hang:\n");
    for (int i = 0; i < order_count; i++) {
        printf("Don hang %d\n", i+1);
        printf("Ten khach hang: %s\n", orders[i].customer->customer_name);
        printf("Dia chi: %s\n", orders[i].customer->address);
        printf("So dien thoai: %s\n", orders[i].customer->phone);
        printf("Phuong thuc thanh toan: %s\n", orders[i].customer->payment_method);
        printf("Tong gia tri don hang: %.3lf\n", orders[i].total_price);
        printf("Danh sach san pham:\n");
        for (int j = 0; j < orders[i].num_products; j++) {
            printf("\tMa san pham: %d | Ten san pham: %s | So luong: %d | Gia: %.3lf\n", orders[i].products[j].code, orders[i].products[j].productName, orders[i].products[j].quantity, orders[i].products[j].price);
        }
        printf("\n");
    }
}

