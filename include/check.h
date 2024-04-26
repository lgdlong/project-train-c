#ifndef CHECK_H
#define CHECK_H

bool isValidQuantity(int quantity);
bool isValidIndex(int index, int array_size);
int getIntegerInput();
bool isProductInCart(int code_of_product, struct cart cart);
bool isValidCartInput(int code_of_product, int quantity, struct product *products, int product_count);

#endif