#ifndef BUTTON_H
#define BUTTON_H

#include <windows.h>

class Button {
public:
    Button(int x, int y, int diameter);
    void Draw(HDC hdc);
    bool IsClicked(int mouseX, int mouseY);
    void SetVisible(bool visible); // Uus meetod n‰htavuse seadmiseks

private:
    int x; // Nupu x-koordinaat
    int y; // Nupu y-koordinaat
    int diameter; // Nupu diameeter
    bool isVisible; // Muutuja, mis m‰‰rab, kas nupp on n‰htav
};

#endif // BUTTON_H