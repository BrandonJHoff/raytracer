#ifndef _PHONGMARBLEMATERIAL_H_
#define _PHONGMARBLEMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"
#include "PerlinNoise.h"

class PhongMarbleMaterial : public Material
{
public:
	PhongMarbleMaterial() {}
	~PhongMarbleMaterial() {}
	PhongMarbleMaterial(const Color& _color1, const Color& _color2, 
						float _scale, int _octaves, float _tscale, 
						float _fscale, float _lacunarity, 
						float _gain, float kd, float ka, const Color& _phongColor, float _n);
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	string getName() const { return "phongmarblematerial"; }
	
	Color color1, color2, phongColor;
	float scale, tscale, fscale, lacunarity, gain, Kd, Ka, exp;
	int octaves;
};

#endif 