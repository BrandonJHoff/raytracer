#ifndef _DIELECTRICMATERIAL_H_
#define _DIELECTRICMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"

class DielectricMaterial : public Material
{
public:
	DielectricMaterial() {}
	~DielectricMaterial() {}
	DielectricMaterial(double _index, float _n);
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	string getName() const { return "dielectricmaterial"; }
	
	double index;
	float exp;
	Color R0;
};

#endif 