#ifndef _JITTERSAMPLE_H_
#define _JITTERSAMPLE_H_

#include "Vector.h"
#include "Sample.h"
#include <vector.h>

class JitterSample: public Sample
{
public:
	JitterSample() {};
	void getSamples(vector<Vector>& samples);
};

#endif 