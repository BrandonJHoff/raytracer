#include "InfiniteAreaLight.h"

InfiniteAreaLight::InfiniteAreaLight(const Point& _center, float _radius, const Vector& tempZ, const Vector& tempX, string filename, float _scale)
{
	image = new Image();
	image->read(filename);
	center = _center;
	radius = _radius;
	Z = tempZ;
	X = tempX;
	Y = cross(Z, X);
	Z.normalize();
	X.normalize();
	Y.normalize();
	scale = _scale;
}

bool InfiniteAreaLight::getLight(Color& light_color,
						  Vector& light_direction,
						  const RenderContext& context,
						  const Point& pos) const
{
	float u1 = drand48();
	float u2 = drand48();
	
//	float z1 = 1.f - 2.f * u1;
//	float r = sqrtf(max(0.f, 1.f - z1*z1));
//	float phi1 = 2.f * M_PI * u2;
//	float x1 = r * cosf(phi1);
//	float y1 = r * sinf(phi1);
	
	float z1 = u1;
	float r = sqrtf(max(0.f, 1.f - z1*z1));
	float phi1 = 2.f * M_PI * u2;
	float x1 = r * cosf(phi1);
	float y1 = r * sinf(phi1);
		
	Point position(x1, y1, z1);
	position = position * radius;
	double x = dot(position - center, X);
	double y = dot(position - center, Y);
	double z = dot(position - center, Z);
	
	double R = sqrt(x*x + y*y + z*z);
	double theta = acos(z/R);
	double phi = atan2(y, x);
	
	double one_over_2pi = .159154943092;
	double one_over_pi = .318309886184;
	
	float u = phi*one_over_2pi;
	if(u < 0.0)
		u += 1.0;
	float v = 1 - theta*one_over_pi;
	
	u = u - int(u);
	v = v - int(v);
	u *= (image->width - 3);
	v *= (image->height - 3);
	
	int iu = (int)u;
	int iv = (int)v;
	
	float tu = u - iu;
	float tv = v - iv;
	
	Color color = image->pixels[iu][iv]*(1-tu)*(1-tv)+
		image->pixels[iu+1][iv]*tu*(1-tv)+
		image->pixels[iu][iv+1]*(1-tu)*tv+
		image->pixels[iu+1][iv+1]*tu*tv;
	
	
	light_color = color*scale;
	light_direction = position - pos;
	light_direction.normalize();
	return true;
}