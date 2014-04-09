#include "PhongMarbleMaterial.h"

PhongMarbleMaterial::PhongMarbleMaterial(const Color& _color1, const Color& _color2, 
										 float _scale, int _octaves, float _tscale, 
										 float _fscale, float _lacunarity, 
										 float _gain, float kd, float ka, const Color& _phongColor, float _n)
{
	color1 = _color1;
	color2 = _color2;
	scale = _scale;
	octaves = _octaves;
	tscale = _tscale;
	fscale = _fscale;
	lacunarity = _lacunarity;
	gain = _gain;
	Kd = kd;
	Ka = ka;
	exp = _n;
	phongColor = _phongColor;
}

void PhongMarbleMaterial::shade(Color& result,
						  const RenderContext& context,
						  const Ray& ray,
						  const HitRecord& record,
						  float attenuation,
						  int depth) const
{
	HitRecord temp_record;
	Point position = record.p;

	Normal N;
	record.obj->getNormal(N, record, position);
	float costheta = dot(N, ray.direction());

	if(costheta > 0)
	{
		N = -N;
	}
	
	result = context.scene->ambient*Ka;
	Color speclight = Color(0, 0, 0);

	for(int i = 0; i < context.scene->lights.size(); i++)
	{
		Vector light_direction;
		Color light_color;
		context.scene->lights[i]->getLight(light_color, light_direction, context, position);
		float cosphi = dot(N, light_direction);
		Ray shadow_ray(position, light_direction);
		
		if(cosphi > 0)
		{
			temp_record.reset();
			if(!context.scene->object->hit(temp_record, context, shadow_ray))
			{
				result += light_color*(Kd * cosphi);
				
				Vector H = light_direction - ray.direction();
				H.normalize();
				float cosalpha = dot(H, N);
				if(cosalpha > 0)
					speclight += light_color * pow(cosalpha, exp);
			}
		}
	}
	
	Point T = position*scale*fscale;
	double value = cos(record.uvw.e[0]*scale + tscale*turbulenceAbs(octaves, Point(T.x(), T.y(), T.z()), lacunarity, gain));
	value = value*0.5 + 0.5;
	Color c = color1*(1 - value) + color2*value;
	
	result *= c;
	result += speclight * phongColor;
}