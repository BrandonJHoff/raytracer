#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector.h"
#include "Point.h"
#include "Normal.h"
#include <math.h>
#include <iostream.h>
#include <iomanip.h>

class Matrix
{
public:
	Matrix() {}
	Matrix(const Matrix& m);
	~Matrix() {};
	
	void invert();
	void transpose();
	Matrix getInverse() const;
	Matrix getTranspose() const;

	Matrix& operator+=(const Matrix& right);
	Matrix& operator-=(const Matrix& right);
	Matrix& operator*=(const Matrix& right);
	Matrix& operator*=(float right);
	
	friend ostream& operator<<(ostream& out, const Matrix& m);

	friend Matrix operator+(const Matrix& left, const Matrix& right);
	friend Matrix operator-(const Matrix& left, const Matrix& right);
	friend Matrix operator*(const Matrix& left, const Matrix& right);
	friend Vector operator*(const Matrix& left, const Vector& right);
	friend Point  operator*(const Matrix& left, const Point& right);
	friend Matrix operator*(const Matrix& left, float right);
	
	friend Vector transformLoc(const Matrix& left, const Vector& right);
	friend Point  transformLoc(const Matrix& left, const Point& right);
	friend Vector transformVec(const Matrix& left, const Vector& right);
	friend Normal transformVec(const Matrix& left, const Normal& right);

	friend Matrix zeroMatrix();
	friend Matrix identityMatrix();
	friend Matrix translate(float _x, float _y, float _z);
	friend Matrix scale(float _x, float _y, float _z);
	friend Matrix rotate(const Vector& axis, float angle);
	friend Matrix rotateX(float angle);
	friend Matrix rotateY(float angle);
	friend Matrix rotateZ(float angle);
	
	float determinant();
	
	float e[4][4];
};

#endif 