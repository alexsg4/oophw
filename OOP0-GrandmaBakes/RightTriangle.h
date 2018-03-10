#pragma once
#include "shape.h"
class RightTriangle :
	public Shape
{
private:
	int len2;
public:
	RightTriangle();
	RightTriangle(int length1, int length2, int height);
	~RightTriangle();

	virtual int getOuterArea() const override;
	virtual int getVolume() const override;
	virtual void showDetails() override;
};

