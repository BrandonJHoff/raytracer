#include "DielectricMaterial.h"

DielectricMaterial::DielectricMaterial(double _index, float _n)
{
	index = _index;
	exp = _n;
	float temp = (index - 1.0)/(index + 1.0);
	temp *= temp;
	R0 = Color(temp, temp, temp);
}

void DielectricMaterial::shade(Color& result,
						  const RenderContext& context,
						  const Ray& ray,
						  const HitRecord& record,
						  float attenuation,
						  int depth) const
{
	Point position = record.p;
	
	Normal N;
	record.obj->getNormal(N, record, position);
	
	Color speclight = Color(0, 0, 0);
	Vector light_direction;
	Color light_color;
	HitRecord temp_record;
	
	for(int i = 0; i < context.scene->lights.size(); i++)
	{
		context.scene->lights[i]->getLight(light_color, light_direction, context, position);
		float cosphi = dot(N, light_direction);
				
		if(cosphi > 0)
		{
			Ray shadow_ray(position, light_direction);
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
	
	result = speclight * Color(1,1,1);
	
	float costheta = dot(N, ray.dir);
	float indexTemp;
	bool entering = false;
	
	if(costheta > 0)
	{
		indexTemp = 1.0/index;
		N = -N;
	}
	else
	{
		entering = true;
		indexTemp = index;
		costheta = -costheta;
	}
	
	if((depth < context.scene->maxDepth) && (attenuation > context.scene->attenuation))
	{
		float costheta2 = 1 + (costheta*costheta - 1)/(indexTemp*indexTemp);
		
		if(costheta2 < 0)
		{
			Color Fr = R0 + (1 - R0)*pow((1 - costheta), 5);
			Vector reflect_direction = ray.direction() + (2*costheta)*N;
			Ray reflect_ray(position, reflect_direction);
			Color reflect_color;
			context.scene->background->getBackgroundColor(reflect_color, context, reflect_ray);
			
			temp_record.reset();
			if(context.scene->object->hit(temp_record, context, reflect_ray))
			{
				temp_record.mat->shade(reflect_color, context, reflect_ray, temp_record, Fr.max()*attenuation, depth + 1);
			}
			
			if(!entering)
				result += reflect_color;
		}
		else
		{
			costheta2 = sqrt(costheta2);
			float cosm = costheta;
			if(cosm > costheta2)
				cosm = costheta2;
			
			Color Fr = R0 + (1 - R0)*pow((1-cosm), 5);
			Vector reflect_direction = ray.direction() + (2*costheta)*N;
			Ray reflect_ray(position, reflect_direction);
			Color reflect_color;
			context.scene->background->getBackgroundColor(reflect_color, context, reflect_ray);
			
			temp_record.reset();
			if(context.scene->object->hit(temp_record, context, reflect_ray))
			{
				temp_record.mat->shade(reflect_color, context, reflect_ray, temp_record, Fr.max()*attenuation, depth + 1);
			}
			
			result += reflect_color * Fr;
			
			Color Ft = 1 - Fr;
			
			Vector transp_direction = (1/indexTemp)*ray.dir + N*((costheta/indexTemp) - costheta2);
			Ray transp_ray(position, transp_direction);
			Color transp_color;
			context.scene->background->getBackgroundColor(transp_color, context, transp_ray);
			
			temp_record.reset();
			if(context.scene->object->hit(temp_record, context, transp_ray))
			{
				temp_record.mat->shade(transp_color, context, transp_ray, temp_record, Ft.max()*attenuation, depth + 1);
			}
			
			result += transp_color * Ft;
			
		}
	}
	
}