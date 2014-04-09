
#ifndef PerlinNoise_h
#define PerlinNoise_h

#include "Point.h"
#include "math.h"

double perlinNoise(const Point& p);
double turbulence(int octaves, const Point& p, double lacunarity, double gain);
double turbulenceAbs(int octaves, const Point& p, double lacunarity, double gain);

#endif
