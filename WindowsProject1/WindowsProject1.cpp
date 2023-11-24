#include <Windows.h>
#include "resource.h"

// Глобальні змінні:
HINSTANCE hInst; // Дескриптор програми
LPCTSTR studentName = TEXT("Prylutska,Rozumenko,Sidelnikov"); // Ім'я класу вікна
LPCTSTR szTitle = L"B-4"; // Заголовок вікна

// Попередній опис функцій
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Основна програма
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    // Реєстрація класу вікна
    MyRegisterClass(hInstance);

    // Створення вікна програми
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Цикл обробки повідомлень
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_VREDRAW | CS_DBLCLKS; // Стиль вікна
    wcex.lpfnWndProc = (WNDPROC)WndProc; // Віконна процедура
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance; // Дескриптор програми
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); // Іконка
    wcex.hCursor = LoadCursor(NULL, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)(COLOR_GRAYTEXT + 1); // Фон вікна (темно-сірий)
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // Меню
    wcex.lpszClassName = studentName; // Ім'я класу
    wcex.hIconSm = NULL;

    return RegisterClassEx(&wcex); // Реєстрація класу вікна
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    hInst = hInstance;

    // Створення вікна програми
    hWnd = CreateWindow(studentName, // Ім'я класу вікна
        szTitle, // Назва програми
        WS_CAPTION | WS_MINIMIZEBOX | WS_HSCROLL | WS_VSCROLL| WS_SYSMENU, // Стиль вікна
        50, // Позиція по X
        90, // Позиція по Y
        400, // Ширина
        500, // Висота
        NULL, // Дескриптор батьківського вікна
        NULL, // Дескриптор меню вікна
        hInstance, // Дескриптор програми
        NULL); // Параметри створення

    if (!hWnd) // Якщо вікно не створилось, функція повертає FALSE
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow); // Показати вікно
    UpdateWindow(hWnd); // Оновити вікно

    return TRUE;
}

// Функція обробки діалогового вікна "Про програму"
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetDlgItemText(hDlg, IDC_PROGRAM_INFO, L"Виконали: Прилуцька Розуменко Сідєльніков");
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        case IDCANCEL:
        case ID_CLOSE:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;

        case ID_DETAILS:
            MessageBox(hDlg, L"Лабораторна робота 1. Виконала бригада нимер 4: Прилуцька Марія, Розуменко Олексій, Сідєльніков Денис", L"Докладніше", MB_OK);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDBLCLK:
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        RECT rc;
        GetClientRect(hWnd, &rc);
        if (PtInRect(&rc, pt))
        {
            MessageBox(hWnd, L"Подвійне натискання миші в межах вікна", L"Повідомлення", MB_OK);
        }
    }
    break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case ID_CHANGE_BGCOLOR:
        {
            HBRUSH hBrush = CreateSolidBrush(RGB(50, 100, 100));
            SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

        case ID_CHANGE_SIZE:
            SetWindowPos(hWnd, HWND_TOP, 50, 90, 600, 700, SWP_SHOWWINDOW);
            break;

        case ID_CHANGE_CURSOR:
        {
            HCURSOR newCur = LoadCursorFromFile(L"arrow.cur");
            if (newCur) {
                SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)newCur);
            }
        }
        break;

        case ID_CHANGE_ICON:
        {
            HICON newIcon = LoadCursorFromFile(L"warning.ico");
            if (newIcon) {
                SetClassLongPtr(hWnd, GCLP_HICON, (LONG_PTR)newIcon);
            }
        }
        break;
        }
        break;

    case WM_CLOSE:
    {
        int result = MessageBox(hWnd, L"Ви впевнені?", L"Підтвердження", MB_YESNO | MB_ICONQUESTION);

        if (result == IDYES)
        {
            DestroyWindow(hWnd);
        }

        return 0;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
