#ifndef _POINT_H_
#define _POINT_H_

#include "Vector.h"
#include <math.h>

class Point
{
public:
	Point();
	Point(float x, float y, float z);
	Point(const Point& p) { *this = p; }
	~Point() {}
	
	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }
	
	friend ostream& operator<<(ostream& os, const Point& p);
	friend bool operator==(const Point& p1, const Point& p2);
	friend bool operator!=(const Point& p1, const Point& p2);
	
	friend Point operator+(const Point& p1, const Point& p2);
	friend Point operator+(const Point& p, const Vector& v);
	friend Point operator-(const Point& p, const Vector& v);
	friend Vector operator-(const Point& p1, const Point& p2);
	friend Point operator*(const Point& p, float s);
	friend Point operator*(float s, const Point& p);
	friend Point operator/(const Point&p, float s);
	
	Point operator=(const Point& p);
		
	float operator[](int i) { return e[i]; }
	
	float e[3];
};

#endif 
