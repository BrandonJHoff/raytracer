#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "RenderContext.h"

class RenderContext;

class Light
{
public:
	virtual bool getLight(Color& light_color,
						  Vector& light_direction,
						  const RenderContext& context,
						  const Point& pos) const = 0;
	
	Color color;
};

#endif 
