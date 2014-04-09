#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "RenderContext.h"

class PointLight : public Light
{
public:
	PointLight() {}
	PointLight(const Point& p, const Color& c);
	~PointLight() {}
	
	bool getLight(Color& light_color,
				  Vector& light_direction,
				  const RenderContext& context,
				  const Point& pos) const;
	
	Point position;
};

#endif 