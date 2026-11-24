#include "product.h"
#include <stdio.h>
#include <string.h>
Product products[MAX_PRODUCTS];
int productCount = 0;

int FindProductById(int id)
{
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].id == id)
        {
            return i;
        }
    }
    return -1;
}
static bool HasVisibleCharacter(const char *text)
{
    for (int i = 0; text[i]!= '\0'; i++)
    {
        if (text[i] != ' ')
        {
            return true;
        }
    }
    return false;
}
ProductResult AddProduct(int id, const char *name, float price, int quantity)
{
    if (id <= 0)                                     return PRODUCT_ERR_ID;
    if (name == NULL || !HasVisibleCharacter(name))  return PRODUCT_ERR_NAME;
    if (price <= 0)                                  return PRODUCT_ERR_PRICE;
    if (quantity < 0)                                return PRODUCT_ERR_QTY;
    if (quantity > MAX_STOCK)                        return PRODUCT_ERR_TOO_MANY;
    if (productCount >= MAX_PRODUCTS)                return PRODUCT_ERR_FULL;
    if (FindProductById(id) != -1)                   return PRODUCT_ERR_DUPLICATE;
    products[productCount].id = id;
    strncpy(products[productCount].name, name, NAME_LEN - 1);
    products[productCount].name[NAME_LEN - 1] = '\0';   /* make sure text ends */
    products[productCount].price = price;
    products[productCount].quantity = quantity;
    productCount++;

    return PRODUCT_OK;
}
ProductResult RestockProduct(int index, int amount)
{
    if (index < 0 || index >= productCount)             return PRODUCT_ERR_NOT_FOUND;
    if (amount <= 0)                                    return PRODUCT_ERR_QTY;
    if (products[index].quantity + amount > MAX_STOCK)  return PRODUCT_ERR_TOO_MANY;

    products[index].quantity += amount;
    return PRODUCT_OK;
}
bool DeleteProductAt(int index)
{
    if (index < 0 ||index >= productCount)
    {
        return false;
    }
    for (int i = index; i < productCount - 1; i++)
    {
        products[i] = products[i + 1];   /* a struct can be copied in one line */
    }
    productCount--;
    return true;
}
bool IsLowStock(int quantity)
{
    return quantity <= LOW_STOCK_LIMIT;
}

int CountLowStock(void)
{
    int count = 0;
    for (int i = 0; i < productCount; i++)
    {
        if (IsLowStock(products[i].quantity))
        {
            count++;
        }
    }
    return count;
}
const char *ProductResultText(ProductResult result)
{
    switch (result)
    {
        case PRODUCT_OK:      return "Product added.";
        case PRODUCT_ERR_ID:    return "Product ID must be a positive number.";
        case PRODUCT_ERR_DUPLICATE: return "That product ID already exists.";
        case PRODUCT_ERR_NAME:   return "Product name cannot be empty.";
        case PRODUCT_ERR_PRICE:     return "Price must be greater than zero.";
        case PRODUCT_ERR_QTY:    return "Quantity must be a positive number.";
        case PRODUCT_ERR_TOO_MANY:  return "Stock cannot exceed 999999.";
        case PRODUCT_ERR_FULL:   return "Product list is full.";
        case PRODUCT_ERR_NOT_FOUND: return "Click a product row first.";
    }
    return "Unknown error.";
}

bool SaveProducts(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return false;
    }

    for (int i = 0;i < productCount; i++)
    {
        fprintf(file, "%d,%s,%.2f,%d\n",
                products[i].id, products[i].name, products[i].price, products[i].quantity);
    }

    return fclose(file) == 0;
}
int LoadProducts(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }

    productCount = 0;
    int loaded = 0;
    char line[200];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        int id, quantity;
        float price;
        char name[NAME_LEN];
        if (sscanf(line, "%d,%29[^,],%f,%d", &id, name, &price, &quantity) == 4)
        {
            if (AddProduct(id, name, price, quantity) == PRODUCT_OK)
            {
                loaded++;
            }
        }
    }

    fclose(file);
    return loaded;
}
