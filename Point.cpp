#include "Point.h"

Point::Point()
{
}

Point::Point(float x, float y, float z)
{
	e[0] = x; 
	e[1] = y;
	e[2] = z;
}

ostream& operator<<(ostream& os, const Point& p)
{
	os << "(" << p.e[0] << " " << p.e[1] << " " << p.e[2] << ")";
	return os;
}

bool operator==(const Point& p1, const Point& p2)
{
	if(p1.e[0] != p2.e[0]) return false;
	if(p1.e[1] != p2.e[1]) return false;
	if(p1.e[2] != p2.e[2]) return false;
	return true;
}

bool operator!=(const Point& p1, const Point& p2)
{
	return !(p1 == p2);
}

Point operator+(const Point& p1, const Point& p2)
{
	return Point(p1.x() + p2.x(), p1.y() + p2.y(), p1.z() + p2.z());
}
	
Point operator+(const Point& p, const Vector& v)
{
	return Point(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}

Point operator-(const Point& p, const Vector& v)
{
	return Point(p.x() - v.x(), p.y() - v.y(), p.z() - v.z());
}

Vector operator-(const Point& p1, const Point& p2)
{
	return Vector(p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z());
}

Point operator*(const Point& p, float s)
{
	return Point(p.e[0]*s, p.e[1]*s, p.e[2]*s);
}

Point operator*(float s, const Point& p)
{
	return Point(p.e[0]*s, p.e[1]*s, p.e[2]*s);
}

Point operator/(const Point&p, float s)
{
	return Point(p.x()/s, p.y()/s, p.z()/s);
}

Point Point::operator=(const Point& p)
{
	e[0] = p.e[0];
	e[1] = p.e[1];
	e[2] = p.e[2];
}