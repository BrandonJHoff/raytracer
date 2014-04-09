#include "Disk.h"

Disk::Disk(Material* _material, const Point& _center, const Normal& _normal, float _radius)
{
	center = _center;
	normal = _normal;
	normal.normalize();
	radius = _radius;
	mat = _material;
	Point min(center.x() - radius, center.y() - radius, center.z() - radius);
	Point max(center.x() + radius, center.y() + radius, center.z() + radius);
	bbox = BBox(min, max);
}

Disk::~Disk()
{
	delete mat;
}

bool Disk::hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const
{
	bool hasHit = false;

	float t = dot(-normal, ray.origin() - center)/dot(normal, ray.direction());

	Point temp_point = ray.point(t);
	Vector D = temp_point - center;
	if(dot(D, D) < (radius*radius))
	{
		hasHit = record.hit(t, this, ray);
	}	

	return hasHit;
}