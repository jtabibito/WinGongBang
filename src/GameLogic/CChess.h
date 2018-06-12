#ifndef __CCHESS_H__
#define __CCHESS_H__

enum ColorType {
	Nil_Chess,
	White_Chess,
	Black_Chess,
};

class CChess {
public:
	CChess(ColorType colortype);
	~CChess();
	void DrawOneChess(int x, int y);
	void DrawLastChess();

public:
	int cx;
	int cy;
	int did_draw;

private:
	int colortype;
};



#endif // !__CCHESS_H__