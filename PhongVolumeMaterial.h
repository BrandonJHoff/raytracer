#ifndef _PHONGVOLUMEMATERIAL_H_
#define _PHONGVOLUMEMATERIAL_H_

#include "Material.h"
#include "Color.h"
#include "RenderContext.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Vector.h"
#include "Colormap.h"
#include <string>

class PhongVolumeMaterial : public Material
{
public:
	PhongVolumeMaterial() {}
	~PhongVolumeMaterial() {}
	PhongVolumeMaterial(string headername, string cmapname, 
						const Point& _lower, const Point& _upper,
						double _grid_stepsize, float _maxopacity,
						float kd, float ka, const Color& _phongColor, float _n);
	void shade(Color& result,
			   const RenderContext& context,
			   const Ray& ray,
			   const HitRecord& record,
			   float attenuation,
			   int depth) const;
	string getName() const { return "phongvolumematerial"; }
	
	Colormap cmap;
	Point lower, upper;
	double grid_stepsize, world_stepsize;
	float maxopacity, Kd, Ka, exp;
	Color phongColor;
	Vector diag, cellsize;
	vector< vector < vector < short > > >  data;
	int nx, ny, nz;
};

#endif 