#ifndef _BBOX_H_
#define _BBOX_H_

#include "Ray.h"
#include "Point.h"

class BBox
{
public:
	BBox() {}
	BBox(const Point& _min, const Point& _max);
	~BBox() {}
	bool intersect(float& tnear, float& tfar, const Ray& ray) const ;
	friend BBox surround(const BBox& b1, const BBox& b2);
	friend float Min(float m1, float m2);
	friend float Max(float m1, float m2);

	Point min, max;
};

#endif 