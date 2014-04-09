#ifndef _ORTHOCAMERA_H_
#define _ORTHOCAMERA_H_

#include "Ray.h"
#include "RenderContext.h"
#include "Point.h"
#include "Vector.h"

class OrthoCamera : public Camera
{
public:
	OrthoCamera() {}
	OrthoCamera(const Point& pos, const Point& _lookAt, const Vector& up, float xsize, float ysize);
	~OrthoCamera() {}
	
	void makeRay(Ray& ray,
				 const RenderContext& context,
				 double x, double y) const;
	
	Point position;
	Vector g, u, v;
};

#endif 