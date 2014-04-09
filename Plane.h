#ifndef _PLANE_H_
#define _PLANE_H_

#include "Object.h"
#include "Ray.h"
#include "Normal.h"
#include "Point.h"
#include "RenderContext.h"
#include "HitRecord.h"
#include "Material.h"

class Plane : public Object
{
public:
	Plane(Material* _material, const Point& p, const Normal& n);
	~Plane() {}
	
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const
	{
		N = normal;
	}
	
	string getName() const { return "plane"; }
	
	Point point;
	Normal normal;
};

#endif 