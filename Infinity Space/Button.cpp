#include "Button.h"
#include <windows.h>

Button::Button(int x, int y, int diameter)
    : x(x), y(y), diameter(diameter), isVisible(true) {
} // Alguses on nupp nähtav

void Button::Draw(HDC hdc) {
    if (isVisible) { // Joonista nupp ainult, kui see on nähtav
        HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255)); // Sinine värv
        SelectObject(hdc, brush);
        Ellipse(hdc, x - diameter / 2, y - diameter / 2, x + diameter / 2, y + diameter / 2);
        DeleteObject(brush);
    }
}

bool Button::IsClicked(int mouseX, int mouseY) {
    int radius = diameter / 2;
    return (mouseX >= x - radius && mouseX <= x + radius && mouseY >= y - radius && mouseY <= y + radius);
}

void Button::SetVisible(bool visible) {
    isVisible = visible; // Muuda nähtavuse olekut
}