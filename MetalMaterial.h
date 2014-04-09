#ifndef _METALMATERIAL_H_
#define _METALMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"

class MetalMaterial : public Material
{
public:
	MetalMaterial() {}
	~MetalMaterial() {}
	MetalMaterial(const Color& _color,float _n);
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	string getName() const { return "metalmaterial"; }
	
	Color R0;
	float exp;
};

#endif 