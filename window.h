#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <d3d11.h>
#include "PixelShader.h"

class Window {
public:
    Window();
    ~Window();

    bool Create(HINSTANCE hInstance, int width, int height, const wchar_t* title);
    void Show();
    HWND GetHandle() const;
    bool Initialize(HINSTANCE hInstance, int nCmdShow);
    void Render();
private:
    HWND hWnd;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_hWnd;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    // Teised liikmed, nagu swap chain, render target view jne.

    PixelShader* m_pixelShader;
};

#endif // WINDOW_H
