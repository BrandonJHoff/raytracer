#ifndef _LAMBERTIANMATERIAL_H_
#define _LAMBERTIANMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"

class LambertianMaterial : public Material
{
public:
	LambertianMaterial() {}
	~LambertianMaterial() {}
	LambertianMaterial(const Color& _color, float kd, float ka);
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	
	string getName() const { return "lambertianmaterial"; }
	
	Color color;
	float Kd;
	float Ka;
};

#endif 