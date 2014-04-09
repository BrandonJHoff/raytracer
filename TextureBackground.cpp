#include "TextureBackground.h"

TextureBackground::TextureBackground(const Point& _center, float _radius, const Vector& tempZ, const Vector& tempX, string filename, float _scale)
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

void TextureBackground::getBackgroundColor(Color& result, const RenderContext& context, const Ray& ray)
{
	bool hasHit = false;
	Vector temp = ray.origin() - center;
	
	double a = dot( ray.direction(), ray.direction() );
	double b = 2.0*dot( ray.direction(), temp );
	double c = dot(temp, temp) - radius*radius;
	
	double discriminant = b*b - 4.0*a*c;
	
	double t = 100000.0;
	
	if(discriminant > 0.0)
	{
		discriminant = sqrt(discriminant);
		double t1 = ( -b - discriminant) / (2.0*a);
		double t2 = (-b + discriminant) / (2.0*a);

		if((t1 > 0.001) && (t1 < t))
		{
			t = t1;
			hasHit = true;
		}
	
		if((t2 > 0.001) && (t2 < t))
		{
			t = t2;
			hasHit = true;
		}
	}
	else
	{
		result = Color(0, 0, 0);
		return;
	}
	
	if(!hasHit)
	{
		result = Color(0, 0, 0);
		return;
	}
	
	Point p = ray.point(t);
	double x = dot(p - center, X);
	double y = dot(p - center, Y);
	double z = dot(p - center, Z);
	
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
	
	result = color*scale;	
}
