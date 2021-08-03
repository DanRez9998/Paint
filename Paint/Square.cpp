#include "stdafx.h"
#include "Square.h"

IMPLEMENT_SERIAL(Square, MyShape, 1)

Square::Square(void)
{
}


Square::~Square(void)
{
}
void Square::innerDraw(CDC* dc) {
	dc->Rectangle((start.x + end.x) / 2 - ((start.y - end.y) / 2), start.y, (start.x + end.x) / 2 + ((start.y - end.y) / 2), end.y);
}