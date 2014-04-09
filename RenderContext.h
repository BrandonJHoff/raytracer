#ifndef _RENDERCONTEXT_H_
#define _RENDERCONTEXT_H_

#include "Scene.h"

class Scene;

class RenderContext
{
public:
	RenderContext() {}
	RenderContext(Scene* s);
	~RenderContext();	
	const Scene* getScene() const;

	Scene* scene;
};

#endif 
