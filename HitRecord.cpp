#include "HitRecord.h"

HitRecord::HitRecord()
{
	obj = NULL;
	t = 100000.0;
	mat = NULL;
}

HitRecord::~HitRecord()
{
	//delete obj;
}

bool HitRecord::hit(double hit_t, const Object* hit_obj, const Ray& ray)
{
	if((hit_t > .001) && (hit_t < t))
	{
		t = hit_t;
		obj = hit_obj;
		p = ray.point(t);
		mat = hit_obj->mat;
		return true;
	}
	return false;
}