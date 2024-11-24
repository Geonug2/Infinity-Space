#include <windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include <stdexcept>
#include <gdiplus.h>

#include "VertexShader.h"

using Microsoft::WRL::ComPtr;
using namespace Gdiplus;

ULONG_PTR gdiplusToken = 0; // GDI+ token
const int TIMER_ID = 1; // Timer ID
const int DISPLAY_TIME = 10000; // 10 seconds in milliseconds
const int SWITCH_TIME = 5000; // 5 seconds in milliseconds

enum class ImageState {
    Main,
    Main2
};

ImageState currentImage = ImageState::Main; // Algne pilt

ID3D12Device* device = nullptr;

// GDI+ algatamine
void InitGDIPlus() {
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

// GDI+ lõpetamine
void ShutdownGDIPlus() {
    GdiplusShutdown(gdiplusToken);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Joonistame pildi
        Graphics graphics(hdc);
        Image image(currentImage == ImageState::Main ? L"Main.jpg" : L"Main2.jpg");

        // Joonistame pildi akna suuruses
        graphics.DrawImage(&image, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom);

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER: {
        // Vahetame pilti
        if (currentImage == ImageState::Main) {
            currentImage = ImageState::Main2;
            SetTimer(hwnd, TIMER_ID, DISPLAY_TIME, NULL); // Seadke timer 10 sekundiks
        }
        else {
            currentImage = ImageState::Main;
            SetTimer(hwnd, TIMER_ID, SWITCH_TIME, NULL); // Seadke timer 5 sekundiks
        }
        InvalidateRect(hwnd, NULL, TRUE); // Taaskäivitage aken
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void InitD3D(HWND hwnd) {
    // D3D12 algatamine (see osa jääb samaks)

    // Looge VertexShader
    VertexShader vertexShader(device);
    // Nüüd saate kasutada vertexShader objekti, et saada shader blob ja seadistada see pipeline'i
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Looge aken
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"DirectX 12 Sample", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1366, 768,
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr) {
        throw std::runtime_error("Failed to create window");
    }

    ShowWindow(hwnd, nCmdShow);

    // Algatage GDI+
    InitGDIPlus();

    // Algatage DirectX
    InitD3D(hwnd);

    // Seadke timer esmakordselt 5 sekundiks
    SetTimer(hwnd, TIMER_ID, SWITCH_TIME, NULL);

    // Pe amine tsükkel
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Lõpetage GDI+
    ShutdownGDIPlus();

    return 0;
}