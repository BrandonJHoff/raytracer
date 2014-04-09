#ifndef _CHECKERMATERIAL_H_
#define _CHECKERMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"

class CheckerMaterial : public Material
{
public:
	CheckerMaterial () {}
	CheckerMaterial (const Point& p, const Vector& _u, const Vector& _v, Material* m1, Material* m2);
	~CheckerMaterial () {}
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	string getName() const { return "checkermaterial"; }
	
	Point origin;
	Vector u,v;
	Material* mat1;
	Material* mat2;
};

#endif 