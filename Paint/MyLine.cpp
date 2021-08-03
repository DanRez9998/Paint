#include "StdAfx.h"
#include "MyLine.h"

IMPLEMENT_SERIAL(MyLine, MyShape, 1)

MyLine::MyLine(void)
{
}


MyLine::~MyLine(void)
{
}

void MyLine::draw(CDC *dc) {
	dc->MoveTo(start.x, start.y);
	dc->LineTo(end.x, end.y);
}