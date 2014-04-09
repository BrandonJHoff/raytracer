#ifndef _NORMAL_H_
#define _NORMAL_H_

#include "Vector.h"
#include <math.h>

class Normal
{
public:
	Normal() {}
	Normal(float x, float y, float z);
	Normal(const Normal& n) { *this = n; }
	~Normal() {}
	
	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }
	
	float length();
	void normalize();
	
	friend ostream& operator<<(ostream& os, const Normal& n);
	friend bool operator==(const Normal& n1, const Normal& n2);
	friend bool operator!=(const Normal& n1, const Normal& n2);
	
	friend Vector operator+(const Normal& n, const Vector& v);
	friend Vector operator+(const Vector& v, const Normal& n);
	friend Normal operator/(const Normal& n, float s);
	friend Normal operator*(const Normal& n, float s);
	friend Normal operator*(float s, const Normal& n);
	
	Normal operator=(const Normal& n);
	Normal operator=(const Vector& v);
	Normal operator-();
	Normal operator-() const;
	
	float operator[](int i) { return e[i]; }
	
	friend float dot(const Normal& n, const Vector& v);
	friend float dot(const Vector& v, const Normal& n);
	
	float e[3];
};

#endif 