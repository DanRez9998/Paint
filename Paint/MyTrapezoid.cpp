#include "StdAfx.h"
#include "MyTrapezoid.h"

IMPLEMENT_SERIAL(MyTrapezoid, MyShape, 1)

MyTrapezoid::MyTrapezoid(void)
{
}


MyTrapezoid::~MyTrapezoid(void)
{
}
void MyTrapezoid::innerDraw(CDC *dc) {
	POINT vertices[] = { {start.x, start.y},{start.x + 50, start.y},{end.x, end.y},{start.x - 50, end.y} };
	dc->Polygon(vertices, 4);


}
