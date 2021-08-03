#pragma once
#include "ShapeFactory.h"
#include "Square.h"
class SquareFactory :
    public ShapeFactory
{
public:
	~SquareFactory(void);
	MyShape* createShape() { return new Square(); }
	static SquareFactory* getInstance() {
		static SquareFactory instance;
		return &instance;
	}
private:
	SquareFactory(void);
};

