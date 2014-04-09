#ifndef _DIRECTLIGHT_H_
#define _DIRECTLIGHT_H_

#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "RenderContext.h"

class DirectLight : public Light
{
public:
	DirectLight() {}
	DirectLight(const Vector& v, const Color& c);
	~DirectLight() {}
	
	bool getLight(Color& light_color,
				  Vector& light_direction,
				  const RenderContext& context,
				  const Point& pos) const;
	
	Vector direction;
};

#endif 