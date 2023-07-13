#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

LPCTSTR lpszClass = TEXT("SpPr12_Class");
LPCTSTR lpszAppTitle = TEXT("Главное окно приложения. Програмист Грицкевич");
LPCTSTR lpszDestroyMessage = TEXT("Поступило сообщение WM_DESTROY, из обработчика "
	"которого и выполнен данный вывод.Сообщение "
	"поступило в связи с разрушением окна приложения");
//-- Prototypes -------------------
LRESULT CALLBACK pr1_WndProc(HWND hWnd, UINT Msg_id, WPARAM wParam, LPARAM lParam) {
	static HWND hEdit;
	const unsigned short int IDC_Edit = 200;
	static HWND hListBox;
	const unsigned short int IDC_ListBox = 201;
	static HWND hButtonSave;
	const unsigned short int IDC_ButtonSave = 202;
	static HWND hButtonPrint;
	const unsigned short int IDC_ButtonPrint = 203;
	static HWND hButtonExit;
	const unsigned short int IDC_ButtonExit = 204;
	DWORD dwStyle = WS_CHILD | WS_BORDER | WS_VISIBLE;
	static int LPad = 20, TPad = 30, CWidth = 120, CHeigth = 20;

	static TCHAR lpsBuffer[1024];
	static TCHAR lpsTextBuffer[200];
	HDC hDC;
	static int wmID, wmEvent;

	switch (Msg_id)
	{
		case WM_CREATE: 
		{
		if (MessageBox(NULL, TEXT("Creating a window\nContinue?"), TEXT("Warning!"), MB_YESNO) == IDNO) 
			{
				return -1;
			}
		hEdit = CreateWindowEx(0, _T("Edit"), _T(""), dwStyle, LPad, TPad, CWidth, CHeigth, hWnd, (HMENU)IDC_Edit, 0, NULL);
		if (!hEdit)
			{
				return -1;
			}
		hListBox = CreateWindowEx(0,
			_T("ListBox"),
			_T("ListBox"),
			dwStyle,
			LPad * 2 + CWidth, TPad, CWidth, CHeigth * 8,
			hWnd,
			(HMENU)IDC_ListBox,
			0, NULL
		);
		if (!hListBox) 
			{
				return -1;
			}
		hButtonSave = CreateWindowEx(0,
			_T("Button"),
			_T("Save"),
			dwStyle,
			LPad, TPad * 2 + CHeigth * 2, CWidth * 2 / 3, CHeigth,
			hWnd,
			(HMENU)IDC_ButtonSave,
			0, NULL);
		if (!hButtonSave) 
			{
				return -1;
			}


		hButtonPrint = CreateWindowEx(0,
			_T("Button"),
			_T("Print"),
			dwStyle,
			LPad, TPad * 1.5 + CHeigth * 4, CWidth * 2 / 3, CHeigth,
			hWnd,
			(HMENU)IDC_ButtonPrint,
			0, NULL);
		if (!hButtonPrint)
			{
				return -1;
			}
		EnableWindow(hButtonPrint, FALSE);

		hButtonExit = CreateWindowEx(0,
			_T("Button"),
			_T("Exit"),
			dwStyle,
			LPad, TPad + CHeigth * 6, CWidth * 2 / 3, CHeigth,
			hWnd,
			(HMENU)IDC_ButtonExit,
			0, NULL);
		if (!hButtonExit) 
			{
				return -1;
			}

		return 0;
		break;
		}
	

//-- Global Variables ------------
HINSTANCE g_hInst;
// Стартовая функция
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;
	g_hInst = hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = lpszClass;
	wc.lpfnWndProc = SpPr12_WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса окна!"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hWnd = CreateWindowEx(NULL, lpszClass, lpszAppTitle,
		WS_OVERLAPPEDWINDOW, 200, 100 ,800,600,
		NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{	
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
// Оконная процедура
LRESULT CALLBACK SpPr12_WndProc(HWND hWnd, UINT messageID,
	WPARAM wParam, LPARAM lParam)
{

	switch (messageID)
	{
	case WM_CREATE:
		if (MessageBox(NULL, TEXT("Creating a a window\nContinue"), TEXT("Warning!"), MB_YESNO) == IDYES)
		{
			return 0;
		}
		else
		{
		return -1;
		}
		break;

	case WM_LBUTTONDOWN:
	{
		HDC hdc;
		hdc = GetDC(hWnd);
		int x;	// = 50;
		int y;	// = 100;
		x = (int)(short)LOWORD(lParam);
		y = GET_Y_LPARAM(lParam);
		LPCTSTR lpszLbuttonDownMessage = TEXT("Обработка сообщения WM_LBUTTONDOWN,"
			" которое посылается в окно при щелчке левой кнопки мыши");
		TextOut(hdc, x, y, lpszLbuttonDownMessage, lstrlen(lpszLbuttonDownMessage));
		ReleaseDC(hWnd, hdc);

	}break;

	case WM_PAINT: // Вывод при обновлении окна
	{	HDC hDC;
		PAINTSTRUCT ps;
			hDC = BeginPaint(hWnd, &ps);	// Получение контекста для
											// обновления окна
			LPCTSTR lpszHelloText = TEXT("Hello, World Win32!");
		TextOut(hDC, 10, 10, lpszHelloText, lstrlen(lpszHelloText)); // Вывод в контекст
		EndPaint(hWnd, &ps); // Завершение обновления окна
	}	break;
	case WM_DESTROY: // Завершение работы приложения
	{	
	MessageBox(hWnd, lpszDestroyMessage, TEXT("From WM_DESTROY"), MB_OK);
	PostQuitMessage(5); // Посылка WM_QUIT приложению
	}break;
	
	default: // Вызов "Обработчика по умолчанию"
		return(DefWindowProc(hWnd, messageID, wParam, lParam));
	}
	return 0;// Для ветвей с "break"
}