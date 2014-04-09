#include "ThinLensCamera.h"
#include <math.h>

ThinLensCamera::ThinLensCamera(const Point& pos, const Point& lookAt, const Vector& up, float angle, float aspect, float _distance, float aperture)
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

	lens_radius = aperture/2.0;
	distance = _distance;

	samples = new DiskSample();
}

void ThinLensCamera::makeRay(Ray& ray,
					const RenderContext& context,
					double x, double y, double a, double b) const
{
	ray.o = position;
	ray.dir = g + x*u + y*v;
	ray.dir.normalize();

	ray.dir = ray.dir * distance;

	Vector lensU = a*lens_radius*u;
	Vector lensV = b*lens_radius*v;

	ray.o = ray.o + (lensU + lensV);
	ray.dir -= lensU + lensV;

	ray.dir.normalize();
}