#include <windows.h>
#include <tchar.h>

LPCTSTR lpszClass = TEXT("SpPr12_Class");
LPCTSTR lpszAppTitle = TEXT("������� ���� ����������. ���������� ���������");
LPCTSTR lpszDestroyMessage = TEXT("��������� ��������� WM_DESTROY, �� ����������� "
	"�������� � �������� ������ �����.��������� "
	"��������� � ����� � ����������� ���� ����������");
//-- Prototypes -------------------
LRESULT CALLBACK SpPr12_WndProc(HWND, UINT, WPARAM, LPARAM);

//-- Global Variables ------------
HINSTANCE g_hInst;
// ��������� �������
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
		MessageBox(NULL, TEXT("������ ����������� ������ ����!"),
			TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hWnd = CreateWindowEx(NULL, lpszClass, lpszAppTitle,
		WS_OVERLAPPEDWINDOW, 200, 100 ,800,600,
		NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		MessageBox(NULL, TEXT("���� �� �������!"),
			TEXT("������"), MB_OK | MB_ICONERROR);
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
// ������� ���������
LRESULT CALLBACK SpPr12_WndProc(HWND hWnd, UINT messageID,
	WPARAM wParam, LPARAM lParam)
{

	switch (messageID)
	{
	case WM_PAINT: // ����� ��� ���������� ����
	{	HDC hDC;
		PAINTSTRUCT ps;
			hDC = BeginPaint(hWnd, &ps);	// ��������� ��������� ���
											// ���������� ����
			LPCTSTR lpszHelloText = TEXT("Hello, World!");
		TextOut(hDC, 10, 10, lpszHelloText, lstrlen(lpszHelloText)); // ����� � ��������
		EndPaint(hWnd, &ps); // ���������� ���������� ����
	}	break;
	case WM_DESTROY: // ���������� ������ ����������
	{	MessageBox(hWnd, lpszDestroyMessage, TEXT("From WM_DESTROY"), MB_OK);
		PostQuitMessage(5); // ������� WM_QUIT ����������
	}break;
	default: // ����� "����������� �� ���������"
		return(DefWindowProc(hWnd, messageID, wParam, lParam));
	}
	return 0;// ��� ������ � "break"
}