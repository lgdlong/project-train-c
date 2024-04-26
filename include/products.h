#ifndef PRODUCTS_H
#define PRODUCTS_H

void displayProducts(struct product *products, int product_count);
void addProduct(struct product *products, int *product_count);
void fixProducts(struct product *products, int product_count);

#endif