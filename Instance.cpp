#include "Instance.h"

Instance::Instance(Matrix trans, Object* _obj)
{
	M = trans;
	Minv = trans;
	Minv.invert();
	obj = _obj;
	mat = obj->mat;
	
	bbox = obj->bbox;

	calculateBBox();
}

bool Instance::hit(HitRecord& record, 
				const RenderContext& context,
				const Ray& ray) const
{
	Point no = transformLoc(Minv, ray.origin());
	Vector nd = transformVec(Minv, ray.direction());
	
	Ray tray(no, nd);
	
	if(obj->hit(record, context, tray))
	{
		
		record.p = transformLoc(M, record.p);
		Normal N;
		record.obj->getNormal(N, record, record.p);
		N.normalize();
		record.n = transformVec(Minv.getTranspose(), N);
		record.n.normalize();
		record.obj = this;
		return true;
	}
	else
	{
		return false;
	}
}

void Instance::getNormal(Normal& N, const HitRecord& record, const Point& pos) const
{
	N = record.n;
}

void Instance::calculateBBox()
{
	Point p1, p2, p3, p4, p5, p6, p7, p8;

	p1 = Point(bbox.min.x(), bbox.min.y(), bbox.min.z());
	p2 = Point(bbox.max.x(), bbox.min.y(), bbox.min.z());
	p3 = Point(bbox.max.x(), bbox.max.y(), bbox.min.z());
	p4 = Point(bbox.min.x(), bbox.max.y(), bbox.min.z());
	p5 = Point(bbox.min.x(), bbox.min.y(), bbox.max.z());
	p6 = Point(bbox.max.x(), bbox.min.y(), bbox.max.z());
	p7 = Point(bbox.max.x(), bbox.max.y(), bbox.max.z());
	p8 = Point(bbox.min.x(), bbox.max.y(), bbox.max.z());

	p1 = transformLoc(M, p1);
	p2 = transformLoc(M, p2);
	p3 = transformLoc(M, p3);
	p4 = transformLoc(M, p4);
	p5 = transformLoc(M, p5);
	p6 = transformLoc(M, p6);
	p7 = transformLoc(M, p7);
	p8 = transformLoc(M, p8);

	float minX, minY, minZ, maxX, maxY, maxZ;
	
	minX = Min(Min(Min(p1.x(), p2.x()), Min(p3.x(), p4.x())), Min(Min(p5.x(), p6.x()), Min(p7.x(), p8.x())));
	minY = Min(Min(Min(p1.y(), p2.y()), Min(p3.y(), p4.y())), Min(Min(p5.y(), p6.y()), Min(p7.y(), p8.y())));
	minZ = Min(Min(Min(p1.z(), p2.z()), Min(p3.z(), p4.z())), Min(Min(p5.z(), p6.z()), Min(p7.z(), p8.z())));

	maxX = Max(Max(Max(p1.x(), p2.x()), Max(p3.x(), p4.x())), Max(Max(p5.x(), p6.x()), Max(p7.x(), p8.x())));
	maxY = Max(Max(Max(p1.y(), p2.y()), Max(p3.y(), p4.y())), Max(Max(p5.y(), p6.y()), Max(p7.y(), p8.y())));
	maxZ = Max(Max(Max(p1.z(), p2.z()), Max(p3.z(), p4.z())), Max(Max(p5.z(), p6.z()), Max(p7.z(), p8.z())));

	bbox = BBox(Point(minX, minY, minZ), Point(maxX, maxY, maxZ));
}

float Instance::Min(float f1, float f2)
{
	if(f1 < f2)
		return f1;
	return f2;
}

float Instance::Max(float f1, float f2)
{
	if(f1 > f2)
		return f1;
	return f2;
}