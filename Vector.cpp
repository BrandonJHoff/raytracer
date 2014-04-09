#include "Vector.h"

Vector::Vector(float x, float y, float z)
{
	e[0] = x; 
	e[1] = y;
	e[2] = z;
}

float Vector::length() const
{
	return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
}

void Vector::normalize() 
{
	*this = *this / (*this).length();
}

ostream& operator<<(ostream& os, const Vector& v)
{
	os << "(" << v.e[0] << " " << v.e[1] << " " << v.e[2] << ")";
	return os;
}

bool operator==(const Vector& v1, const Vector& v2)
{
	if(v1.e[0] != v2.e[0]) return false;
	if(v1.e[1] != v2.e[1]) return false;
	if(v1.e[2] != v2.e[2]) return false;
	return true;
}

bool operator!=(const Vector& v1, const Vector& v2)
{
	return !(v1 == v2);
}
	
Vector operator+(const Vector& v1, const Vector& v2)
{
	return Vector(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

Vector operator-(const Vector& v1, const Vector& v2)
{
	return Vector(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

Vector operator/(const Vector& v1, const Vector& v2)
{
	float tempx, tempy, tempz;
	if(v2.e[0] == 0)
		tempx = 0;
	else
		tempx = v1.e[0] / v2.e[0];
	
	if(v2.e[1] == 0)
		tempy = 0;
	else
		tempy = v1.e[1] / v2.e[1];
	
	if(v2.e[2] == 0)
		tempz = 0;
	else
		tempz = v1.e[2] / v2.e[2];
	
	return Vector(tempx, tempy, tempz);
}


Vector operator/(const Vector& v, float s)
{
	return Vector(v.e[0]/s, v.e[1]/s, v.e[2]/s);
}

Vector operator*(const Vector& v1, const Vector& v2)
{
	return Vector(v1.e[0]*v2.e[0], v1.e[1]*v2.e[1], v1.e[2]*v2.e[2]);
}

Vector operator*(const Vector& v, float s)
{
	return Vector(v.e[0]*s, v.e[1]*s, v.e[2]*s);
}

Vector operator*(float s, const Vector& v)
{
	return Vector(v.e[0]*s, v.e[1]*s, v.e[2]*s);
}
	
Vector Vector::operator=(const Vector& v)
{
	e[0] = v.e[0];
	e[1] = v.e[1];
	e[2] = v.e[2];
}

Vector Vector::operator+=(const Vector& v)
{
	*this = *this + v;
	return *this;
}

Vector Vector::operator-=(const Vector& v)
{
	*this = *this - v;
	return *this;
}

Vector Vector::operator*=(const float s)
{
	*this = *this * s;
	return *this;
}

Vector Vector::operator/=(const float s)
{
	*this = *this / s;
	return *this;
}

Vector Vector::operator-()const
{
	return Vector(-e[0], -e[1], -e[2]);
}
		
Vector cross(const Vector& v1, const Vector& v2)
{
	Vector temp;
	
	temp.e[0] = v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1];
	temp.e[1] = v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2];
	temp.e[2] = v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0];
	
	return temp;
}

float dot(const Vector& v1, const Vector& v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}