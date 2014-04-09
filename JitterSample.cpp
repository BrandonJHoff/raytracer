#include "JitterSample.h"

void JitterSample::getSamples(vector<Vector>& samples)
{
	int sqrt_samples = (int)(sqrt(samples.size()));
	for(int i = 0; i < sqrt_samples; i++)
	{
		for(int j = 0; j < sqrt_samples; j++)
		{
			float x = ((double)i + drand48()) / (double)sqrt_samples;
			float y = ((double)j + drand48()) / (double)sqrt_samples;
			samples[i*sqrt_samples + j].e[0] = x;
			samples[i*sqrt_samples + j].e[1] = y;
		}
	}
}