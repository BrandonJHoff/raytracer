#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Object.h"
#include "Ray.h"
#include "Vector.h"
#include "Point.h"
#include "HitRecord.h"
#include "RenderContext.h"
#include "Material.h"
#include "Normal.h"

class Triangle : public Object
{
public:
	Triangle (Material* _material, const Point& p1, const Point& p2, const Point& p3);
	~Triangle ();
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const
	{ N = normal; }
	float min(float p1, float p2, float p3);
	float max(float p1, float p2, float p3);
	string getName() const { return "triangle"; }
	
	Point point1, point2, point3;
	Normal normal;
};

#endif 