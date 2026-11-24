#include "smartshop.h"
#include "product.h"
#include <stdlib.h>

#define ROW_H            28
#define MAX_VISIBLE_ROWS 9
#define BAR_Y            (CONTENT_Y + CONTENT_H - 45)
#define COL_ID      (CONTENT_X + 30)
#define COL_NAME    (CONTENT_X + 110)
#define COL_PRICE   (CONTENT_X + 400)
#define COL_QTY     (CONTENT_X + 520)
#define COL_STATUS  (CONTENT_X + 610)
typedef enum {
    FORM_ID,
    FORM_NAME,
    FORM_PRICE,
    FORM_QTY,
    FORM_RESTOCK,
    BOX_COUNT
} FormBox;

static TextField fields[BOX_COUNT] = {
    {"", 0, 6,            FIELD_INTEGER},
    {"", 0, NAME_LEN - 1, FIELD_TEXT},
    {"", 0, 9,            FIELD_DECIMAL},
    {"", 0, 6,            FIELD_INTEGER},
    {"", 0, 6,            FIELD_INTEGER}
};
static int  focusedBox = -1;
static int  scrollOffset = 0;
static int  selectedRow = -1;
static bool confirmingDelete = false;
static void SaveChanges(void)
{
    if (!SaveProducts(DataFilePath("products.txt")))
    {
        SetStatus("Warning: could not save products.txt", STATUS_ERROR);
    }
}

static void SubmitForm(void)
{

    for (int i = 0; i < FORM_RESTOCK; i++)
    {
        if (fields[i].length == 0)
        {
            SetStatus("Please fill in all four fields.", STATUS_ERROR);
            return;
        }
    }
    int   id       = atoi(fields[FORM_ID].text);
    float price    = (float)atof(fields[FORM_PRICE].text);
    int   quantity = atoi(fields[FORM_QTY].text);
    ProductResult result = AddProduct(id, fields[FORM_NAME].text, price, quantity);

    if (result == PRODUCT_OK)
    {
        SetStatus(TextFormat("Product added: %s", fields[FORM_NAME].text), STATUS_SUCCESS);

        for (int i = 0; i < FORM_RESTOCK; i++)
        {
            ClearTextField(&fields[i]);
        }
        focusedBox = FORM_ID;
        scrollOffset = productCount - MAX_VISIBLE_ROWS;
        if (scrollOffset < 0) scrollOffset = 0;

        SaveChanges();
    }
    else
    {
        SetStatus(ProductResultText(result), STATUS_ERROR);
    }
}
static void RestockSelected(void)
{
    if (selectedRow < 0 || selectedRow >= productCount)
    {
        SetStatus("Click a product row first.", STATUS_ERROR);
        return;
    }

    int amount = atoi(fields[FORM_RESTOCK].text);
    if (amount <= 0)
    {
        SetStatus("Type how many units to add.", STATUS_ERROR);
        return;
    }

    ProductResult result = RestockProduct(selectedRow, amount);
    if (result == PRODUCT_OK)
    {
        SetStatus(TextFormat("Added %d units to %s. New stock: %d.",
                             amount, products[selectedRow].name,
                             products[selectedRow].quantity), STATUS_SUCCESS);
        ClearTextField(&fields[FORM_RESTOCK]);
        SaveChanges();
    }
    else
    {
        SetStatus(ProductResultText(result), STATUS_ERROR);
    }
}
static void DrawDeleteDialog(void)
{
    if (selectedRow < 0 || selectedRow >= productCount)
    {
        confirmingDelete = false;
        return;
    }

    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0, 0, 0, 120});

    Rectangle dlg = {290, 230, 420, 190};
    DrawRectangle((int)dlg.x, (int)dlg.y, (int)dlg.width, (int)dlg.height, WHITE);
    DrawRectangle((int)dlg.x, (int)dlg.y, (int)dlg.width, 6, red);
    DrawText("Delete product?", (int)dlg.x + 30, (int)dlg.y + 25, 28, navy);
    DrawText(TextFormat("%s (ID %d)", products[selectedRow].name, products[selectedRow].id),
             (int)dlg.x + 30, (int)dlg.y + 68, 20, DARKGRAY);
    DrawText("This cannot be undone.", (int)dlg.x + 30, (int)dlg.y + 95, 16, GRAY);

    Rectangle yesBtn = {dlg.x + 30,  dlg.y + 120, 170, 44};
    Rectangle noBtn  = {dlg.x + 220, dlg.y + 120, 170, 44};

    if (DrawButton(yesBtn, "Yes, delete", red, redHover))
    {
        SetStatus(TextFormat("Deleted: %s", products[selectedRow].name), STATUS_SUCCESS);
        DeleteProductAt(selectedRow);
        selectedRow = -1;
        confirmingDelete = false;
        SaveChanges();
    }
    else if (DrawButton(noBtn, "Cancel", navActive, navyHover) || IsKeyPressed(KEY_ESCAPE))
    {
        SetStatus("Delete cancelled.", STATUS_INFO);
        confirmingDelete = false;
    }
}

void DrawProductsScreen(void)
{
    bool locked = confirmingDelete;
    bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    Vector2 mouse = GetMousePosition();
    Rectangle panel = {CONTENT_X, CONTENT_Y, CONTENT_W, CONTENT_H};
    DrawPanel(panel, "Product Management");
    Rectangle boxes[BOX_COUNT] = {
        {CONTENT_X + 20,  CONTENT_Y + 82, 80,  36},   /* ID       */
        {CONTENT_X + 115, CONTENT_Y + 82, 260, 36},   /* Name     */
        {CONTENT_X + 390, CONTENT_Y + 82, 100, 36},   /* Price    */
        {CONTENT_X + 505, CONTENT_Y + 82, 80,  36},   /* Quantity */
        {CONTENT_X + 360, BAR_Y,          90,  36}    /* Units to add */
    };
    const char *labels[FORM_RESTOCK] = {"ID", "Name", "Price", "Quantity"};
    Rectangle addBtn = {CONTENT_X + 600, CONTENT_Y + 82, 100, 36};
    if (!locked && clicked)
    {
        focusedBox = -1;                         /* clicking elsewhere removes focus */
        for (int i = 0; i < BOX_COUNT; i++)
        {
            if (CheckCollisionPointRec(mouse, boxes[i]))
            {
                focusedBox = i;
            }
        }
    }
    if (!locked && IsKeyPressed(KEY_TAB))
    {
        focusedBox = (focusedBox + 1) % BOX_COUNT;
    }
    if (!locked && focusedBox >= 0)
    {
        UpdateTextField(&fields[focusedBox]);

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))
        {
            if (focusedBox == FORM_RESTOCK)
            {
                RestockSelected();
            }
            else
            {
                SubmitForm();
            }
        }
    }
    float wheel = GetMouseWheelMove();
    if (!locked && wheel > 0) scrollOffset--;
    if (!locked && wheel < 0) scrollOffset++;
    int maxScroll = productCount - MAX_VISIBLE_ROWS;
    if (maxScroll < 0) maxScroll = 0;
    if (scrollOffset > maxScroll) scrollOffset = maxScroll;
    if (scrollOffset < 0) scrollOffset = 0;
    for (int i = 0; i < FORM_RESTOCK; i++)
    {
        DrawText(labels[i], (int)boxes[i].x, (int)boxes[i].y - 20, 16, GRAY);
        DrawTextField(boxes[i], &fields[i], focusedBox == i);
    }
    if (DrawButton(addBtn, "Add", green, greenHover) && !locked)
    {
        SubmitForm();
    }
    int tableY = CONTENT_Y + 135;
    DrawRectangle(CONTENT_X + 20, tableY, CONTENT_W - 40, ROW_H, navy);
    DrawText("ID",     COL_ID,     tableY + 5, 18, WHITE);
    DrawText("Name",   COL_NAME,   tableY + 5, 18, WHITE);
    DrawText("Price",  COL_PRICE,  tableY + 5, 18, WHITE);
    DrawText("Qty",    COL_QTY,    tableY + 5, 18, WHITE);
    DrawText("Status", COL_STATUS, tableY + 5, 18, WHITE);

    if (productCount == 0)
    {
        DrawText("No products yet. Fill in the form above and click Add.",
                 CONTENT_X + 30, tableY + ROW_H + 20, 20, GRAY);
    }

    for (int row = 0; row < MAX_VISIBLE_ROWS && scrollOffset + row < productCount; row++)
    {
        int i = scrollOffset + row;
        int y = tableY + ROW_H * (row + 1);
        bool low = IsLowStock(products[i].quantity);
        Rectangle rowRect = {CONTENT_X + 20, y, CONTENT_W - 40, ROW_H};
        if (!locked && clicked && CheckCollisionPointRec(mouse, rowRect))
        {
            selectedRow = i;
        }

        if (i == selectedRow)
        {
            DrawRectangle(CONTENT_X + 20, y, CONTENT_W - 40, ROW_H, (Color){190, 215, 250, 255});
        }
        else if (row % 2 == 0)
        {
            DrawRectangle(CONTENT_X + 20, y, CONTENT_W - 40, ROW_H, lightBg);
        }

        DrawText(TextFormat("%d", products[i].id),       COL_ID,    y + 5, 18, DARKGRAY);
        DrawText(products[i].name,                       COL_NAME,  y + 5, 18, DARKGRAY);
        DrawText(TextFormat("%.2f", products[i].price),  COL_PRICE, y + 5, 18, DARKGRAY);
        DrawText(TextFormat("%d", products[i].quantity), COL_QTY,   y + 5, 18,
                 low ? red : DARKGRAY);

        if (low)
        {
            DrawText("LOW STOCK", COL_STATUS, y + 5, 18, red);
        }
        else
        {
            DrawText("OK", COL_STATUS, y + 5, 18, green);
        }
    }
    if (productCount > MAX_VISIBLE_ROWS)
    {
        int lastShown = scrollOffset + MAX_VISIBLE_ROWS;
        if (lastShown > productCount) lastShown = productCount;
        DrawText(TextFormat("Rows %d-%d of %d (mouse wheel scrolls)",
                            scrollOffset + 1, lastShown, productCount),
                 CONTENT_X + 30, tableY + ROW_H * (MAX_VISIBLE_ROWS + 1) + 4, 16, GRAY);
    }

    if (selectedRow >= 0 && selectedRow < productCount)
    {
        DrawText(products[selectedRow].name, CONTENT_X + 20, BAR_Y + 9, 18, navy);
    }
    else
    {
        DrawText("Click a row to select a product.", CONTENT_X + 20, BAR_Y + 9, 18, GRAY);
    }

    DrawText("Units to add", (int)boxes[FORM_RESTOCK].x, BAR_Y - 17, 14, GRAY);
    DrawTextField(boxes[FORM_RESTOCK], &fields[FORM_RESTOCK], focusedBox == FORM_RESTOCK);

    Rectangle stockBtn  = {CONTENT_X + 460, BAR_Y, 120, 36};
    Rectangle deleteBtn = {CONTENT_X + 595, BAR_Y, 105, 36};

    if (DrawButton(stockBtn, "Add stock", green, greenHover) && !locked)
    {
        RestockSelected();
    }
    if (DrawButton(deleteBtn, "Delete", red, redHover) && !locked)
    {
        if (selectedRow >= 0 && selectedRow < productCount)
        {
            confirmingDelete = true;
        }
        else
        {
            SetStatus("Click a product row first.", STATUS_ERROR);
        }
    }
    if (confirmingDelete)
    {
        DrawDeleteDialog();
    }
}
