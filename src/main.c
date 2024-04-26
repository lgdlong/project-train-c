// #include "include/libaries_and_define.h"
// Divided into modules
#include "../include/libaries_and_define.h"
#include "../include/products.h"
#include "../include/file.h"
#include "../include/carts.h"
#include "../include/orders.h"

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





bool isPaymentComplete(struct cart cart) {
    return cart.payment_status == 1;
}

bool isValidQuantity(int quantity) {
    return quantity > 0;
}

bool isValidIndex(int index, int array_size) {
    return index >= 0 && index < array_size;
}

int getIntegerInput() {
    int input;
    while (scanf("%d", &input) != 1) {
        printf("Nhap khong hop le! Moi nhap lai: ");
        scanf("%*s");
    }
    return input;
}

bool isProductInCart(int code_of_product, struct cart cart) {
    for (int i = 0; i < cart.num_products; i++) {
        if (cart.products[i].code == code_of_product) {
            return true;
        }
    }
    return false;
}

bool isValidCartInput(int code_of_product, int quantity, struct product *products, int product_count) {
    if (!isValidIndex(code_of_product - 1, product_count)) {
        printf("Ma san pham khong hop le!\n");
        return false;
    }
    if (!isValidQuantity(quantity)) {
        printf("So luong khong hop le!\n");
        return false;
    }
    if (quantity > products[code_of_product - 1].quantity) {
        printf("So luong khong du trong kho!\n");
        return false;
    }
    return true;
}

// WORK WITH PRODUCTS
/*
void displayProducts(struct product *products, int product_count);

void addProduct(struct product *products, int *product_count);

void fixProducts(struct product *products, int product_count);
*/

// WORK WITH CUSTOMERS
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


// WORK WITH FILE
/*
void readProductsFromFile(struct product *products, int *product_count);

void writeProductsToFile(struct product *products, int product_count);

void deleteFileContents(const char *filename);

void updateProductsFile(struct product *products, int product_count);

void ExportOrderIntoFile(struct cart *cart);
*/

// WORK WITH CART
/*
void display_cart_contents(struct cart *cart);

void displayAllCarts();

void create_cart(struct cart *cart, struct customer_inf *customer, struct product *products, int product_count);

void add_to_cart(struct product *products, struct cart *cart, int product_count);

void delete_from_cart(struct product *products, struct cart *cart, int product_count);

void modify_cart(struct product *products, struct cart *cart, int product_count);
*/

// WORK WITH ORDERS
/*
void checkout(struct cart *cart);

void createOrder(struct cart *cart, struct order *order);

void cancelOrder(struct order *orders, int *order_count);

void modifyOrder(struct order *orders, int order_count);

void displayOrder(struct order *orders);
*/

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

    // BẮT ĐẦU CODE

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


int main() {
	struct product products[MAX_PRODUCTS];
    struct cart cart[MAX_PRODUCTS];
    struct order orders[MAX_PRODUCTS];
    int product_count = 0;

    readProductsFromFile(products, &product_count);

    work_with_produts(products, cart, orders, product_count);

    return 0;
}