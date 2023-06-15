#include <Windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <string.h>
#include <iostream>
#include <sstream>

#define IDB_Button1 1
#define IDB_Button2 2

LRESULT CALLBACK WndProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lCmdLine, _In_ int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("DesktopApp");
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	static TCHAR szWindowClass[] = _T("DesktopApp");
	static TCHAR szTitle[] = _T("Windows Desktop");

	HWND hwnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		NULL, 
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);

	// Первый способ создания элементов управления

	HWND hBtn1, hBtn2, hMsg;

	hBtn1 = CreateWindow(
		_T("button"),
		_T("Click me!"), 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
		300, 30, 90, 30, 
		hwnd, 
		(HMENU)IDB_Button1,
		hInstance, 
		NULL);
	ShowWindow(hBtn1, nCmdShow);
	hBtn2 = CreateWindow(
		_T("button"),
		_T("Click me!"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 70, 90, 30,
		hwnd,
		(HMENU)IDB_Button2,
		hInstance,
		NULL);
	ShowWindow(hBtn2, nCmdShow);
	hMsg = CreateWindow(
		_T("Edit"),
		NULL,
		WS_EX_CLIENTEDGE | WS_BORDER | WS_CHILD | WS_VISIBLE,
		300, 110, 90, 20,
		hwnd,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hMsg, nCmdShow);
	UpdateWindow(hwnd);
	MSG msg = {};
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	PAINTSTRUCT ps;
	POINT pt;
	HINSTANCE hInst;
	// HDC - десриптор, который используется для рисования в клиентской области окна
	HDC hdc;
	TCHAR text[] = _T("Hello, World");
	TCHAR StrA[20];

	int a, b, sum, Len;

	static HWND hBtn, hEdt1, hEdt2, hStat; //дексрипторы кнопки, полей редактирования и статического текста

	switch (uMsg)
	{
	case WM_CREATE:
	{
		// Второй способ создания элементов управления
		hInst = ((LPCREATESTRUCT)lParam)->hInstance; // Дексриптор приложения

		hEdt1 = CreateWindow(_T("edit"), _T("0"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 50, 50, 60, 20,
			hwnd, 0, hInst, NULL);
		ShowWindow(hEdt1, SW_SHOWNORMAL);

		hEdt2 = CreateWindow(_T("edit"), _T("0"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 150, 50, 60,
			20, hwnd, 0, hInst, NULL);
		ShowWindow(hEdt2, SW_SHOWNORMAL);
		// Создаем и показываем кнопку
		hBtn = CreateWindow(_T("button"), _T("Рассчитать"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			50, 100, 120, 30, hwnd, 0, hInst, NULL);
		ShowWindow(hBtn, SW_SHOWNORMAL);
		// Создаем и показываем поле текста для результата
		hStat = CreateWindow(_T("static"), _T("0"), WS_CHILD | WS_VISIBLE,
			150, 180, 120, 20, hwnd, 0, hInst, NULL);
		ShowWindow(hStat, SW_SHOWNORMAL);
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 300, 10, text, _tcsclen(text));
		TextOut(hdc, 50, 20, _T("Введите два числа"), 18); // вывод текстовых сообщений
		TextOut(hdc, 50, 180, _T("Результат:"), 10);
		EndPaint(hwnd, &ps);
		return 0;
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
		break;
	}
	case WM_LBUTTONDOWN:
	{
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		std::wstring xPos = (LPCWSTR)std::to_wstring(pt.x).c_str();
		std::wstring yPos = (LPCWSTR)std::to_wstring(pt.y).c_str();
		std::wstring coord = _T("X = ") + xPos + _T("; Y = ") + yPos;

		MessageBox(hwnd, (LPCWSTR)coord.c_str(), _T("HELLO"), MB_OK);
		return 0;
		break;
	}
	case WM_COMMAND:
	{
		if (wParam == IDB_Button1)
		{
			MessageBoxW(hwnd, _T("Button 1"), _T("Btn Message"), MB_OK);
		} 
		else if (wParam == IDB_Button2)
		{
			MessageBoxW(hwnd, _T("Button 2"), _T("Btn Message"), MB_OK);
		}
		else if (lParam == (LPARAM)hBtn)
		{
			Len = GetWindowText(hEdt1, StrA, 20);
			a = _tstoi(StrA); // считываем число из первого поля
			Len = GetWindowText(hEdt2, StrA, 20);
			b = _tstoi(StrA); // считываем число из второго поля
			sum = a + b;  // находим сумму двух чисел

			SetWindowText(hStat, (LPCWSTR)std::to_wstring(sum).c_str()); // выводим результат в статическое поле
			//sMessageBoxW(hwnd, _T("Button 3"), _T("Btn Message"), MB_OK);
		}
	}
	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		break;
	}
}