#pragma once
#include <string.h>

class Shape
{
private:
	int height;
	int len1;
	char type[20] = "Basic Shape";

public:
	Shape();
	Shape(int, int);
	~Shape();

	virtual int getOuterArea() const;
	virtual int getVolume() const;
	virtual void showDetails();
	const char* getType() const;
	int getHeight() const;
	int getLen1() const;
	void setHeight(const int h);
	void setLen1(const int l);
};

