#include "Image.h"
#include <iostream>

Image::Image()
{}

Image::~Image()
{}

Image::Image(int _width, int _height)
{
	width = _width;
	height = _height;
	
	pixels = new Color*[width];
	for(int i = 0; i < width; i++)
	{
		pixels[i] = new Color[height];
	}
}

Image::Image(int _width, int _height, Color background)
{
	width = _width;
	height = _height;
	
	pixels = new Color*[width];
	for(int i = 0; i < width; i++)
	{
		pixels[i] = new Color[height];
	
		for(int j = 0; j < height; j++)
		{
			pixels[i][j] = background;
		}
	}
}

bool Image::set(int x, int y, const Color& color)
{
	if(0 > x || x > width) return false;
	if(0 > y || y > height) return false;
	
	pixels[x][y] = color;
	return true;
}

void Image::write(string filename)
{
	ofstream out;
	out.open(filename.c_str());
	
	out << "P6\n";
	out << width << ' ' << height << '\n';
	out << "255\n";
	
	int i, j;
	unsigned int ired, igreen, iblue;
	unsigned char red, green, blue;
	
	for(i = height-1; i >= 0; i--)
	{
		for(j = 0; j < width; j++)
		{
			ired = (unsigned int)(256.0 * pixels[j][i].r());
			igreen = (unsigned int)(256.0 * pixels[j][i].g());
			iblue = (unsigned int)(256.0 * pixels[j][i].b());
			if(ired > 255) ired = 255;
			if(igreen > 255) igreen = 255;
			if(iblue > 255) iblue = 255;
			red = (unsigned char) ired;
			green = (unsigned char)(igreen);
			blue = (unsigned char)(iblue);
			out.put(red);
			out.put(green);
			out.put(blue);
		}
	}
	
	out.close();	
}

void Image::read(string filename)
{
	ifstream in;
	in.open(filename.c_str());
	if(!in.is_open())
	{
		cerr << " ERROR -- Couldn't open file \'" << filename << "\'." << endl;
		exit(-1);
	}
	
	char ch, type;
	char red, green, blue;
	int i, j, cols, rows;
	int num;
	
	in.get(ch);
	in.get(type);
	in >> cols >> rows >> num;
	
	width = cols;
	height = rows;
	
	pixels = new Color*[width];
	for(i = 0; i < width; i++)
		pixels[i] = new Color[height];
	
	in.get(ch);
	
	for(i = height-1; i >= 0; i--)
		for(j = 0; j < width; j++)
		{
			in.get(red);
			in.get(green);
			in.get(blue);
			pixels[j][i] = Color((float)((unsigned char)red)/255.0, 
								 (float)((unsigned char)green)/255.0,
								 (float)((unsigned char)blue)/255.0);
		}
}

void Image::bloom(float bloomRadius, float bloomWeight, int xres, int yres)
{
	if(bloomRadius > 0.0 && bloomWeight > 0.0)
	{
		int maxRes = 0;
		if(xres > yres)
			maxRes = xres;
		else
			maxRes = yres;
		int bloomSupport = (int)(bloomRadius * maxRes);
		int bloomWidth = bloomSupport / 2;
		
		float *bloomFilter = new float[bloomWidth * bloomWidth];
		for(int i = 0; i < bloomWidth * bloomWidth; ++i)
		{
			float dist = sqrt((float)(i) / (float)(bloomWidth));
			float maxf = 0;
			if(0.0 > (1.0 - dist))
				maxf = 0.0;
			else
				maxf = 1.0 - dist;
			bloomFilter[i] = powf(maxf, 4.0);
		}
		
		int x, y;
		
		Color **bloomImage;
		bloomImage = new Color*[xres];
		for(x = 0; x < xres; x++)
		{
			bloomImage[x] = new Color[yres];
		}
		
		int count = 0;
		int percent = xres*yres/100;
		int percent_done = 0;
	
		for(y = 0; y < yres; ++y)
		{
			for(x = 0; x < xres; ++x)
			{
				if((count % percent) == 0)
				{
					cout << percent_done << "% done" << endl;
					percent_done++;
				}
				
				count++;
				
				int x0 = max(0, x - bloomWidth);
				int x1 = min(x + bloomWidth, xres - 1);
				int y0 = max(0, y - bloomWidth);
				int y1 = min(y + bloomWidth, yres - 1);
				
				float sumWt = 0.0;
				
				for(int by = y0; by <= y1; ++by)
				{
					for(int bx = x0; bx <= x1; ++bx)
					{
						int dx = x - bx;
						int dy = y - by;
						if(dx == 0 && dy == 0)
							break;
						int dist2 = dx*dx + dy*dy;
						if(dist2 < bloomWidth * bloomWidth)
						{
							float wt = bloomFilter[dist2];
							sumWt += wt;
							bloomImage[x][y] += wt * pixels[bx][by];
						}
					}
				}
				
				bloomImage[x][y] /= sumWt;
			}
		}
		
		for(y = 0; y < yres; ++y)
		{
			for(x = 0; x < xres; ++x)
			{
				pixels[x][y] = Lerp(bloomWeight, pixels[x][y], bloomImage[x][y]);
			}
		}
	}
}

Color Image::Lerp(float t, Color& c1, Color& c2)
{
	return (1.0 - t) * c1 + t * c2;
}