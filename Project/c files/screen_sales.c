#include "smartshop.h"
#include "product.h"
#include "billing.h"
#include "report.h"
#include <stdio.h>

#define ROW_H         26
#define HISTORY_ROWS  12
#define TABLE_Y       (CONTENT_Y + 110)
#define SCOL_NO        (CONTENT_X + 25)
#define SCOL_DATE      (CONTENT_X + 60)
#define SCOL_CUSTOMER  (CONTENT_X + 205)
#define SCOL_QTY       (CONTENT_X + 325)
#define SCOL_TOTAL     (CONTENT_X + 365)
#define SCOL_VIP       (CONTENT_X + 455)
#define SCOL_ITEMS     (CONTENT_X + 520)

static int  scrollOffset = 0;
static bool reportOpen = false;
static SalesReport report;
static char reportMessage[80] = "";
static bool reportMessageIsError = false;

static void DrawReportLine(int x, int y, const char *label, const char *value)
{
    DrawText(label, x + 30, y + 3, 18, GRAY);
    DrawText(value, x + 250, y, 22, navy);
}

static void DrawReportWindow(void)
{
    DrawRectangle(0, 0, SCREEN_W, SCREEN_H, (Color){0, 0, 0, 120});

    Rectangle dlg = {290, 110, 420, 430};
    int x = (int)dlg.x;
    int y = (int)dlg.y;
    DrawRectangle(x, y, (int)dlg.width, (int)dlg.height, WHITE);
    DrawRectangle(x, y, (int)dlg.width, 56, navy);
    DrawText("Sales Report", x + 30, y + 14, 26, WHITE);

    DrawReportLine(x, y + 78,  "Number of bills",    TextFormat("%d", report.billCount));
    DrawReportLine(x, y + 110, "Items sold",         TextFormat("%d", report.itemsSold));
    DrawReportLine(x, y + 142, "Total sales",        TextFormat("%.2f", report.totalSales));
    DrawReportLine(x, y + 174, "Average bill",       TextFormat("%.2f", report.averageBill));
    DrawReportLine(x, y + 206, "Highest bill",       TextFormat("%.2f", report.highestBill));
    DrawReportLine(x, y + 238, "VIP customers",      TextFormat("%d", report.vipCustomers));
    DrawReportLine(x, y + 270, "Low-stock products", TextFormat("%d", report.lowStockProducts));

    DrawText(TextFormat("Generated: %s", report.generated), x + 30, y + 312, 16, GRAY);

    Rectangle saveBtn  = {dlg.x + 30,  dlg.y + 345, 200, 44};
    Rectangle closeBtn = {dlg.x + 250, dlg.y + 345, 140, 44};

    if (DrawButton(saveBtn, "Save as report.txt", green, greenHover))
    {
        char path[260];
        snprintf(path, sizeof(path), "%s", DataFilePath("report.txt"));

        if (SaveSalesReport(path, &report))
        {
            snprintf(reportMessage, sizeof(reportMessage), "Saved as report.txt (next to SmartShop.exe)");
            reportMessageIsError = false;
        }
        else
        {
            snprintf(reportMessage, sizeof(reportMessage), "Could not save report.txt");
            reportMessageIsError = true;
        }
    }

    if (reportMessage[0] != '\0')
    {
        DrawText(reportMessage, x + 30, y + 400, 16, reportMessageIsError ? red : green);
    }

    if (DrawButton(closeBtn, "Close", navActive, navyHover) || IsKeyPressed(KEY_ESCAPE))
    {
        reportOpen = false;
    }
}

void DrawSalesScreen(void)
{
    bool locked = reportOpen;
    Vector2 mouse = GetMousePosition();

    Rectangle panel = {CONTENT_X, CONTENT_Y, CONTENT_W, CONTENT_H};
    DrawPanel(panel, "Sales Records");

    DrawText(TextFormat("%d bill(s) saved", saleCount), CONTENT_X + 20, CONTENT_Y + 72, 20, DARKGRAY);

    Rectangle reportBtn = {CONTENT_X + 520, CONTENT_Y + 62, 180, 40};
    if (DrawButton(reportBtn, "Generate Report", green, greenHover) && !locked)
    {
        report = BuildSalesReport();
        reportMessage[0] = '\0';
        reportOpen = true;
    }

    Rectangle tableRect = {CONTENT_X + 20, TABLE_Y, CONTENT_W - 40, ROW_H * (HISTORY_ROWS + 1)};
    float wheel = GetMouseWheelMove();
    if (!locked && CheckCollisionPointRec(mouse, tableRect))
    {
        if (wheel > 0) scrollOffset--;
        if (wheel < 0) scrollOffset++;
    }
    int maxScroll = saleCount - HISTORY_ROWS;
    if (maxScroll < 0) maxScroll = 0;
    if (scrollOffset > maxScroll) scrollOffset = maxScroll;
    if (scrollOffset < 0) scrollOffset = 0;

    DrawRectangle(CONTENT_X + 20, TABLE_Y, CONTENT_W - 40, ROW_H, navy);
    DrawText("No.",      SCOL_NO,       TABLE_Y + 5, 16, WHITE);
    DrawText("Date",     SCOL_DATE,     TABLE_Y + 5, 16, WHITE);
    DrawText("Customer", SCOL_CUSTOMER, TABLE_Y + 5, 16, WHITE);
    DrawText("Qty",      SCOL_QTY,      TABLE_Y + 5, 16, WHITE);
    DrawText("Total",    SCOL_TOTAL,    TABLE_Y + 5, 16, WHITE);
    DrawText("VIP",      SCOL_VIP,      TABLE_Y + 5, 16, WHITE);
    DrawText("Items",    SCOL_ITEMS,    TABLE_Y + 5, 16, WHITE);

    if (saleCount == 0)
    {
        DrawText("No sales yet. Complete a bill on the Billing screen.",
                 CONTENT_X + 30, TABLE_Y + ROW_H + 15, 18, GRAY);
    }

    for (int row = 0; row < HISTORY_ROWS && scrollOffset + row < saleCount; row++)
    {
        const Sale *s = &sales[saleCount - 1 - (scrollOffset + row)];
        int y = TABLE_Y + ROW_H * (row + 1);

        if (row % 2 == 0)
        {
            DrawRectangle(CONTENT_X + 20, y, CONTENT_W - 40, ROW_H, lightBg);
        }

        DrawText(TextFormat("%d", s->saleNumber), SCOL_NO, y + 5, 16, DARKGRAY);
        DrawText(s->date, SCOL_DATE, y + 5, 16, DARKGRAY);
        DrawTextClipped(s->customer, SCOL_CUSTOMER, y + 5, 16, 110, DARKGRAY);
        DrawText(TextFormat("%d", s->totalQuantity), SCOL_QTY, y + 5, 16, DARKGRAY);
        DrawText(TextFormat("%.2f", s->totalAmount), SCOL_TOTAL, y + 5, 16, DARKGRAY);

        if (s->vipNumber > 0)
        {
            DrawText(TextFormat("VIP-%03d", s->vipNumber), SCOL_VIP, y + 5, 16, green);
        }
        else
        {
            DrawText("-", SCOL_VIP, y + 5, 16, GRAY);
        }

        DrawTextClipped(s->itemsText, SCOL_ITEMS, y + 5, 16, 175, DARKGRAY);
    }

    if (saleCount > HISTORY_ROWS)
    {
        int lastShown = scrollOffset + HISTORY_ROWS;
        if (lastShown > saleCount) lastShown = saleCount;
        DrawText(TextFormat("Rows %d-%d of %d (mouse wheel scrolls, newest first)",
                            scrollOffset + 1, lastShown, saleCount),
                 CONTENT_X + 30, TABLE_Y + ROW_H * (HISTORY_ROWS + 1) + 6, 14, GRAY);
    }

    if (reportOpen)
    {
        DrawReportWindow();
    }
}

