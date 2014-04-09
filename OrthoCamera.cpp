#include "OrthoCamera.h"
#include <math.h>

OrthoCamera::OrthoCamera(const Point& pos, const Point& _lookAt, const Vector& up, float xsize, float ysize)
{
	position = pos;
	g = _lookAt - position;
	g.normalize();
	u = cross(g, up);
	v = cross(u, g);
	u.normalize();
	v.normalize();
	
	u = u*xsize;
	v = v*ysize;
}

void OrthoCamera::makeRay(Ray& ray,
						  const RenderContext& context,
						  double x, double y) const
{
	ray.o = position + x*u + y*v;
	ray.dir = g;
	ray.dir.normalize();
}