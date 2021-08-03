#include "StdAfx.h"
#include "MyEllipse.h"

IMPLEMENT_SERIAL(MyEllipse, MyShape, 1)

MyEllipse::MyEllipse(void)
{
}


MyEllipse::~MyEllipse(void)
{
}

void MyEllipse::innerDraw(CDC *dc) {
	dc->Ellipse(start.x, start.y, end.x, end.y);
}
