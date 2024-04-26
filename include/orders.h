#ifndef ORDERS_H
#define ORDERS_H

void checkout(struct cart *cart);
void createOrder(struct cart *cart, struct order *order);
void cancelOrder(struct order *orders, int *order_count);
void modifyOrder(struct order *orders, int order_count);
void displayOrder(struct order *orders);

#endif