#ifndef __CCHESS_H__
#define __CCHESS_H__

class Chess {
public:
	Chess(int x, int y);
	~Chess();
	void DrawOneChess();

private:
	int cx;
	int cy;
};


#endif // !__CCHESS_H__