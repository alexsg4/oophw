#pragma once
#include "shape.h"
#define PI 3.14
class Circle :
	public Shape
{
public:
	Circle();
	Circle(int radius, int height);
	~Circle();

	virtual int getOuterArea() const override;
	virtual int getVolume() const override;
	virtual void showDetails() override;
};

