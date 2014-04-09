#ifndef _GROUP_H_
#define _GROUP_H_

#include "Object.h"
#include "RenderContext.h"
#include "HitRecord.h"
#include "Ray.h"
#include "BBox.h"
#include <vector>

class Group : public Object
{
public:
	Group() { haveBBox = false; }
	~Group();
	
	void addObject(Object* _object);
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const {}
	string getName() const { return "group"; }
	
	vector<Object*> objects;
	bool haveBBox;
};

#endif 