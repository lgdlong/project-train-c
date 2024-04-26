#ifndef CARTS_H
#define CARTS_H

void display_cart_contents(struct cart *cart);
void displayAllCarts();
void create_cart(struct cart *cart, struct customer_inf *customer, struct product *products, int product_count);
void add_to_cart(struct product *products, struct cart *cart, int product_count);
void delete_from_cart(struct product *products, struct cart *cart, int product_count);
void modify_cart(struct product *products, struct cart *cart, int product_count);

#endif