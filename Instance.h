#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include "Object.h"
#include "RenderContext.h"
#include "HitRecord.h"
#include "Ray.h"
#include "BBox.h"
#include "Matrix.h"
#include "Material.h"
#include <vector>

class Instance : public Object
{
public:
	Instance() {}
	Instance(Matrix trans, Object* _obj);
	~Instance();
	
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const;
	void calculateBBox();
	float Min(float f1, float f2);
	float Max(float f1, float f2);
	string getName() const { return "instance"; }
	
	Object* obj;
	Matrix M, Minv;
};

#endif 