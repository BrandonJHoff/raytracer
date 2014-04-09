#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>
#include <iostream.h>

class Vector
{
public:
	Vector() {}
	Vector(float x, float y, float z);
	Vector(const Vector& v) { *this = v; }
	~Vector() {};
	
	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }
	
	float length() const;
	void normalize();
	
	friend ostream& operator<<(ostream& os, const Vector& v);
	friend bool operator==(const Vector& v1, const Vector& v2);
	friend bool operator!=(const Vector& v1, const Vector& v2);
	
	friend Vector operator+(const Vector& v1, const Vector& v2);
	friend Vector operator-(const Vector& v1, const Vector& v2);
	friend Vector operator/(const Vector& v1, const Vector& v2);
	friend Vector operator/(const Vector& v, float s);
	friend Vector operator*(const Vector& v1, const Vector& v2);
	friend Vector operator*(const Vector& v, float s);
	friend Vector operator*(float s, const Vector& v);
	
	Vector operator=(const Vector& v);
	Vector operator+=(const Vector& v);
	Vector operator-=(const Vector& v);
	Vector operator*=(const float s);
	Vector operator/=(const float s);
	Vector operator-() const;
		
	float operator[](int i) { return e[i]; }
	
	friend Vector cross(const Vector& v1, const Vector& v2);
	friend float dot(const Vector& v1, const Vector& v2);
	
	float e[3];
};

#endif 