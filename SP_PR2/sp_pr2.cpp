#include <Windows.h>
#include <tchar.h>
// Указатель на строку с именем класса окна.
#define g_lpszClassName TEXT ("sp_pr2_class")
// Указатаель на строку отображаемую в заголовке окна.
#define g_lpszAplicationTitle TEXT (" Главное окно приложения.")
// Указатель на строку. Этот текст будет использоваться при выводе сообщения о закрытии окна.
#define g_lpszDestroyMessage TEXT ("Поступило сообщение WM_DESTROY, из обработчика которого и выполнен данный вывод. Сообщение поступило в связи с разрушением окна приложения")
#define ID_BUTTON 1
// Указатель на строку используемую при ошибке регистрации класса окна.
#define g_lpszErrorRegister TEXT ("Ошибка регистрации класса окна!")
// Указатель на строку отображаемую в заголовке окна MessageBox при ошибке регистрации окна.
#define g_lpszErrorTitle TEXT ("Ошибка!!!!!!!!!!") 


LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM); // Прототип оконной процедуры для обработки сообщений главного окна

int APIENTRY _tWinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPTSTR IpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;


	//Описание класса окна
	HBRUSH hbr = CreateSolidBrush(RGB(0, 255, 0));
	memset(&wc, 0, sizeof(WNDCLASSEX));
	//Заполненин структуры wc
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = Pr2_WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = h_instance;
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = hbr;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//Завершено описание класса окна

	//Регистрация класса окна
	if (!RegisterClassEx(&wc))
	{
		//Ошибка регистрации класса окна
		MessageBox(NULL, g_lpszErrorRegister, g_lpszErrorTitle, MB_OK | MB_ICONERROR);
		return FALSE;
	}

	HWND hWnd;
	//Создание и отображение окна
	hWnd = CreateWindowEx(
		NULL,
		g_lpszClassName,
		g_lpszAplicationTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX,
		100,
		100,
		800, // ширина 
		600, // высота
		NULL,
		NULL,
		h_instance, // дескриптор экземпляра приложения
		NULL);

	//Если ошибка при создании окна
	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); //Отображение окна
	UpdateWindow(hWnd);

	// Главный цикл выборки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam; // выход из WinMai
}

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND h_Edit;
	static const UINT IDC_EDIT1 = 150;
	static HWND h_ListBox;
	static const UINT IDC_LISTBOX = 151;
	static HWND h_ButtonSave;
	static const UINT IDC_BUTTON_SAVE = 152;
	static HWND h_ButtonAdd;
	static const UINT IDC_BUTTON_ADD = 153;
	static HWND h_ButtonExit;
	static const UINT IDC_BUTTON_EXIT = 154;
	switch (msg)
	{
		

	case WM_CREATE:
	{
		{
			TCHAR text_mes[] = TEXT("Выполняется обработка WM_CREATE. \n Если вы хотите завершите обработку сообщения WM_CREATE возвратом значения 0, то нажмите YES. \n Если вы хотите завершите обработку сообщения WM_CREATE возвратом значения -1, то нажмите NO.");
			TCHAR text_title[] = TEXT("CREATE");
			if (MessageBox(NULL, text_mes, text_title, MB_YESNO) == IDNO)
			{
				return -1;
			}
		}

		h_Edit = CreateWindowEx(
			0,
			TEXT("Edit"),
			TEXT(""),
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			20,
			50,
			160,
			40,
			hWnd,
			(HMENU)(IDC_EDIT1),
			0,
			NULL);
		if (!h_Edit)
		{
			return (-1);
		}


		h_ListBox = CreateWindowEx(
			0,
			TEXT("ListBox"),
			TEXT("Список"),
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			200,
			50,
			160,
			180,
			hWnd,
			(HMENU)(IDC_LISTBOX),
			0,
			NULL);
		if (!h_ListBox)
		{
			return (-1);
		}

		h_ButtonSave = CreateWindowEx(
			0,
			TEXT("Button"),
			TEXT("В буфер"),
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			20,
			240,
			80,
			24,
			hWnd,
			(HMENU)(IDC_BUTTON_SAVE),
			0,
			NULL);
		if (!h_ButtonSave)
		{
			return (-1);
		}


		h_ButtonAdd = CreateWindowEx(
			0,
			TEXT("Button"),
			TEXT("В список"),
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			120,
			240,
			80,
			24,
			hWnd,
			(HMENU)(IDC_BUTTON_ADD),
			0,
			NULL);
		if (!h_ButtonAdd)
		{
			return (-1);
		}

		h_ButtonExit = CreateWindowEx(
			0,
			TEXT("Button"),
			TEXT("Выход"),
			WS_CHILD | WS_BORDER | WS_VISIBLE,
			220,
			240,
			80,
			24,
			hWnd,
			(HMENU)(IDC_BUTTON_EXIT),
			0,
			NULL);
		if (!h_ButtonExit)
		{
			return (-1);
		}
	}
	return 0;
	break;

	case WM_COMMAND:
	{
		int wmID;
		int wmEvent;
		wmID = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		static TCHAR pszText_Buffer[500];

		switch (wmID)
		{
		case IDC_BUTTON_EXIT:
		{
			SendMessage(hWnd, WM_DESTROY, 0, 0);

		}
		break;

		case IDC_BUTTON_SAVE:
		{
			int cch;
			cch = SendMessage(h_Edit, WM_GETTEXT, (WPARAM)500, (LPARAM)pszText_Buffer);
			if (cch == 0)
			{
				MessageBox(hWnd, TEXT("Введите текст"), TEXT("Читаем Edit"), MB_OK);
			}
			else
			{
				TCHAR Buffer1[500] = { 0 };
				SYSTEMTIME st;
				GetSystemTime(&st);
				wsprintf(Buffer1, TEXT("Время : %d ч %d мин %d сек\n"), st.wHour, st.wMinute, st.wSecond);
				lstrcat(Buffer1, TEXT("Текст в памяти: "));
				lstrcat(Buffer1, pszText_Buffer);
				MessageBox(hWnd, Buffer1, TEXT("Содержимое буфера"), MB_OK);
			}
		}
		break;

		case IDC_BUTTON_ADD:
		{
			int ind;
			ind = SendMessage(h_ListBox, LB_ADDSTRING, (WPARAM)0, (LPARAM)pszText_Buffer);
			if (ind == LB_ERR)
			{
				MessageBox(hWnd, TEXT("Ошибка в списке"), TEXT(""), MB_OK);
			}
			//EnableWindow(h_ButtonAdd, FALSE);
		}
		break;// end IDC_BUTTON_ADD
		}

	}
	break;

	case WM_DESTROY:
	{
		MessageBox(NULL, g_lpszDestroyMessage, g_lpszAplicationTitle, MB_OK | MB_ICONERROR);
		PostQuitMessage(5);
	}
	break;

	default: return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return FALSE;
}
