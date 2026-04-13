#include <iostream>
#include <Windows.h>

using namespace std;

LRESULT CALLBACK WindowProcedure(HWND window, UINT uMessage, WPARAM wParameter, LPARAM lParameter) {
    if (uMessage == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(window, uMessage, wParameter, lParameter);
}

int main() {
    // create class
    WNDCLASS windowClass = {};
    windowClass.lpfnWndProc = WindowProcedure;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.lpszClassName = L"MyClass";
    RegisterClass(&windowClass);

    HWND window = CreateWindowW(L"MyClass", L"MyIDE", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 500, 500, 800, 600, NULL, NULL, NULL, NULL);
    HWND hEdit = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | WS_BORDER, 50, 25, 700, 500, window, NULL, NULL, NULL);
    ShowWindow(window, 1);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}