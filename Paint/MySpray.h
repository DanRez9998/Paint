#pragma once
#include "MyShape.h"
#include <vector>
using namespace std;
class MySpray :
	public MyShape
{
public:
	DECLARE_SERIAL(MySpray)
	MySpray(void);
	~MySpray(void);
	virtual bool canBeFilled() { return false; }
	void innerDraw(CDC *dc); // draws the 60 pixels on the dc, according to the pixels selected int the vectors
	void addPoints(); // adds 60 points to the deltaX and deltaY vectors
	CPoint randomPixel;
private:
	vector<int> deltaX;
	vector<int> deltaY;
};
