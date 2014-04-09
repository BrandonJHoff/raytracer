#ifndef _SPHEREPOLAR_H_
#define _SPHEREPOLAR_H_

#include "Object.h"
#include "Ray.h"
#include "Vector.h"
#include "Point.h"
#include "HitRecord.h"
#include "RenderContext.h"
#include "Material.h"
#include "Normal.h"

class SpherePolar : public Object
{
public:
	SpherePolar(Material* _material, const Point& _center, float _radius, const Vector& tempZ, const Vector& tempX);
	~SpherePolar();
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const;
	string getName() const { return "spherepolar"; }
	
	Point center;
	float radius;
	Vector Z, Y, X;
};

#endif 