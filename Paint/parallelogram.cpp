#include "stdafx.h"
#include "parallelogram.h"


IMPLEMENT_SERIAL(parallelogram, MyShape, 1)

parallelogram::parallelogram(void)
{
}


parallelogram::~parallelogram(void)
{
}
void parallelogram::innerDraw(CDC* dc) {
	POINT vertices[] = { {start.x, start.y},{end.x - 100, start.y},{end.x, end.y},{start.x + 100, end.y} };
	dc->Polygon(vertices, 4);


}