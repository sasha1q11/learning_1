#include <windows.h>
#include "checker.h"   // подключаем второй файл

// Идентификаторы элементов управления
#define ID_INPUT        101
#define ID_BUTTON       102
#define ID_RESULT       103
#define ID_LABEL        104

// Глобальные дескрипторы (нужны в оконной процедуре)
HWND hInput, hButton, hResult;

// Оконная процедура — обрабатывает сообщения Windows
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {

	case WM_CREATE: {
		// Подпись
		CreateWindowW(L"STATIC", L"Введите целое число:",
			WS_CHILD | WS_VISIBLE,
			20, 20, 300, 20, hwnd, (HMENU)ID_LABEL, nullptr, nullptr);

		// Поле ввода
		hInput = CreateWindowW(L"EDIT", L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
			20, 45, 300, 25, hwnd, (HMENU)ID_INPUT, nullptr, nullptr);

		// Кнопка
		hButton = CreateWindowW(L"BUTTON", L"Проверить",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 85, 300, 30, hwnd, (HMENU)ID_BUTTON, nullptr, nullptr);

		// Метка результата
		hResult = CreateWindowW(L"STATIC", L"",
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			20, 130, 300, 25, hwnd, (HMENU)ID_RESULT, nullptr, nullptr);
		break;
	}

	case WM_COMMAND:
		// Нажата кнопка «Проверить»
		if (LOWORD(wParam) == ID_BUTTON) {
			wchar_t buffer[32] = { 0 };
			GetWindowTextW(hInput, buffer, 32);

			if (buffer[0] == L'\0') {
				MessageBoxW(hwnd, L"Введите число!", L"Внимание", MB_ICONWARNING);
				break;
			}

			int number = _wtoi(buffer);
			if (number == 0 && buffer[0] != L'0') {
				MessageBoxW(hwnd, L"Введите целое число!", L"Ошибка", MB_ICONERROR);
				break;
			}

			// Передаём число во второй файл и получаем результат
			std::wstring resultText = checkEven(number);
			SetWindowTextW(hResult, resultText.c_str());
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
	return 0;
}

// Точка входа
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	const wchar_t CLASS_NAME[] = L"EvenCheckerClass";

	WNDCLASSW wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowW(CLASS_NAME, L"Проверка чётности числа",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		360, 220,
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg = {};
	while (GetMessageW(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}