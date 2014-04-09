#include "CubicSplineFilter.h"

void CubicSplineFilter::getFilter(vector<Vector>& samples)
{
	for(int i = samples.size() - 2; i >=0; i--)
	{
		float x = samples[i].x();
		float y = samples[i].y();
		
		samples[i].e[0] = cubicFilter(x);
		samples[i].e[1] = cubicFilter(y);
	}
}

float CubicSplineFilter::solve(float r)
{
	float u = r;
	for(int i = 0; i < 5; i++)
	{
		u = (11.0 * r + u * u * (6.0 + u * (8.0 - 9.0 * u))) / (4.0 + 12.0 * u * (1.0 + u * (1.0 - u)));
		return u;
	}
}

float CubicSplineFilter::cubicFilter(float x)
{
	if(x < 1.0 / 24.0)
		return pow(24 * x, 0.25) - 2.0;
	else if(x < 0.5)
		return solve(24.0 * (x - 1.0 / 24.0) / 11.0) - 1.0;
	else if( x < 23.0 / 24.0)
		return 1.0 - solve(24.0 * (23.0 / 24.0 - x) / 11.0);
	else
		return 2 - pow(24.0 * (1.0 - x), 0.25);
}