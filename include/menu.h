#ifndef MENU_H
#define MENU_H

void work_with_order(struct product *products, struct cart *cart, struct order *orders, int *product_count);
void work_with_cart(struct product *products, struct cart *cart, struct order *orders, int product_count);
void work_with_produts(struct product *products, struct cart *cart, struct order *orders, int product_count);

#endif