#pragma once
#include "MyRectangle.h"
class parallelogram :
    public MyRectangle
{
public:
	DECLARE_SERIAL(parallelogram)
	parallelogram(void);
	~parallelogram(void);
	void innerDraw(CDC* dc);
};

