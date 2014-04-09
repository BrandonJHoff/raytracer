#include "Sphere.h"

Sphere::Sphere(Material* _material, const Point& _center, float _radius)
{
	center = _center;
	radius = _radius;
	mat = _material;
	Point min(center.x() - radius, center.y() - radius, center.z() - radius);
	Point max(center.x() + radius, center.y() + radius, center.z() + radius);
	bbox = BBox(min, max);
}

Sphere::~Sphere()
{
	delete mat;
}

bool Sphere::hit(HitRecord& record, 
				 const RenderContext& context,
				 const Ray& ray) const
{	
	bool hasHit = false;
	Vector temp = ray.origin() - center;
	
	double a = dot( ray.direction(), ray.direction() );
	double b = 2.0*dot( ray.direction(), temp );
	double c = dot(temp, temp) - radius*radius;
	
	double discriminant = b*b - 4.0*a*c;
	
	if(discriminant > 0.0)
	{
		discriminant = sqrt(discriminant);
		double t = ( -b - discriminant) / (2.0*a);
		if(record.hit(t, this, ray))
		{
			hasHit = true;
		}
		
		t = (-b + discriminant) / (2.0*a);
		if(record.hit(t, this, ray))
		{
			hasHit = true;
		}
	}
	
	return hasHit;
}

void Sphere::getNormal(Normal& N, const HitRecord& record, const Point& pos) const
{
	N = pos - center;
	N.normalize();
}
