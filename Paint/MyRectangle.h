#pragma once
#include "MyShape.h"
class MyRectangle :
	public MyShape
{
public:
	DECLARE_SERIAL(MyRectangle)
	MyRectangle(void);
	~MyRectangle(void);
	void innerDraw(CDC *dc);
};

