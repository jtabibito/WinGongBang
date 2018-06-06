#include <Windows.h>

#include <math.h>


//
//#include "GL.H"
//#include "GLU.H"
//#include "glut.h"
//#include "GLAUX.H"

#include "MainLogic.h"
#include "CChessBoard.h"


#define MAX_ROW_POS 15
#define MAX_CUR_POS 15

#define RAIUS_OF_STONE 10			// 棋子半径

extern HWND g_hWnd;
extern HDC g_hdc;
extern HGLRC g_hrc;
extern CrossPoint CrossPos[MAX_ROW_POS][MAX_CUR_POS];

CChessBoard g_chessboard(50, 20, 518, 518);

LPPOINT CursorPt = (LPPOINT)malloc(sizeof(tagPOINT));

/*
// 十字光标结构
struct crosscursor {
	int x;
	int y;
}crosscursor;
*/

void
DrawGameUI() {
	g_chessboard.DrawChessBoard(g_hWnd, g_hdc);
	DisplayMousePos();
}


static BOOL
DistanceInspector(int Mx,
	int Cx,
	int My,
	int Cy) {
	if ((pow((Mx - Cx), 2) + pow((My - Cy), 2)) >= pow(RAIUS_OF_STONE, 2)) {
		return FALSE;
	}

	return TRUE;
}

void
DisplayMousePos() {
	memset(CursorPt, 0, sizeof(tagPOINT));
	GetCursorPos(CursorPt);
	ScreenToClient(g_hWnd, CursorPt);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (DistanceInspector(CursorPt->x, CrossPos[i][j].cx, CursorPt->y, CrossPos[i][j].cy)) {
				// crossCursor.x = CrossPos[i][j].cx;
				// crossCursor.y = CrossPos[i][j].cy;
				// DrawRectCross(crossCursor.x, crossCursor.y);
				DrawRectCross(CrossPos[i][j].cx, CrossPos[i][j].cy);
			}
		}
	}
}

void
DrawRectCross(int cx, int cy) {
	PAINTSTRUCT p;
	BeginPaint(g_hWnd, &p);
	HPEN crossPen = CreatePen(PS_SOLID, 2, RGB(0, 103, 255));
	SelectObject(g_hdc, crossPen);
	/// 左上十字
	if (cx > 50 && cy != 20) {
		MoveToEx(g_hdc, cx - 5, cy - 5, NULL);
		LineTo(g_hdc, cx - 5, cy - 15);

		MoveToEx(g_hdc, cx - 5, cy - 5, NULL);
		LineTo(g_hdc, cx - 15, cy - 5);
	}

	/// 右下十字
	if (cx < 568 && cy != 538) {
		MoveToEx(g_hdc, cx + 5, cy + 5, NULL);
		LineTo(g_hdc, cx + 5, cy + 15);

		MoveToEx(g_hdc, cx + 5, cy + 5, NULL);
		LineTo(g_hdc, cx + 15, cy + 5);
	}
	
	/// 右上十字
	if (cy > 20 && cx != 568) {
		MoveToEx(g_hdc, cx + 5, cy - 5, NULL);
		LineTo(g_hdc, cx + 5, cy - 15);

		MoveToEx(g_hdc, cx + 5, cy - 5, NULL);
		LineTo(g_hdc, cx + 15, cy - 5);
	}

	/// 左下十字
	if (cy < 538 && cx != 50) {
		MoveToEx(g_hdc, cx - 5, cy + 5, NULL);
		LineTo(g_hdc, cx - 5, cy + 15);

		MoveToEx(g_hdc, cx - 5, cy + 5, NULL);
		LineTo(g_hdc, cx - 15, cy + 5);
	}
	EndPaint(g_hWnd, &p);
}
