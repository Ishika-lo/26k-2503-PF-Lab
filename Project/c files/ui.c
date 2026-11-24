#include "smartshop.h"
#include <stdio.h>
#include <string.h>

#if PALETTE == 2
Color navy       = {11, 60, 73, 255};
Color navyHover  = {30, 95, 110, 255};
Color navActive  = {0, 150, 136, 255};
Color lightBg    = {236, 246, 245, 255};
Color green      = {67, 160, 71, 255};
Color greenHover = {46, 125, 50, 255};
Color red        = {211, 47, 47, 255};
Color redHover   = {165, 30, 30, 255};
Color selectBg   = {178, 223, 219, 255};
#elif PALETTE == 3
Color navy       = {42, 27, 77, 255};
Color navyHover  = {74, 52, 128, 255};
Color navActive  = {124, 77, 255, 255};
Color lightBg    = {244, 241, 250, 255};
Color green      = {38, 166, 154, 255};
Color greenHover = {0, 121, 107, 255};
Color red        = {229, 57, 53, 255};
Color redHover   = {183, 28, 28, 255};
Color selectBg   = {215, 200, 250, 255};
#elif PALETTE == 4
Color navy       = {33, 37, 41, 255};
Color navyHover  = {73, 80, 87, 255};
Color navActive  = {245, 124, 0, 255};
Color lightBg    = {247, 246, 243, 255};
Color green      = {46, 160, 90, 255};
Color greenHover = {30, 122, 68, 255};
Color red        = {211, 47, 47, 255};
Color redHover   = {165, 30, 30, 255};
Color selectBg   = {255, 224, 178, 255};
#else
Color navy       = {15, 32, 68, 255};
Color navyHover  = {40, 70, 130, 255};
Color navActive  = {46, 98, 190, 255};
Color lightBg    = {240, 244, 250, 255};
Color green      = {46, 184, 108, 255};
Color greenHover = {34, 150, 90, 255};
Color red        = {210, 55, 55, 255};
Color redHover   = {165, 38, 38, 255};
Color selectBg   = {190, 215, 250, 255};
#endif

Font appFont;
static bool fontIsCustom = false;

void LoadAppFont(void)
{
    if (FileExists(DataFilePath(FONT_FILE)))
    {
        appFont = LoadFontEx(DataFilePath(FONT_FILE), 32, NULL, 0);
        if (appFont.texture.id != 0)
        {
            SetTextureFilter(appFont.texture, TEXTURE_FILTER_BILINEAR);
            fontIsCustom = true;
            return;
        }
    }
    appFont = GetFontDefault();
}

void UnloadAppFont(void)
{
    if (fontIsCustom)
    {
        UnloadFont(appFont);
        fontIsCustom = false;
    }
}

static const char *navLabels[NAV_COUNT] = {
    "Dashboard", "Products", "Billing", "Sales Records"
};
static char statusMessage[100] = "Welcome to SmartShop";
static StatusType statusType = STATUS_INFO;

void SetStatus(const char *message, StatusType type)
{
    snprintf(statusMessage, sizeof(statusMessage), "%s", message);
    statusType = type;
}

const char *DataFilePath(const char *fileName)
{
    return TextFormat("%s%s", GetApplicationDirectory(), fileName);
}

bool DrawButton(Rectangle bounds, const char *label, Color normal, Color hover)
{
    Vector2 mouse = GetMousePosition();
    bool isHover = CheckCollisionPointRec(mouse, bounds);

    DrawRectangleRounded(bounds, 0.2f, 8, isHover ? hover : normal);

    int fontSize = 20;
    int textWidth = MeasureText(label, fontSize);
    int textX = (int)(bounds.x + (bounds.width - textWidth) / 2);
    int textY = (int)(bounds.y + (bounds.height - fontSize) / 2);
    DrawText(label, textX, textY, fontSize, WHITE);

    return isHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void UpdateTextField(TextField *field)
{
    int key = GetCharPressed();
    while (key > 0)
    {
        bool allowed = false;

        if (field->mode == FIELD_TEXT)
        {
            allowed = (key >= 32 && key <= 126 && key != ',');
        }
        else if (field->mode == FIELD_INTEGER)
        {
            allowed = (key >= '0' && key <= '9');
        }
        else
        {
            allowed = (key >= '0' && key <= '9');
            if (key == '.' && strchr(field->text, '.') == NULL)
            {
                allowed = true;
            }
        }

        if (allowed && field->length < field->maxLength)
        {
            field->text[field->length] = (char)key;
            field->length++;
            field->text[field->length] = '\0';
        }

        key = GetCharPressed();
    }

    static int holdFrames = 0;
    bool erase = false;

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        erase = true;
        holdFrames = 0;
    }
    else if (IsKeyDown(KEY_BACKSPACE))
    {
        holdFrames++;
        if (holdFrames > 25 && holdFrames % 3 == 0)
        {
            erase = true;
        }
    }
    else
    {
        holdFrames = 0;
    }

    if (erase && field->length > 0)
    {
        field->length--;
        field->text[field->length] = '\0';
    }
}

void DrawTextField(Rectangle bounds, const TextField *field, bool focused)
{
    DrawRectangle((int)bounds.x, (int)bounds.y, (int)bounds.width, (int)bounds.height, WHITE);
    DrawRectangleLinesEx(bounds, 2, focused ? navActive : LIGHTGRAY);

    const char *shown = field->text;
    while (*shown != '\0' && MeasureText(shown, 18) > (int)bounds.width - 24)
    {
        shown++;
    }
    DrawText(shown, (int)bounds.x + 10, (int)bounds.y + 9, 18, navy);

    if (focused && ((int)(GetTime() * 2) % 2 == 0))
    {
        int cursorX = (int)bounds.x + 10 + MeasureText(shown, 18) + 2;
        DrawRectangle(cursorX, (int)bounds.y + 7, 2, 22, navy);
    }
}

void ClearTextField(TextField *field)
{
    field->text[0] = '\0';
    field->length = 0;
}

void DrawTextClipped(const char *text, int x, int y, int fontSize, int maxWidth, Color color)
{
    char buffer[96];
    snprintf(buffer, sizeof(buffer) - 4, "%s", text);

    if (MeasureText(buffer, fontSize) > maxWidth)
    {
        int dotsWidth = MeasureText("..", fontSize);
        int len = (int)strlen(buffer);

        while (len > 0 && MeasureText(buffer, fontSize) > maxWidth - dotsWidth)
        {
            len--;
            buffer[len] = '\0';
        }
        strcat(buffer, "..");
    }

    DrawText(buffer, x, y, fontSize, color);
}

void DrawStatCard(Rectangle card, const char *label, int value, Color accent)
{
    DrawRectangleRounded(card, 0.1f, 8, WHITE);
    DrawRectangle((int)card.x, (int)card.y + 10, 6, (int)card.height - 20, accent);
    DrawText(label, (int)card.x + 25, (int)card.y + 25, 20, GRAY);
    DrawText(TextFormat("%d", value), (int)card.x + 25, (int)card.y + 60, 50, navy);
}
void DrawPanel(Rectangle panel, const char *title)
{
    DrawRectangleRounded(panel, 0.03f, 8, WHITE);
    DrawText(title, (int)panel.x + 20, (int)panel.y + 15, 26, navy);
    DrawRectangle((int)panel.x + 20, (int)panel.y + 52, (int)panel.width - 40, 2, lightBg);
}

Screen DrawSidebar(Screen current)
{
    Screen result = current;

    DrawRectangle(0, 0, SIDEBAR_W, SCREEN_H, navy);
    DrawText("SmartShop", 20, 22, 32, WHITE);
    DrawText("Supermarket Manager", 20, 62, 16, LIGHTGRAY);

    for (int i = 0; i < NAV_COUNT; i++)
    {
        Rectangle r = {20, 110 + i * 60, 180, 50};
        Color normal = ((int)current == i) ? navActive : navy;

        if (DrawButton(r, navLabels[i], normal, navyHover))
        {
            result = (Screen)i;
            SetStatus(TextFormat("Opened: %s", navLabels[i]), STATUS_INFO);
        }
    }

    Rectangle exitBtn = {20, SCREEN_H - 80, 180, 50};
    if (DrawButton(exitBtn, "Exit", red, redHover))
    {
        result = SCREEN_EXIT;
    }

    return result;
}

void DrawHeader(Screen current)
{
    DrawRectangle(SIDEBAR_W, 0, SCREEN_W - SIDEBAR_W, HEADER_H, WHITE);
    if ((int)current >= 0 && (int)current < NAV_COUNT)
    {
        DrawText(navLabels[(int)current], SIDEBAR_W + 30, 18, 34, navy);
    }
}

void DrawStatusBar(void)
{
    Color textColor = DARKGRAY;
    if (statusType == STATUS_SUCCESS) textColor = green;
    if (statusType == STATUS_ERROR)   textColor = red;

    DrawRectangle(SIDEBAR_W, SCREEN_H - STATUS_H, SCREEN_W - SIDEBAR_W, STATUS_H, WHITE);
    DrawText(TextFormat("Status: %s", statusMessage),
             SIDEBAR_W + 20, SCREEN_H - 29, 18, textColor);


}
