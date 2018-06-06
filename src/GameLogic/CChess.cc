#include <Windows.h>

#include <gdiplus.h>
#pragma comment (lib, "gdiplus.lib")

using namespace Gdiplus;

#include "CChess.h"


Gdiplus::Image wstone_gif(L"../../res/Pic/whitestone.gif");
Gdiplus::Image bstone_gif(L"../../res/Pic/blackstone.gif");
Gdiplus::Image lwstone_gif(L"../../res/Pic/lastwhitestone.gif");
Gdiplus::Image lbstone_gif(L"../../res/Pic/lastblackstone.gif");


Chess::Chess(int x, int y) : 
	cx(x), cy(y) {
	
}

Chess::~Chess() {
	this->cx = 0;
	this->cy = 0;
}

void
Chess::DrawOneChess() {

}