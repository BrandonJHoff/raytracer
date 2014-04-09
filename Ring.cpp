#include "Ring.h"

Ring::Ring(Material* _material, const Point& _center, const Normal& _normal, float _minRad, float _maxRad)
{
	center = _center;
	normal = _normal;
	normal.normalize();
	minRad = _minRad;
	maxRad = _maxRad;
	mat = _material;
	Point min(center.x() - maxRad, center.y() - maxRad, center.z() - maxRad);
	Point max(center.x() + maxRad, center.y() + maxRad, center.z() + maxRad);
	bbox = BBox(min, max);
}

Ring::~Ring()
{
	delete mat;
}

bool Ring::hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const
{
	bool hasHit = false;

	float t = dot(-normal, ray.origin() - center)/dot(normal, ray.direction());

	Point temp_point = ray.point(t);
	Vector D = temp_point - center;
	float distance = dot(D, D);
	if((distance > (minRad*minRad)) && (distance  < (maxRad*maxRad)))
	{
		hasHit = record.hit(t, this, ray);
	}	

	return hasHit;
}