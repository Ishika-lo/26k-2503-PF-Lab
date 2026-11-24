#include "billing.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

CartItem cart[MAX_CART_ITEMS];
int cartCount = 0;
Sale sales[MAX_SALES];
int saleCount = 0;

int QuantityInCart(int productId)
{
    for (int i = 0; i < cartCount; i++)
    {
        if (cart[i].productId == productId)
        {
            return cart[i].quantity;
        }
    }
    return 0;
}

CartResult AddToCart(int productIndex, int quantity)
{
    if (productIndex < 0 || productIndex >= productCount) return CART_ERR_NOT_FOUND;
    if (quantity <= 0) return CART_ERR_QTY;

    Product *p = &products[productIndex];
    int already = QuantityInCart(p->id);

    if (already + quantity > p->quantity) return CART_ERR_STOCK;

    for (int i = 0; i < cartCount; i++)
    {
        if (cart[i].productId == p->id)
        {
            cart[i].quantity += quantity;
            return CART_OK;
        }
    }

    if (cartCount >= MAX_CART_ITEMS) return CART_ERR_FULL;

    cart[cartCount].productId = p->id;
    strncpy(cart[cartCount].name, p->name, NAME_LEN - 1);
    cart[cartCount].name[NAME_LEN - 1] = '\0';
    cart[cartCount].price = p->price;
    cart[cartCount].quantity = quantity;
    cartCount++;
    return CART_OK;
}

void RemoveFromCart(int cartIndex)
{
    if (cartIndex < 0 || cartIndex >= cartCount)
    {
        return;
    }
    for (int i = cartIndex; i < cartCount - 1; i++)
    {
        cart[i] = cart[i + 1];
    }
    cartCount--;
}

void ClearCart(void)
{
    cartCount = 0;
}

int CartTotalQuantity(void)
{
    int total = 0;
    for (int i = 0; i < cartCount; i++)
    {
        total += cart[i].quantity;
    }
    return total;
}

float CartTotalAmount(void)
{
    double total = 0;
    for (int i = 0; i < cartCount; i++)
    {
        total += (double)cart[i].price * cart[i].quantity;
    }
    return (float)total;
}

const char *CartResultText(CartResult result)
{
    switch (result)
    {
        case CART_OK:    return "Added to cart.";
        case CART_ERR_NOT_FOUND: return "Click a product in the list first.";
        case CART_ERR_QTY:  return "Type a quantity greater than zero.";
        case CART_ERR_STOCK: return "Not enough stock.";
        case CART_ERR_FULL: return "Cart is full (9 different items). Complete the bill first.";
    }
    return "Unknown error.";
}

static void TrimCopy(char *dest, size_t size, const char *src)
{
    while (*src == ' ')
    {
        src++;
    }
    snprintf(dest, size, "%s", src);

    size_t len = strlen(dest);
    while (len > 0 && dest[len - 1] == ' ')
    {
        len--;
        dest[len] = '\0';
    }
}

static bool SameText(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0')
    {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
        {
            return false;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

static float CustomerSpent(const char *name)
{
    double total = 0;
    for (int i = 0; i < saleCount; i++)
    {
        if (SameText(sales[i].customer, name))
        {
            total += sales[i].totalAmount;
        }
    }
    return (float)total;
}

static int CustomerVipNumber(const char *name)
{
    for (int i = 0; i < saleCount; i++)
    {
        if (SameText(sales[i].customer, name) && sales[i].vipNumber > 0)
        {
            return sales[i].vipNumber;
        }
    }
    return 0;
}

static int NextVipNumber(void)
{
    int highest = 0;
    for (int i = 0; i < saleCount; i++)
    {
        if (sales[i].vipNumber > highest)
        {
            highest = sales[i].vipNumber;
        }
    }
    return highest + 1;
}

static int NextSaleNumber(void)
{
    int highest = 0;
    for (int i = 0; i < saleCount; i++)
    {
        if (sales[i].saleNumber > highest)
        {
            highest = sales[i].saleNumber;
        }
    }
    return highest + 1;
}

static void FormatNow(char *out, size_t size)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    if (local == NULL || strftime(out, size, "%Y-%m-%d %H:%M", local) == 0)
    {
        snprintf(out, size, "unknown");
    }
}

static void BuildItemsText(const Receipt *r, char *out, size_t size)
{
    out[0] = '\0';
    size_t used = 0;

    for (int i = 0; i < r->itemCount; i++)
    {
        int written = snprintf(out + used, size - used, "%s%s x%d",
                               i > 0 ? "; " : "", r->items[i].name, r->items[i].quantity);
        if (written < 0 || (size_t)written >= size - used)
        {
            break;
        }
        used += (size_t)written;
    }
}

static bool AppendSale(const char *filename, const Sale *s)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        return false;
    }
    fprintf(file, "%d,%s,%s,%d,%.2f,%d,%s\n",
            s->saleNumber, s->date, s->customer, s->totalQuantity,
            s->totalAmount, s->vipNumber, s->itemsText);

    return fclose(file) == 0;
}

int LoadSales(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }

    saleCount = 0;
    char line[400];

    while (saleCount < MAX_SALES && fgets(line, sizeof(line), file) != NULL)
    {
        Sale s;
        memset(&s, 0, sizeof(s));

        if (sscanf(line, "%d,%19[^,],%29[^,],%d,%f,%d,%199[^\n]",
                   &s.saleNumber, s.date, s.customer, &s.totalQuantity,
                   &s.totalAmount, &s.vipNumber, s.itemsText) == 7
            && s.saleNumber > 0 && s.totalAmount >= 0)
        {
            size_t n = strlen(s.itemsText);
            while (n > 0 && (s.itemsText[n - 1] == '\r' || s.itemsText[n - 1] == '\n'))
            {
                n--;
                s.itemsText[n] = '\0';
            }
            sales[saleCount] = s;
            saleCount++;
        }
    }

    fclose(file);
    return saleCount;
}

CheckoutResult Checkout(const char *customerName, const char *productsFile,
                        const char *salesFile, Receipt *receipt)
{
    if (cartCount == 0)          return CHECKOUT_EMPTY;
    if (saleCount >= MAX_SALES)  return CHECKOUT_HISTORY_FULL;

    for (int i = 0; i < cartCount; i++)
    {
        int p = FindProductById(cart[i].productId);
        if (p == -1) return CHECKOUT_PRODUCT_MISSING;
        if (cart[i].quantity > products[p].quantity) return CHECKOUT_NOT_ENOUGH_STOCK;
    }

    memset(receipt, 0, sizeof(*receipt));
    receipt->itemCount = cartCount;
    for (int i = 0; i < cartCount; i++)
    {
        receipt->items[i] = cart[i];
    }

    char customer[NAME_LEN];
    TrimCopy(customer, sizeof(customer), customerName);
    bool named = (customer[0] != '\0');

    Sale *s = &receipt->sale;
    s->saleNumber    = NextSaleNumber();
    s->totalQuantity = CartTotalQuantity();
    s->totalAmount   = CartTotalAmount();
    snprintf(s->customer, sizeof(s->customer), "%s", named ? customer : "Walk-in");
    FormatNow(s->date, sizeof(s->date));
    BuildItemsText(receipt, s->itemsText, sizeof(s->itemsText));

    s->vipNumber = 0;
    receipt->customerSpent = 0;
    if (named)
    {
        receipt->customerSpent = CustomerSpent(customer) + s->totalAmount;

        int existing = CustomerVipNumber(customer);
        if (existing > 0)
        {
            s->vipNumber = existing;
        }
        else if (receipt->customerSpent >= VIP_LIMIT)
        {
            s->vipNumber = NextVipNumber();
        }
    }

    if (!AppendSale(salesFile, s))
    {
        return CHECKOUT_SAVE_FAILED;
    }
    sales[saleCount] = *s;
    saleCount++;

    for (int i = 0; i < cartCount; i++)
    {
        int p = FindProductById(cart[i].productId);
        products[p].quantity -= cart[i].quantity;
    }
    receipt->productsFileSaved = SaveProducts(productsFile);

    ClearCart();
    return CHECKOUT_OK;
}

const char *CheckoutResultText(CheckoutResult result)
{
    switch (result)
    {
        case CHECKOUT_OK: return "Sale completed.";
        case CHECKOUT_EMPTY:       return "The cart is empty.";
        case CHECKOUT_PRODUCT_MISSING:  return "A cart item was deleted from Products. Remove it and try again.";
        case CHECKOUT_NOT_ENOUGH_STOCK:  return "A cart item has less stock now. Remove it or lower its quantity.";
        case CHECKOUT_HISTORY_FULL:   return "Sales history is full (500 sales).";
        case CHECKOUT_SAVE_FAILED:  return "Could not save the sale to sales.txt. Nothing was changed.";
    }
    return "Unknown error.";
}
