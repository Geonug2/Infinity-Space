#include "window.h"

bool Window::Create(HINSTANCE hInstance, int width, int height, const wchar_t* title) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SimpleWindowClass";

    RegisterClass(&wc);

    hWnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL, NULL, hInstance, NULL
    );

    return hWnd != NULL;
}

void Window::Show() {
    ShowWindow(hWnd, SW_SHOW);
}

HWND Window::GetHandle() const {
    return hWnd;
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
