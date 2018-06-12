#include <Windows.h>

#include "resource.h"

// 游戏逻辑代码
#include "GameLogic\MainLogic.h"

#define MAX_STR_LEN 100

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

HINSTANCE g_hInstance;
HWND g_hWnd;
HDC g_hdc;
HDC g_mdc;
HGLRC g_hrc;

WCHAR szClassName[MAX_STR_LEN] = L"GoBangGame";

// 注册窗口
ATOM MyRegisterClass(HINSTANCE);
// 更新窗口
BOOL MyUpdateWindow(int);
// 显示窗口
void MyShowWindow(HWND, int);
// 消息处理
void MyProcMsg();
// 事件处理回调
LRESULT CALLBACK MyWndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	// 不引用参数
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// end
	
	MyRegisterClass(hInstance);

	if (!MyUpdateWindow(nCmdShow)) {
		return FALSE;
	}

	MyProcMsg();
	
	return 0;
}

ATOM 
MyRegisterClass(HINSTANCE hInstance) {
	g_hInstance = hInstance;

	WNDCLASSEX wcs;
	memset(&wcs, 0, sizeof(WNDCLASSEX));

	wcs.cbSize = (sizeof(WNDCLASSEX));
	wcs.cbWndExtra = 0;
	wcs.cbClsExtra = 0;
	wcs.style = CS_HREDRAW | CS_VREDRAW;
	wcs.hInstance = hInstance;
	wcs.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcs.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcs.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcs.lpszClassName = szClassName;
	wcs.lpszMenuName = NULL;
	wcs.lpfnWndProc = MyWndProc;
	wcs.hIconSm = LoadIcon(wcs.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcs);
}

BOOL 
MyUpdateWindow(int nCmdShow) {
	HWND hWnd;

	hWnd = CreateWindowW(szClassName, L"五子棋", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, g_hInstance, NULL);
	
	if (!InitResource(hWnd)) {
		MessageBox(hWnd, L"Error", L"初始化资源失败", MB_OKCANCEL | MB_ICONERROR);
		return FALSE;
	}
	

	MyShowWindow(hWnd, nCmdShow);

	return TRUE;
}

void
MyShowWindow(HWND hWnd, int nCmdShow) {
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

void 
MyProcMsg() {
	MSG msg;
	
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, NULL, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// 游戏部分
		// InvalidateRect(g_hWnd, NULL, true);
		DrawGameUI();
	}
}

LRESULT CALLBACK 
MyWndProc(HWND hWnd,
	UINT msgID, 
	WPARAM wParam, 
	LPARAM lParam) {
	switch (msgID) {
	case WM_CREATE: {

	}break;
	case WM_PAINT: {
		
		
	}break;
	case WM_DESTROY: {
		ClearResoucre();
		PostQuitMessage(0);
	}break;
	case WM_LBUTTONDOWN: {
		GetCursorClick();
	}break;
	default:
		return DefWindowProc(hWnd, msgID, wParam, lParam);
	}

	return 0;
}