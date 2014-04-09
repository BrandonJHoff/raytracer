#ifndef _DISK_H_
#define _DISK_H_

#include "Object.h"
#include "Ray.h"
#include "Normal.h"
#include "Point.h"
#include "RenderContext.h"
#include "HitRecord.h"
#include "Material.h"

class Disk : public Object
{
public:
	Disk() {}
	Disk(Material* _material, const Point& _center, const Normal& _normal, float _radius);
	~Disk();
	
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const
	{
		N = normal;
	}
	string getName() const { return "disk"; }
	
	Point center;
	Normal normal;
	float radius;
};

#endif 