#ifndef _TENTFILTER_H_
#define _TENTFILTER_H_

#include "Vector.h"
#include "Filter.h"
#include <vector.h>

class TentFilter: public Filter
{
public:
	void getFilter(vector<Vector>& samples);
};

#endif 