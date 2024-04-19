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
    struct product products;
    int num_products;
    float total_price;
    char buyer_name;
    char address;
    char phone;
    char payment_method;
    char payment_status;
};

struct Cart {
    struct product products;
    int num_products;
    float total_price;
    char customer_id;
};

void add_product(struct product prod) {

}

void menu(){
    while (true) {
        
    }
}

int main() {

    return 0;
}
