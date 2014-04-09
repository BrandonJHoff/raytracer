#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"

class HitRecord;
class RenderContext;

class Material
{
public:
	virtual void shade(Color& result,
					   const RenderContext& context,
					   const Ray& ray,
					   const HitRecord& record,
					   float attenuation,
					   int depth) const = 0;
	virtual string getName() const = 0;
};

#endif 