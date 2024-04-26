#ifndef ORDERS_H
#define ORDERS_H

extern int order_count;

void fill_customer_inf(struct customer_inf *customer);
void checkout(struct cart *cart);
void createOrder(struct cart *cart, struct order *order);
void cancelOrder(struct order *orders, int *order_count);
void modifyOrder(struct order *orders, int order_count);
void displayOrder(struct order *orders);

#endif