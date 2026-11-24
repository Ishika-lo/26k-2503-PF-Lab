#ifndef PRODUCT_H
#define PRODUCT_H
#include <stdbool.h>

#define MAX_PRODUCTS     100
#define NAME_LEN         30
#define LOW_STOCK_LIMIT  5
#define MAX_STOCK        999999

typedef struct {
    int   id;
    char  name[NAME_LEN];
    float price;
    int   quantity;
} Product;
typedef enum {
    PRODUCT_OK,
    PRODUCT_ERR_ID,
    PRODUCT_ERR_DUPLICATE,
    PRODUCT_ERR_NAME,
    PRODUCT_ERR_PRICE,
    PRODUCT_ERR_QTY,
    PRODUCT_ERR_TOO_MANY,
    PRODUCT_ERR_FULL,
    PRODUCT_ERR_NOT_FOUND
} ProductResult;
extern Product products[MAX_PRODUCTS];
extern int productCount;

ProductResult AddProduct(int id, const char *name, float price, int quantity);
ProductResult RestockProduct(int index, int amount);
bool DeleteProductAt(int index);
int  FindProductById(int id);
bool IsLowStock(int quantity);
int  CountLowStock(void);
const char *ProductResultText(ProductResult result);

bool SaveProducts(const char *filename);
int  LoadProducts(const char *filename);

#endif
