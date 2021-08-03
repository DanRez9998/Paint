#pragma once
#include "MyRectangle.h"
class Square :
    public MyRectangle
{
    public:
	DECLARE_SERIAL(Square)
	Square(void);
	~Square(void);
	void innerDraw(CDC *dc);
};

