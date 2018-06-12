#include <Windows.h>
//
//#include "../../3rd/OpenGL/include/GL.H"
//#include "../../3rd/OpenGL/include/GLU.H"
//#include "../../3rd/OpenGL/include/glut.h"
//#include "../../3rd/OpenGL/include/GLAUX.H"

#include "CChessBoard.h"

CrossPoint CrossPos[MAX_ROW_NUM][MAX_CUR_NUM];

CChessBoard::CChessBoard(int sx, int sy, int width, int height) :
	cbsx(sx), cbsy(sy), cbWidth(width), cbHeight(height) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			CrossPos[i][j].cx = this->cbsx + i * 37;
			CrossPos[i][j].cy = this->cbsy + j * 37;
		}
	}
}

CChessBoard::~CChessBoard() {
	this->cbsx = 0;
	this->cbsy = 0;
	this->cbWidth = 0;
	this->cbHeight = 0;
}

void
CChessBoard::DrawChessBoard(HWND hWnd, HDC hdc) {
	PAINTSTRUCT p;
	
	BeginPaint(hWnd, &p);
	HBRUSH hBrush = CreateSolidBrush(RGB(231, 198, 100));
	Rectangle(hdc, this->cbsx - 10, this->cbsy - 10, this->cbsx + this->cbWidth + 10, this->cbsy + this->cbHeight + 10);
	SelectObject(hdc, hBrush);
	GetStockObject(NULL_BRUSH);
	EndPaint(hWnd, &p);

	BeginPaint(hWnd, &p);
	HPEN boardPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, boardPen);
	/*MoveToEx(hdc, this->cbsx, this->cbsy, NULL);
	LineTo(hdc, this->cbsx + this->cbWidth, this->cbsy);
	MoveToEx(hdc, this->cbsx, this->cbsy, NULL);
	LineTo(hdc, this->cbsx, this->cbsy + this->cbHeight);*/
	int count = 0;

	// (0, 0)位置开始画15条线, 
	for (int i = this->cbsx; i < this->cbsx + this->cbWidth; i++) {
		if ((i - this->cbsx) % 37 == 0) {
			MoveToEx(hdc, i, this->cbsy, NULL);
			LineTo(hdc, i, this->cbsy + this->cbHeight);
		}
	}

	for (int i = this->cbsy; i < this->cbsy + this->cbHeight; i++) {
		if ((i - this->cbsy) % 37 == 0) {
			MoveToEx(hdc, this->cbsx, i, NULL);
			LineTo(hdc, this->cbsx + this->cbWidth, i);
		}
	}
	MoveToEx(hdc, this->cbsx + this->cbWidth, this->cbsy, NULL);
	LineTo(hdc, this->cbsx + this->cbWidth, this->cbsy + this->cbHeight);
	MoveToEx(hdc, this->cbsx, this->cbsy + this->cbHeight, NULL);
	LineTo(hdc, this->cbsx + this->cbWidth, this->cbsy + this->cbHeight);

	EndPaint(hWnd, &p);
}