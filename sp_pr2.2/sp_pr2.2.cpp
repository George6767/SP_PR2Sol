#include <Windows.h>
#include <Windowsx.h>  // for GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam macro;
#include <tchar.h>


LPCTSTR g_lpszClassName = TEXT("sp_pr1_ClassName");
LPCTSTR g_lpszAplicationTitle = TEXT("Application main window. Programmer: <Poleshchuk, Egor>");
LPCTSTR g_lpszDestroyMessage = TEXT("Received message WM_DESTROY, from event handler which printed this message, when the window collapsed");
LPCTSTR g_lpszLMBClickMessage = TEXT("Received message WM_LBUTTONDOWN, from event handler which printed this message, when left mouse button clicked");
LPCTSTR g_lpszPaintMessage = TEXT("Received message WM_PAINT, from event handler which printed this message, when window changed size");

LRESULT CALLBACK pr1_WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow) {

	HWND hWnd;
	MSG Msg;
	WNDCLASSEX WndClass;

	memset(&WndClass, 0, sizeof(WNDCLASSEX));

	WndClass.cbSize = sizeof(WNDCLASSEX);								// The size, in bytes, of this structure. Set this member to sizeof(WNDCLASSEX)
	WndClass.lpszClassName = g_lpszClassName;							// String, it specifies the window class name
	WndClass.lpfnWndProc = pr1_WndProc;									// A pointer to the window procedure
	WndClass.style = CS_VREDRAW | CS_HREDRAW;							// The class styles (for WM_PAINT)
	WndClass.hInstance = hInstance;										// A handle to the instance that contains the window procedure for the class. 
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK));		// A handle to the class icon, NULL - default icon
	WndClass.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));		// A handle to the class cursor, NULL - default cursor
	WndClass.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));		// A handle to the class background brush
	WndClass.lpszMenuName = NULL;										// String that specifies the resource name of the class menu, NULL - without menu
	WndClass.cbClsExtra = 0;											// The number of extra bytes to allocate following the window-class structure.
	WndClass.cbWndExtra = 0;


	if (!RegisterClassEx(&WndClass)) {									// Register window class or return FALSE
		MessageBox(
			NULL,
			TEXT("Registration failed!"),
			TEXT("Error!"),
			MB_OK | MB_ICONERROR
		);

		return FALSE;
	}

	hWnd = CreateWindowEx(											// Create window and return handler											
		NULL,														// The extended window style of the window being created
		WndClass.lpszClassName,										// A null-terminated string pointer to registered window class.
		g_lpszAplicationTitle,										// The window title.
		WS_OVERLAPPEDWINDOW,										// The style of the window being created (так же обработчик по-умолчанию)
		600,														// The initial horizontal position of the window
		300,														// The initial vertical position of the window
		300,														// The width, in device units, of the window
		300,														// The height, in device units, of the window
		NULL,														// (Opt) A handle to the parent or owner window of the window being created.
		NULL,														// (Opt) A handle to a menu, or specifies a child-window identifier, depending on the window style		
		hInstance,													// (Opt) A handle to the instance of the module to be associated with the window.
		NULL														// (Opt) ??
	);

	if (!hWnd) {														// If the creation of the window failed return 0
		MessageBox(
			NULL,
			TEXT("Creation failed!"),
			TEXT("Error!"), MB_OK | MB_ICONERROR
		);

		return FALSE;
	}


	ShowWindow(hWnd, nCmdShow);										// Display window
	UpdateWindow(hWnd);												// Update window

	while (GetMessage(&Msg, NULL, 0, 0)) {							// Get msg from queue
		DispatchMessage(&Msg);										// Send message to the relevant window procedure
	}

	return Msg.wParam;
}

LRESULT CALLBACK pr1_WndProc(HWND hWnd, UINT Msg_id, WPARAM wParam, LPARAM lParam) {
	static HWND hEdit;
	const unsigned short int IDC_Edit = 200;
	static HWND hListBox;
	const unsigned short int IDC_ListBox = 201;
	static HWND hButtonSave;
	const unsigned short int IDC_ButtonSave = 202;
	static HWND hButtonOut;
	const unsigned short int IDC_ButtoOut = 203;
	static HWND hButtonExit;
	const unsigned short int IDC_ButtonExit = 204;


	static TCHAR lpszBuffer[1024];
	HDC hDC;

	switch (Msg_id) {

	case WM_CREATE:
		if (MessageBox(NULL, TEXT("Creating a window\nContinue?"), TEXT("Warning!"), MB_YESNO) == IDYES) {
			return 0;
		}
		else {
			return -1;
		}
		break;

	case WM_LBUTTONDOWN:

		hDC = GetDC(hWnd);

		int xPos, yPos;
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);

		RECT lpRect;
		lpRect.left = xPos;
		lpRect.top = yPos;
		lpRect.right = xPos + 200;
		lpRect.bottom = yPos + 100;

		_stprintf_s(lpszBuffer, g_lpszLMBClickMessage);
		DrawText(hDC, lpszBuffer, lstrlen(lpszBuffer), &lpRect, DT_CENTER | DT_WORDBREAK);

		ReleaseDC(hWnd, hDC);
		break;

	case WM_PAINT:
		PAINTSTRUCT Ps;
		hDC = BeginPaint(hWnd, &Ps);
		_stprintf_s(lpszBuffer, g_lpszPaintMessage);
		TextOut(hDC, 20, 100, lpszBuffer, lstrlen(lpszBuffer));
		EndPaint(hWnd, &Ps);
		break;

	case WM_DESTROY:
		MessageBox(NULL, g_lpszDestroyMessage, TEXT("Error!"), MB_OK);
		PostQuitMessage(5);
		break;

	default: return(DefWindowProc(hWnd, Msg_id, wParam, lParam));
	}

	return FALSE;
}