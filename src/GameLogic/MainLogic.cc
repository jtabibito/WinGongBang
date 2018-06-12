#include <Windows.h>

#include <math.h>

#include "resource.h"

//
//#include "GL.H"
//#include "GLU.H"
//#include "glut.h"
//#include "GLAUX.H"

#include "MainLogic.h"
#include "CChessBoard.h"
#include "CChess.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAX_ROW_NUM 15				// ��������
#define MAX_CUR_NUM 15				// ��������

#define RAIUS_OF_STONE 10			// ���Ӱ뾶

// extern by GameMain.cc
extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
extern HDC g_hdc;
extern HDC g_mdc;
extern HGLRC g_hrc;

// extern by CChessBoard.cc
extern CrossPoint CrossPos[MAX_ROW_NUM][MAX_CUR_NUM];
CChessBoard g_chessboard(50, 20, 518, 518);

// extern by CChess.cc
extern HBITMAP white_stone;
extern HBITMAP black_stone;
extern HBITMAP previous_white_stone;
extern HBITMAP previous_black_stone;


LPPOINT CursorPt = (LPPOINT)malloc(sizeof(tagPOINT));	// ���λ�ýṹ


// ʮ�ֹ��ṹ
struct crosscursor {
	int x;
	int y;
}crossCursor;


static void DisplayMousePos();
static void DrawRectCross(int cx, int cy);
static void DrawChessUI();


// TODO: ������
// ����
CChess* BLACKCHESS[113];
static int B_used = 0;
static int B_turn = 1;

// ����
CChess* WHITECHESS[112];
static int W_used = 0;
static int W_turn = 0;

static int Sum_BCHESS;
static int Sum_WCHESS;
// End

// TODO: Begin
// ��ʼ����Դ�Լ��ͷ���Դ
BOOL InitResource(HWND hWnd) {
	g_hWnd = hWnd;

	HBITMAP nil_bmp;
	g_hdc = GetDC(g_hWnd);
	g_mdc = CreateCompatibleDC(g_hdc);
	nil_bmp = CreateCompatibleBitmap(g_hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(g_mdc, nil_bmp);

	black_stone = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	previous_black_stone = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
	white_stone = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP4));
	previous_white_stone = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP3));

	Sum_BCHESS = sizeof(BLACKCHESS) / sizeof(void*);
	Sum_WCHESS = sizeof(WHITECHESS) / sizeof(void*);

	for (int i = 0; i < Sum_WCHESS; i++) {
		WHITECHESS[i] = new CChess(White_Chess);
	}

	for (int i = 0; i < Sum_BCHESS; i++) {
		BLACKCHESS[i] = new CChess(Black_Chess);
	}

	DrawGameUI();
	return TRUE;
}

VOID ClearResoucre() {
	DeleteObject(white_stone);
	DeleteObject(black_stone);
	DeleteObject(previous_white_stone);
	DeleteObject(previous_black_stone);

	for (int i = 0; i < Sum_BCHESS; i++) {
		BLACKCHESS[i]->~CChess();
	}

	for (int i = 0; i < Sum_WCHESS; i++) {
		WHITECHESS[i]->~CChess();
	}
	
	g_chessboard.~CChessBoard();

	DeleteDC(g_mdc);
	ReleaseDC(g_hWnd, g_hdc);
}
// End

//
// ������Ϸͼ��
VOID
DrawGameUI() {
	g_chessboard.DrawChessBoard(g_hWnd, g_hdc);
	DisplayMousePos();
	DrawChessUI();
}

//
// ��굽���̽��������
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

// TODO: Begin
// �������׼��
static void
DisplayMousePos() {
	memset(CursorPt, 0, sizeof(tagPOINT));
	GetCursorPos(CursorPt);
	ScreenToClient(g_hWnd, CursorPt);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (DistanceInspector(CursorPt->x, CrossPos[i][j].cx, CursorPt->y, CrossPos[i][j].cy)) {
				crossCursor.x = CrossPos[i][j].cx;
				crossCursor.y = CrossPos[i][j].cy;
				DrawRectCross(crossCursor.x, crossCursor.y);
				// DrawRectCross(CrossPos[i][j].cx, CrossPos[i][j].cy);
			}
		}
	}
}

static void
DrawRectCross(int cx, int cy) {
	PAINTSTRUCT p;
	BeginPaint(g_hWnd, &p);
	HPEN crossPen = CreatePen(PS_SOLID, 2, RGB(0, 90, 255));
	SelectObject(g_hdc, crossPen);
	/// ����ʮ��
	if (cx > 50 && cy != 20) {
		MoveToEx(g_hdc, cx - 5, cy - 5, NULL);
		LineTo(g_hdc, cx - 5, cy - 15);

		MoveToEx(g_hdc, cx - 5, cy - 5, NULL);
		LineTo(g_hdc, cx - 15, cy - 5);
	}

	/// ����ʮ��
	if (cx < 568 && cy != 538) {
		MoveToEx(g_hdc, cx + 5, cy + 5, NULL);
		LineTo(g_hdc, cx + 5, cy + 15);

		MoveToEx(g_hdc, cx + 5, cy + 5, NULL);
		LineTo(g_hdc, cx + 15, cy + 5);
	}
	
	/// ����ʮ��
	if (cy > 20 && cx != 568) {
		MoveToEx(g_hdc, cx + 5, cy - 5, NULL);
		LineTo(g_hdc, cx + 5, cy - 15);

		MoveToEx(g_hdc, cx + 5, cy - 5, NULL);
		LineTo(g_hdc, cx + 15, cy - 5);
	}

	/// ����ʮ��
	if (cy < 538 && cx != 50) {
		MoveToEx(g_hdc, cx - 5, cy + 5, NULL);
		LineTo(g_hdc, cx - 5, cy + 15);

		MoveToEx(g_hdc, cx - 5, cy + 5, NULL);
		LineTo(g_hdc, cx - 15, cy + 5);
	}
	EndPaint(g_hWnd, &p);
}
// End

// 
// ��ȡ�����
VOID
GetCursorClick() {
	if (B_turn) {
		BLACKCHESS[B_used]->cx = crossCursor.x;
		BLACKCHESS[B_used]->cy = crossCursor.y;
		BLACKCHESS[B_used++]->did_draw = 1;
		B_turn--;
		W_turn++;
	} else if (W_turn) {
		WHITECHESS[W_used]->cx = crossCursor.x;
		WHITECHESS[W_used]->cy = crossCursor.y;
		WHITECHESS[W_used++]->did_draw = 1;
		W_turn--;
		B_turn++;
	}
}

// TODO: Begin
// ��������
static void
DrawChessUI() {
	for (int i = 0; i < Sum_BCHESS; i++) {
		if (BLACKCHESS[i]->did_draw) {
			BLACKCHESS[i]->DrawOneChess(BLACKCHESS[i]->cx, BLACKCHESS[i]->cy);
		}
	}

	for (int i = 0; i < Sum_WCHESS; i++) {
		if (WHITECHESS[i]->did_draw) {
			WHITECHESS[i]->DrawOneChess(WHITECHESS[i]->cx, WHITECHESS[i]->cy);
		}
	}

	// ������һ������λ��
	if (B_used > 0 && B_turn) {
		BLACKCHESS[B_used - 1]->DrawLastChess();
	} else if (W_used > 0 && W_turn) {
		WHITECHESS[W_used - 1]->DrawLastChess();
	}
}
// End