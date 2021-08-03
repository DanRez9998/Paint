#pragma once
#include "MyShape.h"
class MyTrapezoid :
	public MyShape
{
public:
	DECLARE_SERIAL(MyTrapezoid)
	MyTrapezoid(void);
	~MyTrapezoid(void);
	void innerDraw(CDC *dc);
};

