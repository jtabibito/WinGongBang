#include <Windows.h>
#include <tchar.h>

#include "CChess.h"

// extern by GameMain.cc
extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
extern HDC g_hdc;
extern HDC g_mdc;


HBITMAP white_stone;
HBITMAP black_stone;
HBITMAP previous_white_stone;
HBITMAP previous_black_stone;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

CChess::CChess(ColorType colortype) {
	this->colortype = colortype;
	this->did_draw = 0;
}

CChess::~CChess() {
	this->cx = 0;
	this->cy = 0;
	this->colortype = Nil_Chess;
	this->did_draw = 0;
}

void
CChess::DrawOneChess(int x, int y) {
	this->cx = x;
	this->cy = y;

	if (this->colortype == White_Chess) {
		SelectObject(g_mdc, white_stone);
		BitBlt(g_hdc, this->cx - 20, this->cy - 20, WINDOW_WIDTH, WINDOW_WIDTH, g_mdc, 0, 0, SRCCOPY);
	} else if (this->colortype == Black_Chess) {
		SelectObject(g_mdc, black_stone);
		BitBlt(g_hdc, this->cx - 20, this->cy - 20, WINDOW_WIDTH, WINDOW_HEIGHT, g_mdc, 0, 0, SRCCOPY);
	}
}

void
CChess::DrawLastChess() {
	if (this->colortype == White_Chess) {
		SelectObject(g_mdc, previous_white_stone);
		BitBlt(g_hdc, this->cx - 10, this->cy - 10, WINDOW_WIDTH, WINDOW_WIDTH, g_mdc, 0, 0, SRCAND);
	} else if (this->colortype == Black_Chess) {
		SelectObject(g_mdc, previous_black_stone);
		BitBlt(g_hdc, this->cx - 10, this->cy - 10, WINDOW_WIDTH, WINDOW_WIDTH, g_mdc, 0, 0, SRCAND);
	}
}