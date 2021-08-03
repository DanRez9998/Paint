#pragma once
#include "ShapeFactory.h"
#include "MyTriangle.h"

class TriangleFactory :
	public ShapeFactory
{
public:
	~TriangleFactory(void);
	MyShape* createShape() { return new MyTriangle(); }
	static TriangleFactory* getInstance() {
		static TriangleFactory instance;
		return &instance;
	}
private:
	TriangleFactory(void);
};

