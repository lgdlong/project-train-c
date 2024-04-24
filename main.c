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

void readProductsFromFile(struct Product *products, int *product_count) { // Hàm đọc sản phẩm của Trân
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

void writeProductsToFile(struct Product *products, int product_count) { //Hàm viết sản phẩm của Trân
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

void updateProductsFile(struct Product *products, int product_count) { //Hàm cập nhật lại số lượng sản phẩm sau khi thêm hoặc bớt sản phẩm
    deleteFileContents("products.txt");
    writeProductsToFile(products, product_count);
}

void display_cart_contents(struct Cart *cart) { //Update lại hàm của Long
    printf("Danh sach san pham trong gio hang:\n");
    for (int i = 0; i < sizeof(cart); i++) {
        printf("Ten san pham: %s, So luong: %d, Ma san pham: %d\n", cart->products[i].productName, cart->products[i].quantity, cart->products[i].code);
    }
}

void create_cart(struct Cart *cart) { //Phần này thêm trạng thái thanh toán (Chưa thanh toán == 0)
    cart->num_products = 0;
    cart->total_price = 0;
    cart->payment_status = 0;
    printf("Gio hang da duoc tao!\n");
}

void add_to_cart(struct Product *products, struct Cart *cart, int product_count) { //Đã sửa đổi từ so sánh từ tên sản phẩm sang so sánh mã sản phẩm
    displayProducts();
    display_cart_contents(cart);
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
            updateProductsFile(products, product_count);
            return;
        }
    }
    printf("Khong tim thay san pham trong danh sach!\n");
}

void delete_from_cart(struct Product *products, struct Cart *cart, int product_count) { //Đã sửa đổi từ so sánh từ tên sản phẩm sang so sánh mã sản phẩm
    if (cart->num_products == 0) {
        printf("Gio hang trong!\n");
        return;
    }
    displayProducts();
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

void modify_cart(struct Product *products, struct Cart *cart, int product_count) { //Không sửa đổi
    int choice;
    do {
        printf("\n1. Them san pham\n");
        printf("2. Xoa san pham\n");
        printf("3. Hoan tat chinh sua\n");
        printf("Nhap lua chon: ");
        if (scanf("%d", &choice) != 1) {
            printf("Nhap khong hop le!\n");
            return;
        }
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

void ExportOrderIntoFile(struct Cart *cart) { //In giỏ hàng vào file text (Xuất thành đơn mua)
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

void checkout(struct Cart *cart) { //Hàm thanh toán mới
    printf("\n======== Vui long dien thong tin khach hang ========");
    printf("\nTen: ");
    printf("\nDia chi: ");
    printf("\nHinh thuc thanh toan: ");
    cart->payment_status = 1;
    ExportOrderIntoFile(cart);
}

void work_with_cart(struct Product *products, struct Cart *cart, int product_count) { //Không sửa đổi
    int choice;
    do {
        printf("\n======== MENU ========");
        printf("\n1. Tao gio hang");
        printf("\n2. Them san pham vao gio hang");
        printf("\n3. Xoa san pham khoi gio hang");
        printf("\n4. Chinh sua gio hang");
        printf("\n5. Hoan tat mua sam va thanh toan");
        printf("\n0. Thoat");
        printf("\nNhap lua chon: ");
        if (scanf("%d", &choice) != 1) {
            printf("Nhap khong hop le!\n");
            return;
        }
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
                printf("Cam on ban da su dung dich vu!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}
