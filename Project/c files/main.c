#include "smartshop.h"
#include "product.h"
#include "billing.h"

int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H, "SmartShop - Supermarket Management System");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    LoadAppFont();

    int loaded = LoadProducts(DataFilePath("products.txt"));
    if (loaded > 0)
    {
        SetStatus(TextFormat("Loaded %d product(s) from products.txt.", loaded), STATUS_INFO);
    }

    LoadSales(DataFilePath("sales.txt"));

    bool showLowStockPopup = (CountLowStock() > 0);

    Screen currentScreen = SCREEN_DASHBOARD;
    bool shouldExit = false;

    while (!WindowShouldClose() && !shouldExit)
    {
        int totalProducts = productCount;
        int lowStockItems = CountLowStock();

        BeginDrawing();
            ClearBackground(lightBg);

            Screen picked = DrawSidebar(currentScreen);
            if (!showLowStockPopup)
            {
                if (picked == SCREEN_EXIT)
                {
                    shouldExit = true;
                }
                else
                {
                    currentScreen = picked;
                }
            }

            DrawHeader(currentScreen);

            switch (currentScreen)
            {
                case SCREEN_DASHBOARD: DrawDashboardScreen(totalProducts, lowStockItems); break;
                case SCREEN_PRODUCTS:  DrawProductsScreen(); break;
                case SCREEN_BILLING:   DrawBillingScreen();  break;
                case SCREEN_SALES:     DrawSalesScreen();    break;
                default: break;
            }

            DrawStatusBar();

            if (showLowStockPopup && DrawLowStockPopup())
            {
                showLowStockPopup = false;
            }
        EndDrawing();
    }

    UnloadAppFont();
    CloseWindow();
    return 0;
}

