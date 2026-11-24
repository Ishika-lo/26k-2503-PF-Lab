#include "smartshop.h"
#include "product.h"
#include "billing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROW_H      26
#define LIST_ROWS  9
#define TABLE_Y    (CONTENT_Y + 135)
#define BAR_Y      (CONTENT_Y + CONTENT_H - 45)

/* Columns of the product list (left) and of the cart (right) */
#define LCOL_ID     (CONTENT_X + 28)
#define LCOL_NAME   (CONTENT_X + 80)
#define LCOL_PRICE  (CONTENT_X + 240)
#define LCOL_STOCK  (CONTENT_X + 300)
#define RCOL_NAME   (CONTENT_X + 380)
#define RCOL_QTY    (CONTENT_X + 508)
#define RCOL_PRICE  (CONTENT_X + 545)
#define RCOL_TOTAL  (CONTENT_X + 615)

/* The three text boxes of this screen */
typedef enum {
    BILL_CUSTOMER,
    BILL_SEARCH,
    BILL_QTY,
    BILL_COUNT
} BillBox;

/* Private data of this screen: it stays alive between frames ("static") */
static TextField fields[BILL_COUNT] = {
    {"", 0, NAME_LEN - 1, FIELD_TEXT},      /* customer name  */
    {"", 0, 20,           FIELD_TEXT},      /* search text    */
    {"", 0, 5,            FIELD_INTEGER}    /* quantity       */
};
static int  focusedBox = -1;        /* which box is being typed in; -1 means none */
static int  listScroll = 0;         /* scroll position of the product list */
static int  selectedProductId = 0;  /* ID of the chosen product; 0 means none */
static int  selectedCartRow = -1;   /* chosen cart line; -1 means none */
static bool receiptOpen = false;    /* is the receipt window open? */
static Receipt receipt;             /* the last finished bill */

/* Does "text" contain "search"? Upper/lower case does not matter. */
static bool ContainsText(const char *text, const char *search)
{
    int textLen = (int)strlen(text);
    int searchLen = (int)strlen(search);

    for (int start = 0; start + searchLen <= textLen; start++)
    {
        int k = 0;
        while (k < searchLen &&
               tolower((unsigned char)text[start + k]) == tolower((unsigned char)search[k]))
        {
            k++;
        }
        if (k == searchLen)
        {
            return true;   /* an empty search matches everything */
        }
    }
    return false;
}

/* Add the chosen product, with the typed quantity, to the cart */
static void AddSelectedToCart(void)
{
    int index = (selectedProductId > 0) ? FindProductById(selectedProductId) : -1;
    if (index < 0)
    {
        SetStatus("Click a product in the list first.", STATUS_ERROR);
        return;
    }

    int quantity = atoi(fields[BILL_QTY].text);   /* empty text gives 0 */
    CartResult result = AddToCart(index, quantity);

    if (result == CART_OK)
    {
        SetStatus(TextFormat("Added %d x %s to the cart.", quantity, products[index].name),
                  STATUS_SUCCESS);
        ClearTextField(&fields[BILL_QTY]);
    }
    else if (result == CART_ERR_STOCK)
    {
        SetStatus(TextFormat("Not enough stock: %d available, %d already in cart.",
                             products[index].quantity, QuantityInCart(products[index].id)),
                  STATUS_ERROR);
    }
    else
    {
        SetStatus(CartResultText(result), STATUS_ERROR);
    }
}

/* Complete the sale */
static void DoCheckout(void)
{
    /* Copy the file paths first: DataFilePath reuses one temporary text buffer */
    char productsPath[260];
    char salesPath[260];
    snprintf(productsPath, sizeof(productsPath), "%s", DataFilePath("products.txt"));
    snprintf(salesPath, sizeof(salesPath), "%s", DataFilePath("sales.txt"));

    CheckoutResult result = Checkout(fields[BILL_CUSTOMER].text, productsPath, salesPath, &receipt);

    if (result == CHECKOUT_OK)
    {
        receiptOpen = true;
        selectedCartRow = -1;
        ClearTextField(&fields[BILL_CUSTOMER]);
        ClearTextField(&fields[BILL_QTY]);

        if (receipt.productsFileSaved)
        {
            SetStatus(TextFormat("Sale completed. Bill No. %d", receipt.sale.saleNumber),
                      STATUS_SUCCESS);
        }
        else
        {
            SetStatus("Sale saved, but products.txt could not be updated!", STATUS_ERROR);
        }
    }
    else
    {
        SetStatus(CheckoutResultText(result), STATUS_ERROR);
    }
}

/* The receipt window. Draws it and handles its button. */
static void DrawReceiptWindow(void)
{
    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0, 0, 0, 120});   /* dim the screen */

    Rectangle dlg = {250, 30, 500, 590};
    int x = (int)dlg.x;
    int y = (int)dlg.y;
    DrawRectangle(x, y, (int)dlg.width, (int)dlg.height, WHITE);
    DrawRectangle(x, y, (int)dlg.width, 56, navy);
    DrawText("SmartShop Receipt", x + 25, y + 14, 26, WHITE);

    DrawText(TextFormat("Bill No: %d", receipt.sale.saleNumber), x + 25, y + 70, 18, DARKGRAY);
    DrawText(receipt.sale.date, x + 300, y + 70, 18, DARKGRAY);
    DrawText(TextFormat("Customer: %s", receipt.sale.customer), x + 25, y + 96, 18, DARKGRAY);

    /* Table of items */
    DrawRectangle(x + 20, y + 128, 460, 26, navy);
    DrawText("Item",     x + 25,  y + 133, 16, WHITE);
    DrawText("Qty",      x + 280, y + 133, 16, WHITE);
    DrawText("Price",    x + 340, y + 133, 16, WHITE);
    DrawText("Subtotal", x + 405, y + 133, 16, WHITE);

    for (int i = 0; i < receipt.itemCount; i++)
    {
        int rowY = y + 156 + i * 22;
        float subtotal = receipt.items[i].price * receipt.items[i].quantity;

        DrawTextClipped(receipt.items[i].name, x + 25, rowY, 16, 245, DARKGRAY);
        DrawText(TextFormat("%d", receipt.items[i].quantity),   x + 280, rowY, 16, DARKGRAY);
        DrawText(TextFormat("%.2f", receipt.items[i].price),    x + 340, rowY, 16, DARKGRAY);
        DrawText(TextFormat("%.2f", subtotal),                  x + 405, rowY, 16, DARKGRAY);
    }

    DrawRectangle(x + 20, y + 362, 460, 2, lightBg);
    DrawText(TextFormat("Total items: %d", receipt.sale.totalQuantity), x + 25, y + 374, 18, DARKGRAY);
    DrawText(TextFormat("TOTAL: %.2f", receipt.sale.totalAmount), x + 25, y + 400, 28, navy);

    /* VIP information */
    if (receipt.sale.vipNumber > 0)
    {
        DrawText(TextFormat("VIP customer number: VIP-%03d", receipt.sale.vipNumber),
                 x + 25, y + 445, 20, green);
    }
    else if (receipt.customerSpent > 0)
    {
        DrawText(TextFormat("Spent so far: %.2f  (VIP number at %.0f)",
                            receipt.customerSpent, VIP_LIMIT),
                 x + 25, y + 447, 16, GRAY);
    }
    else
    {
        DrawText("Enter a customer name to earn a VIP number.", x + 25, y + 447, 16, GRAY);
    }

    DrawText("Thank you for shopping at SmartShop!", x + 25, y + 480, 16, GRAY);

    Rectangle closeBtn = {dlg.x + 150, dlg.y + 520, 200, 44};
    if (DrawButton(closeBtn, "New bill", green, greenHover) || IsKeyPressed(KEY_ESCAPE))
    {
        receiptOpen = false;
        SetStatus("Ready for the next customer.", STATUS_INFO);
    }
}

void DrawBillingScreen(void)
{
    /* While the receipt window is open, the rest of the screen ignores the mouse and keyboard */
    bool locked = receiptOpen;
    bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    Vector2 mouse = GetMousePosition();

    Rectangle panel = {CONTENT_X, CONTENT_Y, CONTENT_W, CONTENT_H};
    DrawPanel(panel, "Billing");

    /* Positions of the 3 boxes and the buttons */
    Rectangle boxes[BILL_COUNT] = {
        {CONTENT_X + 20,  CONTENT_Y + 82, 260, 36},   /* Customer */
        {CONTENT_X + 300, CONTENT_Y + 82, 240, 36},   /* Search   */
        {CONTENT_X + 20,  BAR_Y,          70,  36}    /* Quantity */
    };
    Rectangle addBtn      = {CONTENT_X + 100, BAR_Y, 130, 36};
    Rectangle removeBtn   = {CONTENT_X + 370, BAR_Y, 90,  36};
    Rectangle clearBtn    = {CONTENT_X + 470, BAR_Y, 80,  36};
    Rectangle checkoutBtn = {CONTENT_X + 560, BAR_Y, 140, 36};
    Rectangle listRect    = {CONTENT_X + 20, TABLE_Y, 330, ROW_H * (LIST_ROWS + 1)};

    if (selectedCartRow >= cartCount)
    {
        selectedCartRow = -1;
    }

    /* ----- Input: which box did the user click? ----- */
    if (!locked && clicked)
    {
        focusedBox = -1;
        for (int i = 0; i < BILL_COUNT; i++)
        {
            if (CheckCollisionPointRec(mouse, boxes[i]))
            {
                focusedBox = i;
            }
        }
    }

    if (!locked && IsKeyPressed(KEY_TAB))
    {
        focusedBox = (focusedBox + 1) % BILL_COUNT;
    }

    if (!locked && focusedBox >= 0)
    {
        UpdateTextField(&fields[focusedBox]);

        if (focusedBox == BILL_QTY && (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)))
        {
            AddSelectedToCart();
        }
    }

    /* ----- Find the products that match the search text ----- */
    int matches[MAX_PRODUCTS];
    int matchCount = 0;
    for (int i = 0; i < productCount; i++)
    {
        char idText[16];
        snprintf(idText, sizeof(idText), "%d", products[i].id);

        if (ContainsText(products[i].name, fields[BILL_SEARCH].text) ||
            ContainsText(idText, fields[BILL_SEARCH].text))
        {
            matches[matchCount] = i;
            matchCount++;
        }
    }

    /* Mouse wheel scrolls the product list while the mouse is over it */
    float wheel = GetMouseWheelMove();
    if (!locked && CheckCollisionPointRec(mouse, listRect))
    {
        if (wheel > 0) listScroll--;
        if (wheel < 0) listScroll++;
    }
    int maxScroll = matchCount - LIST_ROWS;
    if (maxScroll < 0) maxScroll = 0;
    if (listScroll > maxScroll) listScroll = maxScroll;
    if (listScroll < 0) listScroll = 0;

    /* ----- Drawing: the top boxes ----- */
    DrawText("Customer name (optional)", (int)boxes[BILL_CUSTOMER].x, (int)boxes[BILL_CUSTOMER].y - 20, 16, GRAY);
    DrawText("Search product (name or ID)", (int)boxes[BILL_SEARCH].x, (int)boxes[BILL_SEARCH].y - 20, 16, GRAY);
    DrawText("Quantity", (int)boxes[BILL_QTY].x, BAR_Y - 17, 14, GRAY);
    for (int i = 0; i < BILL_COUNT; i++)
    {
        DrawTextField(boxes[i], &fields[i], focusedBox == i);
    }

    DrawRectangle(CONTENT_X + 20, TABLE_Y, 330, ROW_H, navy);
    DrawText("ID",    LCOL_ID,    TABLE_Y + 5, 16, WHITE);
    DrawText("Name",  LCOL_NAME,  TABLE_Y + 5, 16, WHITE);
    DrawText("Price", LCOL_PRICE, TABLE_Y + 5, 16, WHITE);
    DrawText("Stock", LCOL_STOCK, TABLE_Y + 5, 16, WHITE);

    if (matchCount == 0)
    {
        DrawText(productCount == 0 ? "No products yet. Add some first." : "No product matches.",
                 CONTENT_X + 30, TABLE_Y + ROW_H + 10, 16, GRAY);
    }

    for (int row = 0; row < LIST_ROWS && listScroll + row < matchCount; row++)
    {
        int i = matches[listScroll + row];       /* position in the products array */
        int y = TABLE_Y + ROW_H * (row + 1);
        Rectangle rowRect = {CONTENT_X + 20, y, 330, ROW_H};

        if (!locked && clicked && CheckCollisionPointRec(mouse, rowRect))
        {
            selectedProductId = products[i].id;
            SetStatus(TextFormat("Selected: %s", products[i].name), STATUS_INFO);
        }

        if (products[i].id == selectedProductId)
        {
            DrawRectangle(CONTENT_X + 20, y, 330, ROW_H, (Color){190, 215, 250, 255});
        }
        else if (row % 2 == 0)
        {
            DrawRectangle(CONTENT_X + 20, y, 330, ROW_H, lightBg);
        }

        DrawText(TextFormat("%d", products[i].id), LCOL_ID, y + 5, 16, DARKGRAY);
        DrawTextClipped(products[i].name, LCOL_NAME, y + 5, 16, 150, DARKGRAY);
        DrawText(TextFormat("%.2f", products[i].price), LCOL_PRICE, y + 5, 16, DARKGRAY);
        DrawText(TextFormat("%d", products[i].quantity), LCOL_STOCK, y + 5, 16,
                 IsLowStock(products[i].quantity) ? red : DARKGRAY);
    }

    if (matchCount > LIST_ROWS)
    {
        DrawText("Mouse wheel scrolls the list", CONTENT_X + 30,
                 TABLE_Y + ROW_H * (LIST_ROWS + 1) + 6, 14, GRAY);
    }

    DrawRectangle(CONTENT_X + 370, TABLE_Y, 330, ROW_H, navy);
    DrawText("Cart",  RCOL_NAME,  TABLE_Y + 5, 16, WHITE);
    DrawText("Qty",   RCOL_QTY,   TABLE_Y + 5, 16, WHITE);
    DrawText("Price", RCOL_PRICE, TABLE_Y + 5, 16, WHITE);
    DrawText("Total", RCOL_TOTAL, TABLE_Y + 5, 16, WHITE);

    if (cartCount == 0)
    {
        DrawText("Cart is empty.", RCOL_NAME, TABLE_Y + ROW_H + 10, 16, GRAY);
    }

    for (int i = 0; i < cartCount; i++)
    {
        int y = TABLE_Y + ROW_H * (i + 1);
        Rectangle rowRect = {CONTENT_X + 370, y, 330, ROW_H};

        if (!locked && clicked && CheckCollisionPointRec(mouse, rowRect))
        {
            selectedCartRow = i;
        }

        if (i == selectedCartRow)
        {
            DrawRectangle(CONTENT_X + 370, y, 330, ROW_H, (Color){190, 215, 250, 255});
        }
        else if (i % 2 == 0)
        {
            DrawRectangle(CONTENT_X + 370, y, 330, ROW_H, lightBg);
        }

        DrawTextClipped(cart[i].name, RCOL_NAME, y + 5, 16, 120, DARKGRAY);
        DrawText(TextFormat("%d", cart[i].quantity), RCOL_QTY, y + 5, 16, DARKGRAY);
        DrawText(TextFormat("%.2f", cart[i].price), RCOL_PRICE, y + 5, 16, DARKGRAY);
        DrawText(TextFormat("%.2f", cart[i].price * cart[i].quantity), RCOL_TOTAL, y + 5, 16, DARKGRAY);
    }

    DrawText(TextFormat("Items: %d", CartTotalQuantity()),
             RCOL_NAME, TABLE_Y + ROW_H * (LIST_ROWS + 1) + 6, 18, DARKGRAY);
    DrawText(TextFormat("TOTAL: %.2f", CartTotalAmount()),
             CONTENT_X + 500, TABLE_Y + ROW_H * (LIST_ROWS + 1) + 4, 20, navy);

    if (DrawButton(addBtn, "Add to cart", green, greenHover) && !locked)
    {
        AddSelectedToCart();
    }

    if (DrawButton(removeBtn, "Remove", red, redHover) && !locked)
    {
        if (selectedCartRow >= 0 && selectedCartRow < cartCount)
        {
            SetStatus(TextFormat("Removed from cart: %s", cart[selectedCartRow].name), STATUS_INFO);
            RemoveFromCart(selectedCartRow);
            selectedCartRow = -1;
        }
        else
        {
            SetStatus("Click a cart item first.", STATUS_ERROR);
        }
    }

    if (DrawButton(clearBtn, "Clear", navActive, navyHover) && !locked)
    {
        if (cartCount > 0)
        {
            ClearCart();
            selectedCartRow = -1;
            SetStatus("Cart cleared.", STATUS_INFO);
        }
        else
        {
            SetStatus("The cart is already empty.", STATUS_ERROR);
        }
    }

    if (DrawButton(checkoutBtn, "Checkout", green, greenHover) && !locked)
    {
        DoCheckout();
    }

    if (receiptOpen)
    {
        DrawReceiptWindow();
    }
}
