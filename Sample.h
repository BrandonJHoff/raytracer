#ifndef _SAMPLE_H_
#define _SAMPLE_H_

#include "Vector.h"
#include <vector.h>

class Sample
{
public:
	virtual void getSamples(vector<Vector>& samples) = 0;
};

#endif 