#pragma once
#include "shape.h"
class Rectangle :
	public Shape
{
private:
	int len2=0;
public:
	Rectangle();
	Rectangle(int length1, int length2, int height);
	Rectangle(int length, int height); //square
	~Rectangle();

	virtual int getOuterArea() const override;
	virtual int getVolume() const override;
	virtual void showDetails() override;
};

