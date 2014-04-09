#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "Ray.h"
#include "Color.h"
#include "RenderContext.h"

class RenderContext;

class Background
{
public:
	virtual void getBackgroundColor(Color& result,
									const RenderContext& context,
									const Ray& ray) = 0;
};

#endif 
