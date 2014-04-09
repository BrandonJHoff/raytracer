#ifndef _THINLENSCAMERA_H_
#define _THINLENSCAMERA_H_

#include "Ray.h"
#include "RenderContext.h"
#include "Point.h"
#include "Vector.h"
#include "DiskSample.h"

class ThinLensCamera : public Camera
{
public:
	ThinLensCamera () {}
	ThinLensCamera (const Point& pos, const Point& lookAt, const Vector& up, float angle, float aspect, float _distance, float aperture);
	~ThinLensCamera () {}
	
	void makeRay(Ray& ray,
				 const RenderContext& context,
				 double x, double y, double a, double b) const;
	
	Point position;
	Vector g, u, v;
	float lens_radius, distance;
};

#endif 