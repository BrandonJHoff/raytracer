#include "Triangle.h"

Triangle::Triangle(Material* _material, const Point& p1, const Point& p2, const Point& p3)
{
	point1 = p1;
	point2 = p2;
	point3 = p3;
	normal = cross((p1 - p3), (p2 - p3));
	normal.normalize();
	mat = _material;
	//float x = 
	Point temp_min(min(p1.x(), p2.x(), p3.x()), min(p1.y(), p2.y(), p3.y()), min(p1.z(), p2.z(), p3.z()));
	Point temp_max(max(p1.x(), p2.x(), p3.x()), max(p1.y(), p2.y(), p3.y()), max(p1.z(), p2.z(), p3.z()));
	bbox = BBox(temp_min, temp_max);
}

Triangle::~Triangle()
{
	delete mat;
}

bool Triangle::hit(HitRecord& record, 
				 const RenderContext& context,
				 const Ray& ray) const
{
	bool hasHit = false;

	Vector e1 = point1 - point3;
	Vector e2 = point2 - point3;
	Vector r1 = cross(ray.direction(), e2);

	float denom = dot(e1, r1);

	if(fabs(denom) < 0.00000001)
		return false;

	float invDenom = 1/denom;

	Vector s = ray.origin() - point3;
	float b1 = dot(s, r1)*invDenom;

	if((b1 < 0) || (b1 > 1))
		return false;

	Vector r2 = cross(s, e1);
	float b2 = dot(ray.direction(), r2)*invDenom;

	if((b2 < 0) || ((b1 + b2) > 1))
		return false;

	float t = dot(e2, r2)*invDenom;

	if(record.hit(t, this, ray))
	{
		hasHit = true;
		record.uvw.e[0] = b1;
		record.uvw.e[1] = b2;
		record.uvw.e[2] = 1 - b1 - b2;
		record.uvw.normalize();
	}
	
	return hasHit;
}

float Triangle::min(float p1, float p2, float p3)
{
	if((p1 < p2) && (p1 < p3))
		return p1;
	else if(p2 < p3)
		return p2;
	return p3;
}

float Triangle::max(float p1, float p2, float p3)
{
	if((p1 > p2) && (p1 > p3))
		return p1;
	else if(p2 > p3)
		return p2;
	return p3;
}