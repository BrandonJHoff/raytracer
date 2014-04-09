#include "LambertianMaterial.h"

LambertianMaterial::LambertianMaterial(const Color& _color, float kd, float ka)
{
	color = _color;
	Kd = kd;
	Ka = ka;
}

void LambertianMaterial::shade(Color& result,
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
			}
			else
			{
				if(temp_record.obj->mat->getName() == "dielectricmaterial")
				{
					Color tempColor;
					temp_record.obj->mat->shade(tempColor, context, shadow_ray, temp_record, attenuation, depth + 1);
					result += tempColor*(Kd * cosphi);
				}
			}
		}
	}
	
	result *= color;
}