#include "DiskSample.h"

void DiskSample::getSamples(vector<Vector>& samples)
{
	
	float r2[samples.size()];
	float theta[samples.size()];
	
	for(int i = 0; i < samples.size(); i++)
	{
		r2[i] = ((double)i + drand48()) / (double)samples.size();
		theta[i] = ((2*M_PI)*((double)i + drand48())) / (double)samples.size();
	}

	shuffle(r2, samples.size());
	shuffle(theta, samples.size());

	for(int j = 0; j < samples.size(); j++)
	{
		samples[j].e[0] = sqrt(r2[j])*sin(theta[j]);
		samples[j].e[1] = sqrt(r2[j])*cos(theta[j]);
	}
}

void DiskSample::shuffle(float* samples, int num_samples)
{
	for(int i = num_samples - 2; i >= 0; i--)
	{
		int target = int(drand48() * (double)i);
		float temp = samples[i+1];
		samples[i+1] = samples[target];
		samples[target] = temp;
	}	
}
