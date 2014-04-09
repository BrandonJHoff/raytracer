#ifndef _TEXTUREBACKGROUND_H_
#define _TEXTUREBACKGROUND_H_

#include "Background.h"
#include "Ray.h"
#include "Color.h"
#include "RenderContext.h"
#include "Point.h"
#include "Vector.h"
#include "Image.h"

class TextureBackground: public Background
{
public:
	TextureBackground() {}
	TextureBackground(const Point& _center, float _radius, const Vector& tempZ, const Vector& tempX, string filename, float _scale);
	void getBackgroundColor(Color& result, const RenderContext& context, const Ray& ray);
	
	Point center;
	float radius, scale;
	Vector Z, Y, X;
	Image* image;
};

#endif 