#ifndef SMARTSHOP_H
#define SMARTSHOP_H

#include "raylib.h"
#include <stdbool.h>

#define PALETTE    2
#define FONT_FILE  "font.ttf"
#define SCREEN_W   1000
#define SCREEN_H   650
#define SIDEBAR_W  220
#define HEADER_H   70
#define STATUS_H   40
#define CONTENT_X  (SIDEBAR_W + 30)
#define CONTENT_Y  (HEADER_H + 30)
#define CONTENT_W  (SCREEN_W - SIDEBAR_W - 60)
#define CONTENT_H  (SCREEN_H - HEADER_H - STATUS_H - 60)

typedef enum {
    SCREEN_DASHBOARD,
    SCREEN_PRODUCTS,
    SCREEN_BILLING,
    SCREEN_SALES,
    SCREEN_EXIT
} Screen;

#define NAV_COUNT 4

typedef enum {
    STATUS_INFO,
    STATUS_SUCCESS,
    STATUS_ERROR
} StatusType;

typedef enum {
    FIELD_TEXT,
    FIELD_INTEGER,
    FIELD_DECIMAL
} FieldMode;

typedef struct {
    char text[32];
    int  length;
    int  maxLength;
    FieldMode mode;
} TextField;

extern Color navy;
extern Color navyHover;
extern Color navActive;
extern Color lightBg;
extern Color green;
extern Color greenHover;
extern Color red;
extern Color redHover;
extern Color selectBg;

extern Font appFont;
void LoadAppFont(void);
void UnloadAppFont(void);
#define DrawText(text, x, y, size, color) \
    DrawTextEx(appFont, (text), (Vector2){(float)(x), (float)(y)}, (float)(size), (float)(size) / 16.0f, (color))
#define MeasureText(text, size) \
    ((int)MeasureTextEx(appFont, (text), (float)(size), (float)(size) / 16.0f).x)

bool DrawButton(Rectangle bounds, const char *label, Color normal, Color hover);
void DrawStatCard(Rectangle card, const char *label, int value, Color accent);
void DrawPanel(Rectangle panel, const char *title);
Screen DrawSidebar(Screen current);
void DrawHeader(Screen current);
void DrawStatusBar(void);
void SetStatus(const char *message, StatusType type);

void UpdateTextField(TextField *field);
void DrawTextField(Rectangle bounds, const TextField *field, bool focused);
void ClearTextField(TextField *field);

void DrawTextClipped(const char *text, int x, int y, int fontSize, int maxWidth, Color color);

const char *DataFilePath(const char *fileName);

void DrawDashboardScreen(int totalProducts, int lowStockItems);
bool DrawLowStockPopup(void);
void DrawProductsScreen(void);
void DrawBillingScreen(void);
void DrawSalesScreen(void);

#endif
