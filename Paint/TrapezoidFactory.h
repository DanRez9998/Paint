#include "ShapeFactory.h"
#include "MyTrapezoid.h"

#pragma once

class TrapezoidFactory :
	public ShapeFactory
{
public:
	~TrapezoidFactory(void);
	MyShape* createShape() { return new MyTrapezoid(); }
	static TrapezoidFactory* getInstance() {
		static TrapezoidFactory instance;
		return &instance;
	}
private:
	TrapezoidFactory(void);
};