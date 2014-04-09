#ifndef _HEIGHTFIELD_H_
#define _HEIGHTFIELD_H_

#include "Object.h"
#include "Ray.h"
#include "Vector.h"
#include "Point.h"
#include "HitRecord.h"
#include "RenderContext.h"
#include "Material.h"
#include "Normal.h"
#include "Box.h"

class Heightfield : public Object
{
public:
	Heightfield(Material* _material, string filename, const Point& _min, const Point& _max);
	~Heightfield();
	bool hit(HitRecord& record, 
			 const RenderContext& context,
			 const Ray& ray) const;
	void getNormal(Normal& N, const HitRecord& record, const Point& pos) const;
	void readData(string filename);
	float Min(float f1, float f2) const;
	float Max(float f1, float f2) const;
	string getName() const { return "heightfield"; }
	
	Point Pmin, Pmax;
	Box* boundingBox;
	Vector D, cellsize;
	double minz, maxz;
	int nx, ny;
	float** data;
	float* p;
};

#endif 