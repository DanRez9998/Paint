#pragma once
#include "ShapeFactory.h"
#include "parallelogram.h"
class ParallelogramFactory :
    public ShapeFactory
{
public:
	~ParallelogramFactory(void);
	MyShape* createShape() { return new parallelogram(); }
	static ParallelogramFactory* getInstance() {
		static ParallelogramFactory instance;
		return &instance;
	}
private:
	ParallelogramFactory(void);
};

