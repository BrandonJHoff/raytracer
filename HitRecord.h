#ifndef _HITRECORD_H_
#define _HITRECORD_H_

#include "Object.h"
#include "Point.h"
#include "Normal.h"
#include "Vector.h"
#include "Ray.h"
#include "Material.h"
#include <assert.h>

#define MAXSIZE 400

class Object;
class Material;

class HitRecord
{
public:
	HitRecord();
	~HitRecord();
	void reset() 
	{ t = 100000.0; obj = NULL; mat = NULL; }
	bool hit(double hit_t, const Object* hit_obj, const Ray& ray);
	template<typename T> T* getScratchpad() const { assert(sizeof(T) <= MAXSIZE); return (T*)(data); }
	
	double t;
	Vector uvw;
	Point p;
	Normal n;
	const Object* obj;
	const Material* mat;
	char data[MAXSIZE];
};

#endif 