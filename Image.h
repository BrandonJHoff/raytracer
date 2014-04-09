#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <math.h>
#include <string>
#include <fstream>
#include "Color.h"

using namespace std;

class Image
{
public:
	Image();
	~Image();
	Image(int _width, int _height);
	Image(int _width, int _height, Color background);
	bool set(int x, int y, const Color& color);
	void write(string filename);
	void read(string filename);
	void bloom(float bloomRadius, float bloomWeight, int xres, int yres);
	Color Lerp(float t, Color& c1, Color& c2);
	
	int width;
	int height;
	Color** pixels;
};

#endif 
