#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <CommCtrl.h>

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton1;
	static HWND hButton2;
	static HWND hToolTip;
	switch (msg)
	{
	case WM_CREATE:
		hButton1 = CreateWindow(TEXT("BUTTON"), TEXT("ボタン１"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)IDOK, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hButton2 = CreateWindow(TEXT("BUTTON"), TEXT("ボタン２"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)IDCANCEL, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		{
			hToolTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_ALWAYSTIP /*| TTS_BALLOON*/, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

			SendMessage(hToolTip, TTM_SETDELAYTIME, TTDT_INITIAL, 1500); // 1.5秒後に表示

			// Associate the tooltip with the tool.
			TOOLINFO toolInfo = { 0 };
			toolInfo.cbSize = sizeof(toolInfo);
			toolInfo.hwnd = hWnd;
			toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;

			toolInfo.uId = (UINT_PTR)hButton1;
			toolInfo.lpszText = L"これはメッセージボックスが表示されるボタン1だよ";
			SendMessage(hToolTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);

			toolInfo.uId = (UINT_PTR)hButton2;
			toolInfo.lpszText = L"これはメッセージボックスが表示されるボタン2だよ";
			SendMessage(hToolTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
		}
		break;
	case WM_SIZE:
		MoveWindow(hButton1, 10, 10, 256, 32, TRUE);
		MoveWindow(hButton2, 10, 50, 256, 32, TRUE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			MessageBox(hWnd, L"ボタン1", TEXT("Title"), MB_OK);
		} else if (LOWORD(wParam) == IDCANCEL) {
			MessageBox(hWnd, L"ボタン2", TEXT("Title"), MB_OK);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("Window"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
