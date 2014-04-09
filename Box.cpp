#include "Box.h"

Box::Box(Material* _material, const Point& _min, const Point& _max)
{
	min = _min;
	max = _max;
	mat = _material;
	bbox = BBox(min, max);
}

Box::~Box()
{
	delete mat;
}

bool Box::hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const
{	
	bool hasHit = false;
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

	if ((tmin >= tymax) || (tymin >= tmax))
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

	if ( (tmin >= tzmax) || (tzmin >= tmax) )
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	
	if(record.hit(tmin, this, ray))
	{
		hasHit = true;
	}
	
	if(record.hit(tmax, this, ray))
	{
		hasHit = true;
	}
		
	return hasHit;

}

bool Box::intersect(float& tnear, float& tfar, const Ray& ray)
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
	
	if ((tmin >= tymax) || (tymin >= tmax))
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
	
	if ( (tmin >= tzmax) || (tzmin >= tmax) )
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

	
void Box::getNormal(Normal& N, const HitRecord& record, const Point& pos) const
{
	float epsilon = .001;
	
	if(fabs(min.x() - pos.x()) < epsilon)
		N = Normal(-1, 0, 0);
	else if(fabs(max.x() - pos.x()) < epsilon)
		N = Normal(1, 0, 0);
	else if(fabs(min.y() - pos.y()) < epsilon)
		N = Normal(0, -1, 0);
	else if(fabs(max.y() - pos.y()) < epsilon)
		N = Normal(0, 1, 0);
	else if(fabs(min.z() - pos.z()) < epsilon)
		N = Normal(0, 0, -1);
	else 
		N = Normal(0, 0, 1);
	
}