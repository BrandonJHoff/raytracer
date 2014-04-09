#include "Normal.h"

Normal::Normal(float x, float y, float z)
{
	e[0] = x; 
	e[1] = y;
	e[2] = z;
}

float Normal::length()
{
	return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
}

void Normal::normalize()
{
	*this = *this / (*this).length();
}

ostream& operator<<(ostream& os, const Normal& n)
{
	os << "(" << n.e[0] << " " << n.e[1] << " " << n.e[2] << ")";
	return os;
}


bool operator==(const Normal& n1, const Normal& n2)
{
	if(n1.e[0] != n2.e[0]) return false;
	if(n1.e[1] != n2.e[1]) return false;
	if(n1.e[2] != n2.e[2]) return false;
	return true;
}

bool operator!=(const Normal& n1, const Normal& n2)
{
	return !(n1 == n2);
}
	
Vector operator+(const Normal& n, const Vector& v)
{
	return Vector(n.e[0] + v.e[0], n.e[1] + v.e[1], n.e[2] + v.e[2]);
}

Vector operator+(const Vector& v, const Normal& n)
{
	return Vector(n.e[0] + v.e[0], n.e[1] + v.e[1], n.e[2] + v.e[2]);
}

Normal operator/(const Normal& n, float s)
{
	return Normal(n.e[0]/s, n.e[1]/s, n.e[2]/s);
}


Normal operator*(const Normal& n, float s)
{
	return Normal(n.e[0]*s, n.e[1]*s, n.e[2]*s);
}

Normal operator*(float s, const Normal& n)
{
	return Normal(n.e[0]*s, n.e[1]*s, n.e[2]*s);
}
	
Normal Normal::operator=(const Normal& n)
{
	e[0] = n.e[0];
	e[1] = n.e[1];
	e[2] = n.e[2];
}

Normal Normal::operator=(const Vector& v)
{
	e[0] = v.e[0];
	e[1] = v.e[1];
	e[2] = v.e[2];
}

Normal Normal::operator-()
{
	return Normal(-e[0], -e[1], -e[2]);
}

Normal Normal::operator-() const
{
	return Normal(-e[0], -e[1], -e[2]);
}
		
float dot(const Normal& n, const Vector& v)
{
	return n.e[0] * v.e[0] + n.e[1] * v.e[1] + n.e[2] * v.e[2];
}

float dot(const Vector& v, const Normal& n)
{
	return n.e[0] * v.e[0] + n.e[1] * v.e[1] + n.e[2] * v.e[2];
}