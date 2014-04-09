#include "MetalMaterial.h"

MetalMaterial::MetalMaterial(const Color& _color, float _n)
{
	R0 = _color;
	exp = _n;
}

void MetalMaterial::shade(Color& result,
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
	else
	{
		costheta = -costheta;
	}
	
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
				Vector H = light_direction - ray.direction();
				H.normalize();
				float cosalpha = dot(H, N);
				if(cosalpha > 0)
					speclight += light_color * pow(cosalpha, exp);
			}
		}
	}
	
	result = speclight * R0;
	
	if((depth < context.scene->maxDepth) && (attenuation > context.scene->attenuation))
	{
		Color Fr = R0 + (1 - R0)*pow((1 - costheta), 5);
		Vector reflect_direction = ray.direction() + 2*costheta*N;
		Ray reflect_ray(position, reflect_direction);
		Color reflect_color;
		context.scene->background->getBackgroundColor(reflect_color, context, reflect_ray);
		
		temp_record.reset();
		if(context.scene->object->hit(temp_record, context, reflect_ray))
		{
			temp_record.mat->shade(reflect_color, context, reflect_ray, temp_record, Fr.max()*attenuation, depth + 1);
		}
		
		result += Fr * reflect_color;
	}
}