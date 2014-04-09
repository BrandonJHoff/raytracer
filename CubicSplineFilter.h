#ifndef _CUBICSPLINEFILTER_H_
#define _CUBICSPLINEFILTER_H_

#include "Vector.h"
#include "Filter.h"
#include <vector.h>

class CubicSplineFilter: public Filter
{
public:
	CubicSplineFilter() {}
	void getFilter(vector<Vector>& samples);
	float solve(float r);
	float cubicFilter(float x);
};

#endif 