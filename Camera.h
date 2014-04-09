#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Ray.h"
#include "RenderContext.h"
#include "Sample.h"

class RenderContext;

class Camera
{
public:
	virtual void makeRay(Ray& ray,
						 const RenderContext& context,
						 double x, double y, double a, double b) const = 0;

	Sample* samples;
};

#endif 
