#ifndef _RING_H_
#define _RING_H_

#include "Object.h"
#include "Ray.h"
#include "Normal.h"
#include "Point.h"
#include "RenderContext.h"
#include "HitRecord.h"
#include "Material.h"

class Ring : public Object
{
public:
	Ring () {}
	Ring (Material* _material, const Point& _center, const Normal& _normal, float _minRad, float _maxRad);
	~Ring ();
	
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const
	{
		N = normal;
	}
	
	string getName() const { return "ring"; }
	
	Point center;
	Normal normal;
	float minRad, maxRad;
};

#endif 