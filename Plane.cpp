#include "Plane.h"

Plane::Plane(Material* _material, const Point& p, const Normal& n)
{
	point = p;
	normal = n;
	normal.normalize();
	mat = _material;
}

bool Plane::hit(HitRecord& record, 
				const RenderContext& context,
				const Ray& ray) const
{
	float t = dot(-normal, ray.origin() - point)/dot(normal, ray.direction());
	return record.hit(t, this, ray);
}
