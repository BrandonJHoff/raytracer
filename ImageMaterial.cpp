#include "ImageMaterial.h"

ImageMaterial::ImageMaterial(string filename, float kd, float ka)
{
	image = new Image();
	image->read(filename);
	Kd = kd;
	Ka = ka;
}

void ImageMaterial::shade(Color& result,
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
	
	
	
	float u = record.uvw.e[0] - int(record.uvw.e[0]);
	float v = record.uvw.e[1] - int(record.uvw.e[1]);
	u *= (image->width - 3);
	v *= (image->height - 3);

	int iu = (int)u;
	int iv = (int)v;
	
	float tu = u - iu;
	float tv = v - iv;
	
	Color c = image->pixels[iu][iv]*(1-tu)*(1-tv)+
			image->pixels[iu+1][iv]*tu*(1-tv)+
			image->pixels[iu][iv+1]*(1-tu)*tv+
			image->pixels[iu+1][iv+1]*tu*tv;
	
	result *= c;
}