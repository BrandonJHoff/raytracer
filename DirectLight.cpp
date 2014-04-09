#include "DirectLight.h"

DirectLight::DirectLight(const Vector& v, const Color& c)
{
	direction = v;
	direction.normalize();
	color = c;
}

bool DirectLight::getLight(Color& light_color,
						  Vector& light_direction,
						  const RenderContext& context,
						  const Point& pos) const
{
	light_color = color;
	light_direction = -direction;
	light_direction.normalize();
	return true;
}