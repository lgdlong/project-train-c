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
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_PRODUCTS 50
#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_PAYMENT_METHOD_LENGTH 20
#define MAX_CUSTOMERS 50

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


// WORK WITH PRODUCTS
void displayProducts(struct product *products, int product_count) {
    printf("\nDanh sach san pham:\n");
    for (int i = 0; i < product_count; i++) {
        printf("Ma san pham: %d | Ten san pham: %s | So luong: %d | Gia: %.3lf\n", products[i].code, products[i].productName, products[i].quantity, products[i].price);
    }
}

void addProduct(struct product *products, int *product_count) {
    static int last_product_code = 0;
    
    printf("\nNhap ten san pham: ");
    getchar(); 
    fgets(products[*product_count].productName, sizeof(products[*product_count].productName), stdin);
    products[*product_count].productName[strcspn(products[*product_count].productName, "\n")] = '\0';

    printf("Nhap so luong: ");
    scanf("%d", &products[*product_count].quantity);

    printf("Nhap gia san pham: ");
    scanf("%lf", &products[*product_count].price);

    last_product_code++; // Tăng giá trị của mã sản phẩm cuối cùng
    products[*product_count].code = last_product_code;

    (*product_count)++;
}

void fixProducts(struct product *products, int product_count){
	int i;
	displayProducts(products, product_count);
	printf("Nhap ma san pham muon thay doi: ");
	scanf("%d", &i);
	
	int j=i-1;
	
	if(j>=0 && j< product_count) {
	printf("Nhap ten moi cho san pham: ");
	getchar();
        fgets(products[j].productName, sizeof(products[j].productName), stdin);
        products[j].productName[strcspn(products[j].productName, "\n")] = '\0';

        printf("Nhap so luong moi: ");
        scanf("%d", &products[j].quantity);

        printf("Nhap gia moi: ");
        scanf("%lf", &products[j].price);

        printf("Thong tin san pham da cap nhat thanh cong!\n");
    }
    else {
        printf("So nay khong phu hop!\n");
    }
}


// WORK WITH FILE
void readProductsFromFile(struct product *products, int *product_count) { // Hàm đọc sản phẩm của Trân
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    while (fscanf(file, "%99[^,], %d, %lf, %d\n", products[*product_count].productName, &products[*product_count].quantity, &products[*product_count].price, &products[*product_count].code) == 4) {
        (*product_count)++;
    }

    fclose(file);
}

void writeProductsToFile(struct product *products, int product_count) { //Hàm viết sản phẩm của Trân
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    for (int i = 0; i < product_count; i++) {
        fprintf(file, "%s, %d, %.2lf, %d\n", products[i].productName, products[i].quantity, products[i].price, products[i].code);
    }

    fclose(file);
}

void deleteFileContents(const char *filename) { //Hàm xóa tất cả dữ liệu trong file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    fclose(file);
}

void updateProductsFile(struct product *products, int product_count) { //Hàm cập nhật lại số lượng sản phẩm sau khi thêm hoặc bớt sản phẩm
    deleteFileContents("products.txt");
    writeProductsToFile(products, product_count);
}

void ExportOrderIntoFile(struct cart *cart) {
    if (isPaymentComplete(*cart)) {
        FILE *file = fopen("order.txt", "w");
        if (file == NULL) {
            printf("Khong the mo file.\n");
            return;
        }
        for (int i = 0; i < cart->num_products; i++) {
            fprintf(file, "%s, %d, %.2lf\n", cart->products[i].productName, cart->products[i].quantity, cart->products[i].price);
        }
        fclose(file);
    } else {
        printf("Khong the xuat don hang vi chua thanh toan!\n");
    }
}

// WORK WITH CART
void display_cart_contents(struct cart *cart) {
    printf("\nDanh sach san pham trong gio hang:\n");
    for (int i = 0; i < cart->num_products; i++) {
        printf("Ma san pham: %d | Ten san pham: %s | So luong: %d\n",  cart->products[i].code, cart->products[i].productName, cart->products[i].quantity);
    }
}

void displayAllCarts() {
    printf("========== DANH SACH GIO HANG ==========\n\n");
    for (int i = 0; i < num_customer_carts; i++) {
        printf("Thong tin khach hang:\n");
        printf("Ten: %s\n", customer_carts[i].customer->customer_name);
        printf("Dia chi: %s\n", customer_carts[i].customer->address);
        printf("So dien thoai: %s\n\n", customer_carts[i].customer->phone);

        printf("Danh sach san pham trong gio hang:\n");
        for (int j = 0; j < customer_carts[i].cart.num_products; j++) {
            printf("Ma san pham: %d | Ten san pham: %s | So luong: %d\n", 
                   customer_carts[i].cart.products[j].code,
                   customer_carts[i].cart.products[j].productName,
                   customer_carts[i].cart.products[j].quantity);
        }
        printf("\n=======================================\n");
    }
}

void create_cart(struct cart *cart, struct customer_inf *customer, struct product *products, int product_count) {
    // Kiểm tra xem khách hàng đã có giỏ hàng trước đó hay chưa
    for (int i = 0; i < num_customer_carts; i++) {
        if (strcmp(customer_carts[i].customer->phone, customer->phone) == 0) {
            // Nếu có, lưu giỏ hàng đó vào mảng customer_carts
            printf("Tim thay gio hang cu cua khach hang!\n");
            customer_carts[i].cart = *cart;
            // Cập nhật thông tin khách hàng nếu cần thiết
            customer_carts[i].customer = customer;
            return;
        }
    }

    // Nếu không có giỏ hàng trước đó, tạo giỏ hàng mới
    if (num_customer_carts < MAX_CUSTOMERS) {
        // Sao chép thông tin khách hàng vào giỏ hàng mới
        cart->customer = (struct customer_inf *)malloc(sizeof(struct customer_inf)); // Cấp phát động
        if (cart->customer != NULL) {
            *cart->customer = *customer;
        }
        else {
            printf("Khong the cap phat bo nho cho khach hang!\n");
            return;
        }

        // Sao chép thông tin sản phẩm từ giỏ hàng vào giỏ hàng mới
        for (int i = 0; i < cart->num_products; i++) {
            cart->products[i] = products[i];
        }
        
        // Thêm giỏ hàng mới vào mảng customer_carts
        customer_carts[num_customer_carts].customer = cart->customer;
        customer_carts[num_customer_carts].cart = *cart;
        printf("\nGio hang da duoc tao cho khach hang %s!\n", customer->customer_name);

        num_customer_carts++;
    }
    else {
        printf("Da dat toi gioi han luu tru khach hang!\n");
        return;
    }
}

void add_to_cart(struct product *products, struct cart *cart, int product_count) {
    displayProducts(products, product_count);

    int code_of_product;
    int quantity;

    printf("Nhap ma san pham muon them: ");
    if (scanf("%d", &code_of_product) != 1) {
        printf("Nhap khong hop le!\n");
        return;
    }

    // Kiểm tra xem sản phẩm có tồn tại trong kho không
    int product_index = -1;
    for (int i = 0; i < product_count; i++) {
        if (products[i].code == code_of_product) {
            product_index = i;
            break;
        }
    }

    if (product_index == -1) {
        printf("San pham khong ton tai trong kho!\n");
        return;
    }

    printf("Nhap so luong: ");
    if (scanf("%d", &quantity) != 1) {
        printf("Nhap khong hop le!\n");
        return;
    }

    if (quantity > products[product_index].quantity) {
        printf("So luong khong du trong kho!\n");
        return;
    }

    // Thêm sản phẩm vào giỏ hàng
    cart->products[cart->num_products] = products[product_index];
    cart->products[cart->num_products].quantity = quantity;
    cart->total_price += products[product_index].price * quantity;
    
    cart->num_products++;

    // Cập nhật số lượng sản phẩm còn lại trong kho
    products[product_index].quantity -= quantity;

    printf("San pham da duoc them vao gio hang!\n");

    // Thêm sản phẩm vào giỏ hàng của khách hàng
    customer_carts[num_customer_carts].cart.products[cart->num_products - 1] = cart->products[cart->num_products - 1];

    // Hiển thị giỏ hàng sau khi thêm sản phẩm
    display_cart_contents(cart);
}

/*
void add_to_cart(struct product *products, struct cart *cart, int product_count) { //Đã sửa đổi từ so sánh từ tên sản phẩm sang so sánh mã sản phẩm
    displayProducts(products, product_count);

    int count_to_display_cart_content = 0;
    if (count_to_display_cart_content != 0) display_cart_contents(cart);

    int code_of_product;
    int quantity;
    printf("Nhap ma san pham muon them: ");
    if (scanf("%d", &code_of_product) != 1) {
        printf("Nhap khong hop le!\n");
        return;
    }

    for (int i = 0; i < product_count; i++) {
        if (products[i].code == code_of_product) {
            printf("Nhap so luong: ");
            
            if (scanf("%d", &quantity) != 1) {
                printf("Nhap khong hop le!\n");
                return;
            }
            if (quantity > products[i].quantity) {
                printf("So luong khong du trong kho!\n");
                return;
            }
            
            cart->products[cart->num_products] = products[i];
            cart->products[cart->num_products].quantity = quantity;
            cart->total_price += products[i].price * quantity;
            cart->num_products++;
            products[i].quantity -= quantity;
            printf("San pham da duoc them vao gio hang!\n"); 

            count_to_display_cart_content++;
            updateProductsFile(products, product_count);



            // cap nhat san pham them vao gio hang cua khach hang
            // Cập nhật thông tin cho sản phẩm được thêm vào giỏ hàng của khách hàng
            customer_carts[num_customer_carts].cart.products[i].code = code_of_product;

            strcpy(customer_carts[num_customer_carts].cart.products[i].productName, cart->products[cart->num_products - 1].productName);

            customer_carts[num_customer_carts].cart.products[i].quantity = cart->products[cart->num_products - 1].quantity;


            display_cart_contents(cart);
            return;
        }
    }


    printf("Khong tim thay san pham trong danh sach!\n");
}
*/

void delete_from_cart(struct product *products, struct cart *cart, int product_count) { //Đã sửa đổi từ so sánh từ tên sản phẩm sang so sánh mã sản phẩm
    if (cart->num_products == 0) {
        printf("Gio hang trong!\n");
        return;
    }
    displayProducts(products, product_count);
    display_cart_contents(cart);
    int code_of_product;
    int quantity;
    printf("Nhap ma san pham muon xoa: ");
    if (scanf("%d", &code_of_product) != 1) {
        printf("Nhap khong hop le!\n");
        return;
    }

    for (int i = 0; i < cart->num_products; i++) {
        if (cart->products[i].code == code_of_product) {
            printf("Nhap so luong: ");
            if (scanf("%d", &quantity) != 1) {
                printf("Nhap khong hop le!\n");
                return;
            }
            if (quantity > cart->products[i].quantity) {
                printf("So luong nhap vao lon hon so luong trong gio hang!\n");
                return;
            }
            cart->total_price -= cart->products[i].price * quantity;
            products[i].quantity += quantity;

            for (int j = i; j < cart->num_products - 1; j++) {
                cart->products[j] = cart->products[j + 1];
            }
            cart->num_products--;
            printf("San pham da duoc xoa khoi gio hang!\n");
            updateProductsFile(products, product_count);
            return;
        }
    }
    printf("Khong tim thay san pham trong gio hang!\n");
}

void modify_cart(struct product *products, struct cart *cart, int product_count) { // Hàm chỉnh sửa giỏ hàng
    int choice;
    do {
        printf("\n1. Them san pham\n");
        printf("2. Xoa san pham\n");
        printf("3. Hoan tat chinh sua\n");
        printf("\nNhap lua chon: ");
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
                printf("Lua chon khong hop le!\n");
        }
    } while (true);
}


// WORK WITH ORDERS
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