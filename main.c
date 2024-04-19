#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>


struct product {
    char productName[50];
    int quantity;
    double price;
};

struct Order {
    Product products;
    int num_products;
    float total_price;
    char buyer_name;
    char address;
    char phone;
    char payment_method;
    char payment_status;
};

struct Cart {
    Product products;
    int num_products;
    float total_price;
    char customer_id;
};

void add_product(struct product prod) {

}

int main() {
	int a = 5, b = 10;
    printf("hello world!\n");
    printf("chao moi nguoi minh ten la Long\n");
    printf("Minh la K19\n");
    int sum = a + b;
    printf("Sum a + b = %d", sum);
    return 0;
}
