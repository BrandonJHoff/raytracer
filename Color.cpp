#include "Color.h"

float Color::max()
{
	if((e[0] > e[1]) && (e[0] > e[2]))
		return e[0];
	else if(e[1] > e[2])
		return e[1];
	else
		return e[2];
}

Color operator+(const Color& c1, const Color& c2)
{
	return Color(c1.e[0] + c2.e[0], c1.e[1] + c2.e[1], c1.e[2] + c2.e[2]);
}

Color operator-(float n, const Color& c)
{
	return Color(n - c.e[0], n - c.e[1], n - c.e[2]);
}


Color operator*(const Color& c1, const Color& c2)
{
	return Color(c1.e[0] * c2.e[0], c1.e[1] * c2.e[1], c1.e[2] * c2.e[2]);
}

Color operator*(const Color& c, float s)
{
	return Color(c.e[0]*s, c.e[1]*s, c.e[2]*s);
}

Color operator*(float s, const Color& c)
{
	return Color(c.e[0]*s, c.e[1]*s, c.e[2]*s);
}

Color operator/(const Color& c, float s)
{
	return Color(c.e[0]/s, c.e[1]/s, c.e[2]/s);
}

Color Color::operator+=(const Color& c)
{
	*this = *this + c;
	return *this;
}

Color Color::operator*=(const Color& c)
{
	*this = *this * c;
	return *this;
}


Color Color::operator*=(const float s)
{
	*this = *this * s;
	return *this;
}

Color Color::operator/=(const float s)
{
	*this = *this / s;
	return *this;
}
