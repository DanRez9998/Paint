#pragma once
#include "MyShape.h"
class MyBrush :
	public MyShape
{
public:
	DECLARE_SERIAL(MyBrush)
	MyBrush(void);
	~MyBrush(void);
	virtual bool canBeFilled() { return false; }
	void innerDraw(CDC *dc);
};

