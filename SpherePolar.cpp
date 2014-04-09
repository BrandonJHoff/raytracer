#include "SpherePolar.h"

SpherePolar::SpherePolar(Material* _material, const Point& _center, float _radius, const Vector& tempZ, const Vector& tempX)

{
	center = _center;
	radius = _radius;
	mat = _material;
	Point min(center.x() - radius, center.y() - radius, center.z() - radius);
	Point max(center.x() + radius, center.y() + radius, center.z() + radius);
	bbox = BBox(min, max);
	Z = tempZ;
	X = tempX;
	Y = cross(Z, X);
	Z.normalize();
	X.normalize();
	Y.normalize();
}

SpherePolar::~SpherePolar()
{
	delete mat;
}

bool SpherePolar::hit(HitRecord& record, 
				 const RenderContext& context,
				 const Ray& ray) const
{	
	double t;
	bool hasHit = false;
	Vector temp = ray.origin() - center;
	
	double a = dot( ray.direction(), ray.direction() );
	double b = 2.0*dot( ray.direction(), temp );
	double c = dot(temp, temp) - radius*radius;
	
	double discriminant = b*b - 4.0*a*c;
	
	if(discriminant > 0.0)
	{
		discriminant = sqrt(discriminant);
		t = ( -b - discriminant) / (2.0*a);
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

	if(hasHit)
	{	
		Point p = ray.point(record.t);
		double x = dot(p - center, X);
		double y = dot(p - center, Y);
		double z = dot(p - center, Z);

		double R = sqrt(x*x + y*y + z*z);
		double theta = acos(z/R);
		double phi = atan2(y, x);
		
		double one_over_2pi = .159154943092;
		double one_over_pi = .318309886184;

		record.uvw.e[0] = phi*one_over_2pi;
		if(record.uvw.e[0] < 0.0)
			record.uvw.e[0] += 1.0;
		record.uvw.e[1] = 1 - theta*one_over_pi;
		record.uvw.e[2] = R; 
	}
	
	return hasHit;
}

void SpherePolar::getNormal(Normal& N, const HitRecord& record, const Point& pos) const
{
	N = pos - center;
	N.normalize();
}
