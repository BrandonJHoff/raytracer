#ifndef _PHONGMATERIAL_H_
#define _PHONGMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"

class PhongMaterial : public Material
{
public:
	PhongMaterial() {}
	~PhongMaterial() {}
	PhongMaterial(const Color& _color, float kd, float ka, const Color& _phongColor, float _n);
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	string getName() const { return "phongmaterial"; }
	
	Color color;
	float Kd;
	float Ka;
	float exp;
	Color phongColor;
};

#endif 