#include "smartshop.h"
#include "product.h"
#include "billing.h"
static void DrawStatCardText(Rectangle card, const char *label, const char *value, Color accent)
{
    DrawRectangleRounded(card, 0.1f, 8, WHITE);
    DrawRectangle((int)card.x, (int)card.y + 10, 6, (int)card.height - 20, accent);
    DrawText(label, (int)card.x + 25, (int)card.y + 25, 20, GRAY);
    DrawText(value, (int)card.x + 25, (int)card.y + 60, 50, navy);
}
void DrawDashboardScreen(int totalProducts, int lowStockItems)
{
    double totalSales = 0;
    for (int i = 0; i <saleCount; i++)
    {
        totalSales += sales[i].totalAmount;
    }
    Rectangle card1 = {CONTENT_X,       CONTENT_Y,       340, 130};
    Rectangle card2 = {CONTENT_X + 380, CONTENT_Y,       340, 130};
    Rectangle card3 = {CONTENT_X,       CONTENT_Y + 150, 340, 130};
    Rectangle card4 = {CONTENT_X + 380, CONTENT_Y + 150, 340, 130};

    DrawStatCard(card1, "Total Products", totalProducts, green);
    DrawStatCard(card2, "Low-Stock Items", lowStockItems,
                 lowStockItems > 0 ? red : green);
    DrawStatCard(card3, "Bills Made", saleCount, green);
    DrawStatCardText(card4, "Total Sales", TextFormat("%.2f", totalSales), green);

    Rectangle panel = {CONTENT_X, CONTENT_Y + 300, CONTENT_W, 180};
    DrawPanel(panel, "Welcome to SmartShop");
    DrawText("Use the menu on the left to open a section.",
             CONTENT_X + 20, CONTENT_Y + 300 + 75, 20, GRAY);
    DrawText("Products and sales are saved automatically.",
             CONTENT_X + 20, CONTENT_Y + 300 + 105, 20, GRAY);
}
bool DrawLowStockPopup(void)
{
    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0, 0, 0, 150});

    DrawRectangle(250, 120, 500, 410, WHITE);
    DrawRectangle(250, 120, 500, 64, red);
    DrawText("Low Stock Alert", 275, 138, 30, WHITE);

    int lowCount = CountLowStock();
    DrawText(TextFormat("%d product(s) with %d or fewer left:", lowCount, LOW_STOCK_LIMIT),
             275, 200, 18, DARKGRAY);
    int shown = 0;
    for (int i = 0; i < productCount && shown < 8; i++)
    {
        if (!IsLowStock(products[i].quantity))
        {
            continue;
        }

        int y = 232 + shown * 28;
        DrawText(products[i].name, 275, y, 18, navy);
        if (products[i].quantity == 0)
        {
            DrawText("OUT OF STOCK", 560, y, 18, red);
        }
        else
        {
            DrawText(TextFormat("%d left", products[i].quantity), 560, y, 18, red);
        }
        shown++;
    }

    if (lowCount > shown)
    {
        DrawText(TextFormat("...and %d more", lowCount - shown), 275, 458, 16, GRAY);
    }

    Rectangle okBtn = {400, 480, 200, 44};
    return DrawButton(okBtn, "OK", green, greenHover);
}
