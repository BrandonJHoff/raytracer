#include "PinholeCamera.h"
#include <math.h>

PinholeCamera::PinholeCamera(const Point& pos, const Point& lookAt, const Vector& up, float angle, float aspect)
{
	float PI = 3.14159265;
	
	position = pos;

	g = lookAt - position;
	g.normalize();
	u = cross(g, up);
	v = cross(u, g);
	
	u.normalize();
	v.normalize();
	u = u*tan((angle/2.0)*PI/180.0);
	v = v*tan((angle/2.0)*PI/180.0)/aspect;

	samples = NULL;
}

void PinholeCamera::makeRay(Ray& ray,
							const RenderContext& context,
							double x, double y, double a, double b) const
{
	ray.o = position;
	ray.dir = g + x*u + y*v;
	ray.dir.normalize();
}