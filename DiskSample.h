#ifndef _DISKSAMPLE_H_
#define _DISKSAMPLE_H_

#include "Vector.h"
#include "Sample.h"
#include <vector.h>

class DiskSample: public Sample
{
public:
	DiskSample() {};
	void getSamples(vector<Vector>& samples);
	void shuffle(float* samples, int num_samples);
};

#endif 