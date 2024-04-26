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
void work_with_order(struct product *products, struct cart *cart, struct order *orders, int *product_count) {
/*
Đơn mua: thông tin cá nhân, xuất đơn mua
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
    int num;
    int choice1;
    

    do {
        printf("\n=============== MENU ===============\n");
        printf("1. Tao don mua\n");
        printf("2. Huy don mua\n");
        printf("3. Sua don mua\n");
        printf("4. Hien thi don mua\n");
        printf("5. Thanh toan\n");
        printf("6. Quay ve menu truoc do\n");
        printf("\n");

        printf("Moi nhap lua chon: ");
        scanf("%d", &choice1);
        printf("\n");

        switch (choice1) {
            case 1:
                createOrder(cart, orders);
                break;
            case 2:
                cancelOrder(orders, &order_count);
                break;
            case 3:
                modifyOrder(orders, order_count);
                break;
            case 4:
                displayOrder(orders);
                break;
            case 5:
                checkout(cart);
                break;
            case 6:
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    while (choice1 != 6);
}

void work_with_cart(struct product *products, struct cart *cart, struct order *orders, int product_count) { // Hàm làm việc với giỏ hàng
    // Khai báo một biến customer_inf để truyền vào hàm create_cart
    struct customer_inf customer;

    int choice;
    do {
        printf("\n============= MENU ==============");
        printf("\n1. Tao moi gio hang");
        printf("\n2. Thao tac voi gio hang");
        printf("\n3. Xem gio hang hien tai");
        printf("\n4. Hoan tat gio hang va bat dau thanh toan");
        printf("\n0. Quay ve menu truoc do\n");
        printf("\nNhap lua chon: ");
        scanf("%d", &choice); getchar();
        switch (choice) {
            case 1:
                fill_customer_inf(&customer);
                create_cart(cart, &customer, products, product_count);
                break;
            case 2:
                int choice1;
                do {
                    printf("\n=========== MENU ============");
                    printf("\n1. Them san pham vao gio hang");
                    printf("\n2. Xoa san pham khoi gio hang");
                    printf("\n3. Chinh sua gio hang");
                    printf("\n0. Quay ve menu truoc do\n");
                    printf("\nNhap lua chon: ");
                    scanf("%d", &choice1); getchar();
                    switch (choice1) {
                        case 1:
                            add_to_cart(products, cart, product_count);
                            break;
                        case 2:
                            delete_from_cart(products, cart, product_count);
                            break;
                        case 3:
                            modify_cart(products, cart, product_count);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Lua chon khong hop le!\n");
                    }
                } while (choice1 != 0);
                break;
            case 3:
                displayAllCarts(); // Hiển thị thông tin giỏ hàng
                break;
            case 4:

                work_with_order(products, cart, orders, &product_count);
                break;
            case 0:
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}

void work_with_produts(struct product *products, struct cart *cart, struct order *orders, int product_count) {
    int choice;
    do {
        printf("\n============ MENU ============");
        printf("\n1. Them san pham");
        printf("\n2. Hien thi danh sach san pham");
        printf("\n3. Chinh sua thong tin san pham");
        printf("\n4. Lam viec voi gio hang");
        printf("\n0. Thoat chuong trinh\n");
        printf("\nNhap lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addProduct(products, &product_count);
                break;
            case 2:
                displayProducts(products, product_count);
                break;
            case 3:
                fixProducts(products, product_count);
                break;
            case 4:
                work_with_cart(products, cart, orders, product_count);
                break;
            case 0:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    } while(choice != 0);
}
