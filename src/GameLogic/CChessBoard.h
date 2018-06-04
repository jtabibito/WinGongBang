#ifndef __CCHESSBOARD_H__
#define __CCHESSBOARD_H__

class CChessBoard {
public:
	CChessBoard(int sx, int sy, int fx, int fy, int width, int height);
	~CChessBoard();
public:
	void DrawChessBoard();

private:
	int cbsx;
	int cbsy;
	int cbfx;
	int cbfy;
	int cbWidth;
	int cbHeight;
};

#endif // !__CCHESSBOARD_H__