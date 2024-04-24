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
#include <stdlib.h> 

#include "menu.c"
#define MAX_PRODUCTS 50

struct product {
    char productName[MAX_PRODUCTS];
    int quantity;
    double price;
    int code; // mới thêm kiểu code, như id vậy
};
struct cart {
    struct product products[MAX_PRODUCTS];
    int num_products;
    float total_price;
    char customer_id;
    int payment_status;
};
struct order {
    struct product products[MAX_PRODUCTS];
    int num_products;
    float total_price;
    char customer_name[50];
    char address[50];
    char phone[50];
    char payment_method[50];
    bool payment_status;
};


void readProductsFromFile(struct product *products, int *product_count) { // Hàm đọc sản phẩm của Trân
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    while (fscanf(file, "%49[^,], %d, %lf, %d\n", products[*product_count].productName, &products[*product_count].quantity, &products[*product_count].price, &products[*product_count].code) == 4) {
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

void displayProducts(struct product *products, int product_count) {
    printf("\nSan pham:\n");
    int i;
    for (i = 0; i < product_count; i++) {
    	int j=i+1;
        printf("So: %d | ", j);
        printf("Ten san pham: %s | ", products[i].productName);
        printf("So luong: %d | ", products[i].quantity);
        printf("Gia: %.3lf | ", products[i].price);
        printf("\n");
    }
}

void display_cart_contents(struct cart *cart) { //Update lại hàm của Long
    printf("Danh sach san pham trong gio hang:\n");
    for (int i = 0; i < sizeof(cart); i++) {
        printf("Ten san pham: %s, So luong: %d, Ma san pham: %d\n", cart->products[i].productName, cart->products[i].quantity, cart->products[i].code);
    }
}

void create_cart(struct cart *cart) { //Phần này thêm trạng thái thanh toán (Chưa thanh toán == 0)
    cart->num_products = 0;
    cart->total_price = 0;
    cart->payment_status = 0; // chưa thanh toán
    printf("Gio hang da duoc tao!\n");
}

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
        if (products[i].code == code_of_product) { // wtf
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
            printf("San pham da duoc them vao gio hang!\n"); count_to_display_cart_content++;
            updateProductsFile(products, product_count);
            return;
        }
    }
    printf("Khong tim thay san pham trong danh sach!\n");
}

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

void ExportOrderIntoFile(struct cart *cart) { //In giỏ hàng vào file text (Xuất thành đơn mua)
    if (cart->payment_status == 1) {
        FILE *file = fopen("order.txt", "w");
        if (file == NULL) {
            printf("Khong the mo file.\n");
            return;
        }
        for (int i = 0; i < cart->num_products; i++) {
            fprintf(file, "%s, %d, %.2lf\n", cart->products[i].productName, cart->products[i].quantity, cart->products[i].price);
        }
        fclose(file);
    }
}

void customer_inf(struct order *orders) { /* Intput customer_name, address, payment_method */
    printf("\n======== Vui long dien thong tin khach hang ========\n");

    // Nhập tên người mua
    printf("Ten: ");
    fgets(orders->customer_name, sizeof(orders->customer_name), stdin);
    orders->customer_name[strcspn(orders->customer_name, "\n")] = '\0';

    // Nhập địa chỉ
    printf("Dia chi: ");
    fgets(orders->address, sizeof(orders->address), stdin);
    orders->address[strcspn(orders->address, "\n")] = '\0';

    // Nhập số điện thoại
    printf("So dien thoai: ");
    scanf("%s", &orders->phone);

    printf("\nHinh thuc thanh toan: \n");
    printf("\t1. Chuyen phat thanh thu ho (COD)\n");
    printf("\t2. Vi dien tu\n");
    printf("\t3. The tin dung/the ghi no\n");

    printf("\tMoi chon so thu tu hinh thuc thanh toan: ");

    // Chọn phương thức thanh toán
    int payment_method_choice;
    scanf("%d", &payment_method_choice); getchar();
    switch (payment_method_choice) {
    case 1:
        strcpy(orders->payment_method, "COD");
        printf("\nDa chon: Chuyen phat thanh thu ho (COD)!\n");
        break;
    case 2:
        strcpy(orders->payment_method, "Vi dien tu");
        printf("\nDa chon: Vi dien tu!\n");
        break;
    case 3:
        strcpy(orders->payment_method, "The tin dung/ghi no");
        printf("\nDa chon: The tin dung/the ghi no!\n");
        break;
    default:
        printf("Lua chon khong hop le!\n");
        break;
    }

    // Cập nhật trạng thái thanh toán
    if (orders->payment_status == true) printf("Da thanh toan\n");
    else printf("Chua thanh toan\n");

}

void addProduct(struct product *products, int *product_count) {
    printf("\nNhap ten san pham: ");
    getchar(); 
    fgets(products[*product_count].productName, sizeof(products[*product_count].productName), stdin);
    products[*product_count].productName[strcspn(products[*product_count].productName, "\n")] = '\0';

    printf("Nhap so luong: ");
    scanf("%d", &products[*product_count].quantity);

    printf("Nhap gia san pham: ");
    scanf("%lf", &products[*product_count].price);

    (*product_count)++;
}


void display_cart(struct cart *cart) {
    /*
    Cái này của Long thêm vào
    */
    for (int i = 0; i < sizeof(cart); i++) {
        printf("%s\n", cart[i].products->productName);
    }
}

void fixProducts(struct product *products, int product_count){
	int i;
	displayProducts(products, product_count);
	printf("Nhap so cua san pham muon thay doi: ");
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

void work_with_order(struct product *products, struct cart *cart, struct order *orders, int product_count) {
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

    cart->payment_status = 1; // 2 thằng nawny Linh mới thêm
    ExportOrderIntoFile(cart);

    customer_inf(orders); // Nhập thông tin người mua

    int num, choice1;
    printf("\n=============== MENU ===============\n");
    printf("1. Them don mua\n");
    printf("2. Xoa don mua\n");
    printf("3. Sua don mua\n");
    printf("4.Quay ve menu truoc do\n");
    printf("\n");

    lua_chon(&choice1);

    do {
        switch (choice1) {
            case 1:
                display_cart(cart); // In giỏ hàng

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
}

void work_with_cart(struct product *products, struct cart *cart, struct order *orders, int product_count) { // Hàm làm việc với giỏ hàng
    int choice;
    do {
        printf("\n============= MENU ==============");
        printf("\n1. Tao moi gio hang");
        printf("\n2. Them san pham vao gio hang");
        printf("\n3. Xoa san pham khoi gio hang");
        printf("\n4. Chinh sua gio hang");
        printf("\n5. Hoan tat gio hang va bat dau thanh toan");
        printf("\n0. Quay ve menu truoc do\n");
        printf("\nNhap lua chon: ");
        scanf("%d", &choice); getchar();
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
                work_with_order(products, cart, orders, product_count);
                break;
            case 0:
                printf("Cam on ban da su dung dich vu!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}

// check lại hàm này
void work_with_produts(struct product *products, struct cart *cart, struct order *orders, int *product_count) {
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
                addProduct(products, &*product_count);
                break;
            case 2:
                displayProducts(products, *product_count);
                break;
            case 3:
                fixProducts(products, *product_count);
                break;
            case 4:
                work_with_cart(products, cart, orders, *product_count);
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

    work_with_produts(products, cart, orders, &product_count);

    return 0;
}
