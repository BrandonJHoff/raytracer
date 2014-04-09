#include "BoxFilter.h"

void BoxFilter::getFilter(vector<Vector>& samples)
{
	for(int i = samples.size() - 2; i >=0; i--)
	{
		samples[i].e[0] = samples[i].x() - 0.5;
		samples[i].e[1] = samples[i].y() - 0.5;
	}
}