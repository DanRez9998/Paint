#pragma once
#include "MyShape.h"
class MyLine :
	public MyShape
{
public:
	DECLARE_SERIAL(MyLine)
	MyLine(void);
	~MyLine(void);
	virtual bool canBeFilled() { return false; }
	void draw(CDC *dc);
};

