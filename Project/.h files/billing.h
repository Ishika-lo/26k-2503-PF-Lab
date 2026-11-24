#ifndef BILLING_H
#define BILLING_H

#include <stdbool.h>
#include "product.h"
#define MAX_CART_ITEMS  9
#define MAX_SALES       500
#define ITEMS_TEXT_LEN  200
#define VIP_LIMIT       5000.0f

typedef struct {
    int   productId;
    char  name[NAME_LEN];
    float price;
    int   quantity;
} CartItem;

typedef struct {
    int   saleNumber;
    char  date[20];
    char  customer[NAME_LEN];
    int   totalQuantity;
    float totalAmount;
    int   vipNumber;
    char  itemsText[ITEMS_TEXT_LEN];
} Sale;

typedef struct {
    Sale     sale;
    CartItem items[MAX_CART_ITEMS];
    int      itemCount;
    float    customerSpent;
    bool     productsFileSaved;
} Receipt;

typedef enum {
    CART_OK,
    CART_ERR_NOT_FOUND,
    CART_ERR_QTY,
    CART_ERR_STOCK,
    CART_ERR_FULL
} CartResult;

typedef enum {
    CHECKOUT_OK,
    CHECKOUT_EMPTY,
    CHECKOUT_PRODUCT_MISSING,
    CHECKOUT_NOT_ENOUGH_STOCK,
    CHECKOUT_HISTORY_FULL,
    CHECKOUT_SAVE_FAILED
} CheckoutResult;

extern CartItem cart[MAX_CART_ITEMS];
extern int cartCount;
extern Sale sales[MAX_SALES];
extern int saleCount;

CartResult AddToCart(int productIndex, int quantity);
void  RemoveFromCart(int cartIndex);
void  ClearCart(void);
int   QuantityInCart(int productId);
int   CartTotalQuantity(void);
float CartTotalAmount(void);
const char *CartResultText(CartResult result);

CheckoutResult Checkout(const char *customerName, const char *productsFile,
                        const char *salesFile, Receipt *receipt);
const char *CheckoutResultText(CheckoutResult result);

int LoadSales(const char *filename);

#endif
