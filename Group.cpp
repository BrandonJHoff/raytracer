#include "Group.h"

Group::~Group()
{
	for(int i = 0; i < objects.size(); i++)
		delete objects[i];
	delete mat;
}

void Group::addObject(Object* _object)
{
	if(!haveBBox)
	{
		bbox = _object->bbox;
		haveBBox = true;
	}
	else
		bbox = surround(bbox, _object->bbox);
	objects.push_back(_object);
}

bool Group::hit(HitRecord& record, 
				const RenderContext& context,
				const Ray& ray) const
{
	bool hasHit = false;
	
	for(int i = 0; i < objects.size(); i++)
	{
		if(objects[i]->hit(record, context, ray))
		{
			hasHit = true;
		}
	}
	
	return hasHit;
}