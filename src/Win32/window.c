// Platform headers
#include <windows.h>
// Project headers
#include <FLIB/window.h>
#include <FLIB/events.h>

WindowSpec DEFAULT_WINDOW_SPEC;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void window_spec_init(WindowSpec *restrict spec) {
    *spec = DEFAULT_WINDOW_SPEC;
}

void window_create(WindowSpec spec) {
    char className[] = "Sample Window Class";
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSEXA winClass = { 0 };

    winClass.lpszClassName = className;
    winClass.lpfnWndProc = WindowProc;
    winClass.hInstance = hInstance;
    winClass.cbSize = sizeof(winClass);

    RegisterClassExA(&winClass);


    HWND newHwnd = CreateWindowExA(
        0,
        className,
        "Learn to program windows!",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if(newHwnd == NULL) return;
    ShowWindow(newHwnd, SW_SHOW);

    MSG msg = { 0 };

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}