#pragma once
#include "ShapeFactory.h"
#include "MyEllipse.h"

class EllipseFactory :
	public ShapeFactory
{
public:	
	~EllipseFactory(void);
	MyShape* createShape() { return new MyEllipse(); }
	static EllipseFactory* getInstance() {
		static EllipseFactory instance;
		return &instance;
	}
private:
	EllipseFactory(void);
};

