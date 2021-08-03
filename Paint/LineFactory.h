#pragma once
#include "ShapeFactory.h"
#include "MyLine.h"

class LineFactory :
	public ShapeFactory
{
public:	
	~LineFactory(void);
	MyShape* createShape() { return new MyLine(); }
	static LineFactory* getInstance() {
		static LineFactory instance;
		return &instance;
	}
private:
	LineFactory(void);
};

