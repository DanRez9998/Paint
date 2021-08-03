#include "StdAfx.h"
#include "MyTriangle.h"

IMPLEMENT_SERIAL(MyTriangle, MyShape, 1)

MyTriangle::MyTriangle(void)
{
}


MyTriangle::~MyTriangle(void)
{
}
void MyTriangle::innerDraw(CDC *dc) {
	POINT vertices[] = { {start.x, start.y}, {start.x-50, end.y}, {start.x+50, end.y} };
	dc->Polygon(vertices, 3);

	
}
