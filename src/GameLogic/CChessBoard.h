#ifndef __CCHESSBOARD_H__
#define __CCHESSBOARD_H__

#define MAX_ROW_NUM 15
#define MAX_CUR_NUM 15

struct CrossPoint {
	int cx;
	int cy;
};

class CChessBoard {
public:
	CChessBoard(int sx, int sy, int width, int height);
	~CChessBoard();
public:
	void DrawChessBoard(HWND, HDC);

private:
	int cbsx;
	int cbsy;
	int cbWidth;
	int cbHeight;
};

#endif // !__CCHESSBOARD_H__