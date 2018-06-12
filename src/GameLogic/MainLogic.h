#ifndef __MAINLOGIC_H__
#define __MAINLOGIC_H__

class CChessBoard;
class CChess;

BOOL InitResource(HWND hWnd);
VOID ClearResoucre();

VOID DrawGameUI();
VOID GetCursorClick();

#endif // !__MAINLOGIC_H__