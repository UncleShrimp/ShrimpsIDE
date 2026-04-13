#include <iostream>
#include <tchar.h>
#include <string>
#include <Windows.h>

using namespace std;

enum ButtonCodes
{
RUN_CODE = 101,
SAVE_CODE = 102,
OPEN_CODE = 103
};


HWND codeText;
HWND saveText;

LRESULT CALLBACK WindowProcedure(HWND window, UINT uMessage, WPARAM wParameter, LPARAM lParameter) {
    if (uMessage == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    // Get the length of the text (in characters)
    int lengthOfCode = GetWindowTextLength(codeText);

    switch (uMessage) {
        case WM_COMMAND: {
            int wmId = LOWORD(wParameter);
            int wmEvent = HIWORD(wParameter);

            if (wmEvent == BN_CLICKED) {
                switch (wmId) {
                case RUN_CODE:
                    cout << "RUN!\n";
                    break;
                case SAVE_CODE:
                    cout << "SAVE\n";

                    if (lengthOfCode > 0) {
                        // Allocate buffer (add 1 for the null terminator)
                        TCHAR* buffer = new TCHAR[lengthOfCode + 1];

                        // Retrieve the text
                        GetWindowText(codeText, buffer, lengthOfCode + 1);

                        // debug print
                        _tprintf(_T("%s\n"), buffer);

                        // Free the memory
                        delete[] buffer;
                    }

                    break;
                case OPEN_CODE:
                    cout << "OPEN\n";
                    break;
                }
            }
            break;
        }
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

    // main window
    HWND window = CreateWindowW(L"MyClass", L"MyIDE", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 500, 500, 800, 600, NULL, NULL, NULL, NULL);
    
    // buttons
    HWND hwndRunButton = CreateWindow( L"BUTTON", L"Run Code", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 50, 10, 100, 30, window,
        (HMENU)RUN_CODE,
        (HINSTANCE)GetWindowLongPtr(window, GWLP_HINSTANCE),
        NULL        
    );
    HWND hwndSaveButton = CreateWindow(L"BUTTON", L"Save Code", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 175, 10, 100, 30, window,
        (HMENU)SAVE_CODE,
        (HINSTANCE)GetWindowLongPtr(window, GWLP_HINSTANCE),
        NULL
    );
    HWND hwndOpenButton = CreateWindow(L"BUTTON", L"Open Code", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 300, 10, 100, 30, window,
        (HMENU)OPEN_CODE, 
        (HINSTANCE)GetWindowLongPtr(window, GWLP_HINSTANCE),
        NULL
    );

    // text inputs
    HWND hSavePath = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_AUTOVSCROLL | WS_BORDER, 50, 45, 700, 25, window, NULL, NULL, NULL);
    HWND hEdit = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | WS_BORDER, 50, 75, 700, 475, window, NULL, NULL, NULL);
    
    codeText = hEdit;

    // shwo window
    ShowWindow(window, 1);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
