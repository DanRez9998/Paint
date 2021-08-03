#include "StdAfx.h"
#include "MySpray.h"

IMPLEMENT_SERIAL(MySpray, MyShape, 1)

MySpray::MySpray(void)
{
	addPoints();
}

MySpray::~MySpray(void) {}

void MySpray::addPoints(){
	for(int i = 0; i < 60; i++)
	{
		deltaX.push_back((rand()%(20))); // adds 60 random values between 0-19 to the deltaX vector
		deltaY.push_back((rand()%(20))); // adds 60 random values between 0-19 to the deltaY vector
	}
}

void MySpray::innerDraw(CDC *dc){
	for(int i = 0; i < 60; i++)
	{
		randomPixel.SetPoint((start.x + deltaX[i]), (start.y - deltaY[i])); // set the random pixel point with the selected random numbers
		dc->SetPixel(randomPixel, bgColor); // draw pixel on the random pixel selected with the selected color
	}
}
