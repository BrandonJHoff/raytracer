#ifndef _PHONGIMAGEMATERIAL_H_
#define _PHONGIMAGEMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Image.h"
#include <string>

class PhongImageMaterial : public Material
{
public:
	PhongImageMaterial() {}
	~PhongImageMaterial() {}
	PhongImageMaterial(string filename, float kd, float ka, const Color& _phongColor, float _n);
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	string getName() const { return "phongimagematerial"; }
	
	Image* image;
	float Kd;
	float Ka;
	float exp;
	Color phongColor;
};

#endif 