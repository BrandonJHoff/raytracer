#ifndef _INFINITEAREALIGHT_H_
#define _INFINITEAREALIGHT_H_

#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "RenderContext.h"
#include "Image.h"
#include <string>

class InfiniteAreaLight : public Light
{
public:
	InfiniteAreaLight() {}
	InfiniteAreaLight(const Point& _center, float _radius, const Vector& tempZ, const Vector& tempX, string filename, float _scale);
	~InfiniteAreaLight() {}
	
	bool getLight(Color& light_color,
				  Vector& light_direction,
				  const RenderContext& context,
				  const Point& pos) const;
	
	Point center;
	float radius, scale;
	Vector Z, Y, X;
	Image* image;
};

#endif 