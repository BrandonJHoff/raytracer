#ifndef _RAY_H_
#define _RAY_H_

#include "Vector.h"
#include "Point.h"

using namespace std;

class Ray
{
public:
	Ray() {}
	Ray(const Point& _origin, const Vector& _direction);
	Ray(const Ray& r) { *this = r; }
	Point origin() const { return o; }
	Vector direction() const { return dir; }
	Point point(float t) const
	{ return o + t*dir; }
	
	Point o;
	Vector dir;
};

inline Ray::Ray(const Point& _origin, const Vector& _direction)
{
	o = _origin;
	dir = _direction;
	dir.normalize();
}

inline ostream& operator<<(ostream& os, const Ray& ray)
{
	os << "(" << ray.origin() << ") + t(" << ray.direction() << ")";
	return os;
}

#endif 