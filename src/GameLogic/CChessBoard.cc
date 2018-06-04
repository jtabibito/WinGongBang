#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../3rd/OpenGL/include/GL.H"
#include "../../3rd/OpenGL/include/GLU.H"
#include "../../3rd/OpenGL/include/glut.h"
#include "../../3rd/OpenGL/include/GLAUX.H"

#include "CChessBoard.h"

CChessBoard::CChessBoard(int sx, int sy, int fx, int fy, int width, int height) :
	cbsx(sx), cbsy(sy), cbfx(fx), cbfy(fy) {
	this->cbWidth = width;
	this->cbHeight = height;
}

CChessBoard::~CChessBoard() {
	this->cbsx = 0;
	this->cbsy = 0;
	this->cbfx = 0;
	this->cbfy = 0;
	this->cbWidth = 0;
	this->cbHeight = 0;
}

void
CChessBoard::DrawChessBoard() {

}