#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Object.h"
#include "Ray.h"
#include "Vector.h"
#include "Point.h"
#include "HitRecord.h"
#include "RenderContext.h"
#include "Material.h"
#include "Normal.h"

class Sphere : public Object
{
public:
	Sphere(Material* _material, const Point& _center, float _radius);
	~Sphere();
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const;
	string getName() const { return "sphere"; }
	
	Point center;
	float radius;
};

#endif 