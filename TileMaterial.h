#ifndef _TILEMATERIAL_H_
#define _TILEMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"

class TileMaterial : public Material
{
public:
	TileMaterial () {}
	TileMaterial (const Point& p, const Vector& _u, const Vector& _v, Material* m1, Material* m2, float _gwidth, float _scale);
	~TileMaterial () {}
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	string getName() const { return "tilematerial"; }
	
	Point origin;
	Vector U,V;
	Material* mat1;
	Material* mat2;
	float gwidth, scale;
};

#endif 