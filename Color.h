#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
	Color() { e[0] = e[1] = e[2] = 0;}
	Color(float _red, float _green, float _blue) { e[0] = _red; e[1] = _green; e[2] = _blue; }
	Color(const Color& color) { *this = color;}
	~Color() {}
	
	float r() { return e[0]; }
	float g() { return e[1]; }
	float b() { return e[2]; }
	
	float max();
	
	friend Color operator+(const Color& c1, const Color& c2);
	friend Color operator-(float n, const Color& c);
	friend Color operator*(const Color& c1, const Color& c2);
	friend Color operator*(const Color& c, float s);
	friend Color operator*(float s, const Color& c);
	friend Color operator/(const Color& c, float s);
	
	Color operator+=(const Color& c);
	Color operator*=(const Color& c);
	Color operator*=(const float s);
	Color operator/=(const float s);
	
	float e[3];
};

#endif 
