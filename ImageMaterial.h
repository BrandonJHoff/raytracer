#ifndef _IMAGEMATERIAL_H_
#define _IMAGEMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Image.h"
#include <string>

class ImageMaterial : public Material
{
public:
	ImageMaterial() {}
	~ImageMaterial() {}
	ImageMaterial(string filename, float kd, float ka);
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	
	string getName() const { return "imagematerial"; }
	
	Image* image;
	float Kd;
	float Ka;
};

#endif 