#include "TentFilter.h"

void TentFilter::getFilter(vector<Vector>& samples)
{
	for(int i = 0; i < samples.size(); i++)
	{
		float x = samples[i].x();
		float y = samples[i].y();
		
		if(x < 0.5)
			samples[i].e[0] = sqrt(2.0 * x) - 1.0;
		else
			samples[i].e[0] = 1.0 - sqrt(2.0 - 2.0 * x);
		
		if(y < 0.5)
			samples[i].e[1] = sqrt(2.0 * y) - 1.0;
		else
			samples[i].e[1] = 1.0 - sqrt(2.0 - 2.0 * y);
	}
}