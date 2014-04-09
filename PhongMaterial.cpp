#include "PhongMaterial.h"

PhongMaterial::PhongMaterial(const Color& _color, float kd, float ka, const Color& _phongColor, float _n)
{
	color = _color;
	Kd = kd;
	Ka = ka;
	exp = _n;
	phongColor = _phongColor;
}

void PhongMaterial::shade(Color& result,
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
	
	result *= color;
	result += speclight * phongColor;
}