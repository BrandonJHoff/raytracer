#include "BBox.h"

BBox::BBox(const Point& _min, const Point& _max)
{
	min = _min;
	max = _max;
}

bool BBox::intersect(float& tnear, float& tfar, const Ray& ray) const
{	
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	
	if (ray.direction().x() >= 0) 
	{
		tmin = (min.x() - ray.origin().x()) / ray.direction().x();
		tmax = (max.x() - ray.origin().x()) / ray.direction().x();
	}
	else 
	{
		tmin = (max.x() - ray.origin().x()) / ray.direction().x();
		tmax = (min.x() - ray.origin().x()) / ray.direction().x();
	}
	
	if (ray.direction().y() >= 0) 
	{
		tymin = (min.y() - ray.origin().y()) / ray.direction().y();
		
		tymax = (max.y() - ray.origin().y()) / ray.direction().y();
	}
	else 
	{
		tymin = (max.y() - ray.origin().y()) / ray.direction().y();
		tymax = (min.y() - ray.origin().y()) / ray.direction().y();
	}
	
	if ((tmin > tymax) || (tymin > tmax))
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	
	if (ray.direction().z() >= 0) 
	{
		tzmin = (min.z() - ray.origin().z()) / ray.direction().z();
		tzmax = (max.z() - ray.origin().z()) / ray.direction().z();
	}
	else 
	{
		tzmin = (max.z() - ray.origin().z()) / ray.direction().z();
		tzmax = (min.z() - ray.origin().z()) / ray.direction().z();
	}
	
	if ( (tmin > tzmax) || (tzmin > tmax) )
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	
	if((tmin < 100000.0) && (tmax > .001))
	{
		if(tmin < 0)
			tnear = 0;
		else
			tnear = tmin;
		
		tfar = tmax;
		
		return true;
	}
	else
	{
		return false;
	}
}

BBox surround(const BBox& b1, const BBox& b2)
{
	return BBox(Point(Min(b1.min.x(), b2.min.x()), Min(b1.min.y(), b2.min.y()), Min(b1.min.z(), b2.min.z())),
			Point(Max(b1.max.x(), b2.max.x()), Max(b1.max.y(), b2.max.y()), Max(b1.max.z(), b2.max.z())));
}

float Min(float m1, float m2)
{
	if(m1 < m2)
		return m1;
	return m2;
}

float Max(float m1, float m2)
{
	if(m1 > m2)
		return m1;
	return m2;
}