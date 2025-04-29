#include "window.h"

Window::Window()
    : m_device(nullptr)
    , m_deviceContext(nullptr)
    , m_pixelShader(nullptr)
{
    // Konstruktoris initsialiseerid vajadusel muutujaid
}

Window::~Window() {
    if (m_pixelShader) {
        delete m_pixelShader;
    }
    // Vabastada ka teised DirectX ressursid
}

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

bool Window::Initialize(HINSTANCE hInstance, int nCmdShow) {
    // Peale seadme loomist initsialiseeri pixel shader.
    m_pixelShader = new PixelShader();
    // Vajadusel muuda siia failitee vastavalt projekti struktuurile (nt L"shaders\\sPixelShader.hlsl")
    if (!m_pixelShader->Initialize(m_device, L"PixelShader.hlsl")) {
        // Võid siin lisada täpsemat vea haldust
        return false;
    }
    return true;
}

void Window::Show() {
    ShowWindow(hWnd, SW_SHOW);
}

HWND Window::GetHandle() const {
    return hWnd;
}

void Window::Render() {
    // Tühjenda renderdusala, seadista pipeline jne.

    // Seome pixel shaderi enne joonistamist.
    m_pixelShader->Bind(m_deviceContext);

    // Tegelike joonistuskäskude tegemine
    // ...

    // Esita joonistustulemused.
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
