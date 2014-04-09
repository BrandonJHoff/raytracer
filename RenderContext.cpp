#include "RenderContext.h"

RenderContext::RenderContext(Scene* s)
	{ 
		scene = s; 
	}

RenderContext::~RenderContext()
{
	delete scene;
}

const Scene* RenderContext::getScene() const
	{
		return scene;
	}
	