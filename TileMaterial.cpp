#include "TileMaterial.h"

TileMaterial::TileMaterial (const Point& p, const Vector& _u, const Vector& _v, Material* m1, Material* m2, float _gwidth, float _scale)
{
	origin = p;
	U = _u;
	U = U/(U.length() * U.length());
	V = _v;
	V = V/(V.length() * V.length());
	mat1 = m1;
	mat2 = m2;
	gwidth = _gwidth;
	scale = _scale;
}

void TileMaterial::shade(Color& result,
					const RenderContext& context,
					const Ray& ray,
					const HitRecord& record,
					float attenuation,
					int depth) const
{
	Point position = record.p;
	
	Vector temp = position - origin;
	
	int i1 = floor(dot(U, temp));
	int i2 = floor(dot(V, temp));
	
	int cell = (i1 + i2)%2;
	
	if(cell == 0)
		mat1->shade(result, context, ray, record, attenuation, depth);
	else
		mat2->shade(result, context, ray, record, attenuation, depth);
	
	
//	float u = temp.e[0];
//	float v = temp.e[1];
////	float u = record.uvw.e[0];
////	float v = record.uvw.e[1];
//	float s = u*scale - int(u*scale);
//	float t = v*scale - int(v*scale);
//	
//	if((s < gwidth) || (t < gwidth))
//		mat1->shade(result, context, ray, record, attenuation, depth);
//	else
//		mat2->shade(result, context, ray, record, attenuation, depth);

}