#ifndef _BOXFILTER_H_
#define _BOXFILTER_H_

#include "Vector.h"
#include "Filter.h"
#include <vector.h>

class BoxFilter: public Filter
{
public:
	void getFilter(vector<Vector>& samples);
};

#endif 