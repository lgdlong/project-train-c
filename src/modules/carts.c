#include "../../include/libaries_and_define.h"
#include "../../include/products.h"
#include "../../include/carts.h"
#include "../../include/file.h"


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
struct customer_cart {
    struct customer_inf *customer;
    struct cart cart;
};

extern struct customer_cart customer_carts[MAX_CUSTOMERS];

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

