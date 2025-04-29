#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

class Window {
public:
    bool Create(HINSTANCE hInstance, int width, int height, const wchar_t* title);
    void Show();
    HWND GetHandle() const;

private:
    HWND hWnd;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // WINDOW_H
