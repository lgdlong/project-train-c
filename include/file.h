#ifndef FILE_H
#define FILE_H


void readProductsFromFile(struct product *products, int *product_count);
void writeProductsToFile(struct product *products, int product_count);
void deleteFileContents(const char *filename);
void updateProductsFile(struct product *products, int product_count);
void ExportOrderIntoFile(struct cart *cart);

#endif