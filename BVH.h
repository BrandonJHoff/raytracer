#ifndef _BVH_H_
#define _BVH_H_

#include "Object.h"
#include "RenderContext.h"
#include "HitRecord.h"
#include "Ray.h"
#include <vector>

class BVH : public Object
{
public:
	BVH() {}
	BVH(vector<Object*>& objects);
	BVH(Object* o1, Object* o2);
	~BVH();
	
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const {}
	string getName() const { return "bvh"; }
	Object* buildBranch(vector<Object*>& objects, int axis);
	void split(vector<Object*>& objects, 
			float pivot, 
			int axis, 
			vector<Object*>& leftObjects, 
			vector<Object*>& rightObjects);
	
	Object* left;
	Object* right;
};

#endif 