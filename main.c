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

#define MAX_PRODUCTS 50
#include "menu.c"

struct product {
    char productName[50];
    int quantity;
    double price;
};

struct order {
    struct product products;
    int num_products;
    float total_price;
    char buyer_name;
    char address;
    char phone;
    char payment_method;
    char payment_status;
};

struct cart {
    struct product products;
    int num_products;
    float total_price;
    char customer_id;
};

void menu() {
    int maxproducts = 50;

    int choice; // menu mẹ
    // int choice1; // menu con cấp 1
    // int choice2; // menu con cấp 2
    
    int n; // số lượng sản phẩm trong 
    
    struct order *ord = (struct order *)malloc(maxproducts * sizeof(struct order));

    do {
        ds_1();
        lua_chon(&choice);

        switch (choice) {
            case 1: // Làm việc với sản phẩm
                work_with_san_pham();
                break;
            case 2: // Giỏ hàng: thêm, xóa, sửa số lượng
                work_with_gio_hang();
                break;
            case 3:
            // Đơn mua: thông tin cá nhân, xuất đơn mua
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

                // BẮT ĐẦU CODE
                int num, choice1;
                printf("1. Them don mua\n");
                printf("2. Xoa don mua\n");
                printf("3. Sua don mua\n");
                printf("4. Quay ve danh sach lua chon truoc do\n");
                printf("\n");

                lua_chon(&choice1);

                do {
                    switch (choice1) {
                        case 1:
                            // --> in ra giỏ hàng

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
                break;

            case 4:
                return;
            
            default:
                printf("Invalid choice!\n");

        }
    } while (choice != 4);
}

void addProduct(struct product *products, int *product_count) {
    printf("Nhap ten san pham: ");
    getchar(); 
    fgets(products[*product_count].productName, sizeof(products[*product_count].productName), stdin);
    products[*product_count].productName[strcspn(products[*product_count].productName, "\n")] = '\0';

    printf("Nhap so luong: ");
    scanf("%d", &products[*product_count].quantity);

    printf("Nhap gia san pham: ");
    scanf("%lf", &products[*product_count].price);

    (*product_count)++;
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

void create_cart(struct cart *cart) { // Hàm tạo giỏ hàng
    cart->num_products = 0;
    cart->total_price = 0;
    printf("Gio hang da duoc tao!\n");
}

void add_to_cart(struct product *products, struct cart *cart, int product_count) { // Hàm thêm sản phẩm vào giỏ hàng
    displayProducts(products, product_count);
    char name_of_product[50];
    int quantity;
    printf("Nhap ten san pham muon them: ");
    scanf("%s", name_of_product);

    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].productName, name_of_product) == 0) {
            printf("Nhap so luong: ");
            scanf("%d", &quantity);
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
            return;
        }
    }
    printf("Khong tim thay san pham trong danh sach!\n");
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

void delete_from_cart(struct product *products, struct cart *cart, int product_count) { // Hàm xóa sản phẩm từ giỏ hàng
    if (cart->num_products == 0) {
        printf("Gio hang trong!\n");
        return;
    }

    displayProducts(products, product_count);
    char name_of_product[50];
    int quantity;
    printf("Nhap ten san pham muon xoa: ");
    scanf("%s", name_of_product);

    for (int i = 0; i < cart->num_products; i++) {
        if (strcmp(cart->products[i].productName, name_of_product) == 0) {
            printf("Nhap so luong: ");
            scanf("%d", &quantity);
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
        printf("Nhap lua chon: ");
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

void checkout(struct cart *cart) { // Hàm thanh toán
    printf("\n======== Vui long dien thong tin khach hang ========");
    printf("\nTen: ");
    printf("\nDia chi: ");
    printf("\nHinh thuc thanh toan: ");
}

void work_with_cart(struct product *products, struct cart *cart, int product_count) { // Hàm làm việc với giỏ hàng
    int choice;
    do {
        printf("\n======== MENU ========");
        printf("\n1. Tao moi gio hang");
        printf("\n2. Them san pham vao gio hang");
        printf("\n3. Xoa san pham khoi gio hang");
        printf("\n4. Chinh sua gio hang");
        printf("\n5. Hoan tat mua sam va thanh toan");
        printf("\n0. Thoat");
        printf("\nNhap lua chon: ");
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
                printf("Cam on ban da su dung dich vu!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}

void work_with_produts(struct product *products, struct cart *cart, int product_count) {
    int choice;
    do {
        printf("\n======== MENU ========");
        printf("\n1. Them san pham");
        printf("\n2. Hien thi danh sach san pham");
        printf("\n3. Chinh sua thong tin san pham");
        printf("\n4. Lam viec voi gio hang");
        printf("\n0. Thoat");
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
                work_with_cart(products, &*cart, product_count);
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
	struct product products[50];
    struct cart cart;
    int product_count = 0;

    work_with_produts(products, &cart, product_count);
    
    menu();

    return 0;
}

/*
Đơn mua là sau khi thêm vào giỏ hàng và nhấn mua
*/