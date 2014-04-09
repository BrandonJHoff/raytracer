#ifndef _FILTER_H_
#define _FILTER_H_

#include "Vector.h"
#include <vector.h>

class Filter
{
public:
	virtual void getFilter(vector<Vector>& samples) = 0;
};

#endif 