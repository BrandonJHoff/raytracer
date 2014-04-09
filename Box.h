#ifndef _BOX_H_
#define _BOX_H_

#include "Object.h"
#include "Ray.h"
#include "Point.h"
#include "HitRecord.h"
#include "RenderContext.h"
#include "Material.h"
#include "Normal.h"
#include "BBox.h"

class Box : public Object
{
public:
	Box() {}
	Box(Material* _material, const Point& _min, const Point& _max);
	~Box();
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const;
	bool intersect(float& tnear, float& tfar, const Ray& ray);
	string getName() const { return "box"; }
	
	Point min, max;
};

#endif 