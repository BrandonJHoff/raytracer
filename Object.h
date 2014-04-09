#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Ray.h"
#include "RenderContext.h"
#include "HitRecord.h"
#include "Material.h"
#include "Normal.h"
#include "Point.h"
#include "BBox.h"
#include <string>

using namespace std;

class Material;
class HitRecord;
class RenderContext;

class Object
{
public:
	virtual bool hit(HitRecord& record, 
					 const RenderContext& context,
					 const Ray& ray) const = 0;
	virtual void getNormal(Normal& N, const HitRecord& record, const Point& pos) const = 0;
	virtual string getName() const = 0;
	
	Material* mat;
	BBox bbox;
};

#endif 
