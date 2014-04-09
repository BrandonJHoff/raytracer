#ifndef _CONSTANTBACKGROUND_H_
#define _CONSTANTBACKGROUND_H_

#include "Background.h"
#include "Ray.h"
#include "Color.h"
#include "RenderContext.h"

class ConstantBackground: public Background
{
public:
	ConstantBackground() {}
	ConstantBackground(const Color& _color)
	{ color = _color; }
	void getBackgroundColor(Color& result,
							const RenderContext& context,
							const Ray& ray)
	{ result = color; }
	
	Color color;
};

#endif 