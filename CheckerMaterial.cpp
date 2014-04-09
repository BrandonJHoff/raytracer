#include "CheckerMaterial.h"

int Floor(float d)
{
	if(d < 0)
	{
		int i = -static_cast<int>(-d);
		if(i == d)
			return i;
		else
			return i - 1;
	}
	else
	{
		return static_cast<int>(d);
	}
	
}

CheckerMaterial::CheckerMaterial (const Point& p, const Vector& _u, const Vector& _v, Material* m1, Material* m2)
{
	origin = p;
	u = _u;
	v = _v;
	u = u / (u.length()*u.length());
	v = v / (v.length()*v.length());
	mat1 = m1;
	mat2 = m2;
}

void CheckerMaterial::shade(Color& result,
					const RenderContext& context,
					const Ray& ray,
					const HitRecord& record,
					float attenuation,
					int depth) const
{
	Point position = record.p;
	
	Vector temp = position - origin;
	
	int i1 = Floor(dot(u, temp));
	int i2 = Floor(dot(v, temp));
	
	int cell = (i1 + i2)%2;

	if(cell == 0)
		mat1->shade(result, context, ray, record, attenuation, depth);
	else
		mat2->shade(result, context, ray, record, attenuation, depth);

}