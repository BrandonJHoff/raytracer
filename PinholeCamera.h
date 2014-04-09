#ifndef _PINHOLECAMERA_H_
#define _PINHOLECAMERA_H_

#include "Ray.h"
#include "RenderContext.h"
#include "Point.h"
#include "Vector.h"

class PinholeCamera : public Camera
{
public:
	PinholeCamera() {}
	PinholeCamera(const Point& pos, const Point& lookAt, const Vector& up, float angle, float aspect);
	~PinholeCamera() {}
	
	void makeRay(Ray& ray,
				 const RenderContext& context,
				 double x, double y, double a, double b) const;
	
	Point position;
	Vector g, u, v;
};

#endif 