#include "PointLight.h"

PointLight::PointLight(const Point& p, const Color& c)
{
	position = p;
	color = c;
}

bool PointLight::getLight(Color& light_color,
						  Vector& light_direction,
						  const RenderContext& context,
						  const Point& pos) const
{
	light_color = color;
	light_direction = position - pos;
	light_direction.normalize();
	return true;
}