#pragma once
#include "shape.h"

class Circle :
	public Shape
{
private:
	const double PI = 3.14;

public:
	Circle();
	Circle(int radius, int height);
	~Circle();

	virtual int getOuterArea() const override;
	virtual int getVolume() const override;
	virtual void showDetails() override;
};

