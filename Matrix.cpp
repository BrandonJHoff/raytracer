#include "Matrix.h"

float det3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	return a*e*i + b*h*c + g*b*f - g*e*c - d*b*i - a*h*f;
}

Matrix::Matrix(const Matrix& m)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			e[i][j] = m.e[i][j];
}
	
void Matrix::invert()
{
	float det = determinant();
	Matrix inverse;
	
	inverse.e[0][0] =  det3(e[1][1], e[1][2], e[1][3],
					e[2][1], e[2][2], e[2][3],
					e[3][1], e[3][2], e[3][3]) / det;
	inverse.e[0][1] = -det3(e[0][1], e[0][2], e[0][3],
					e[2][1], e[2][2], e[2][3],
					e[3][1], e[3][2], e[3][3]) / det;
	inverse.e[0][2] =  det3(e[0][1], e[0][2], e[0][3],
					e[1][1], e[1][2], e[1][3],
					e[3][1], e[3][2], e[3][3]) / det;
	inverse.e[0][3] = -det3(e[0][1], e[0][2], e[0][3],
					e[1][1], e[1][2], e[1][3],
					e[2][1], e[2][2], e[2][3]) / det;

	inverse.e[1][0] = -det3(e[1][0], e[1][2], e[1][3],
					e[2][0], e[2][2], e[2][3],
					e[3][0], e[3][2], e[3][3]) / det;
	inverse.e[1][1] =  det3(e[0][0], e[0][2], e[0][3],
					e[2][0], e[2][2], e[2][3],
					e[3][0], e[3][2], e[3][3]) / det;
	inverse.e[1][2] = -det3(e[0][0], e[0][2], e[0][3],
					e[1][0], e[1][2], e[1][3],
					e[3][0], e[3][2], e[3][3]) / det;
	inverse.e[1][3] =  det3(e[0][0], e[0][2], e[0][3],
					e[1][0], e[1][2], e[1][3],
					e[2][0], e[2][2], e[2][3]) / det;

	inverse.e[2][0] =  det3(e[1][0], e[1][1], e[1][3],
					e[2][0], e[2][1], e[2][3],
					e[3][0], e[3][1], e[3][3]) / det;
	inverse.e[2][1] = -det3(e[0][0], e[0][1], e[0][3],
					e[2][0], e[2][1], e[2][3],
					e[3][0], e[3][1], e[3][3]) / det;
	inverse.e[2][2] =  det3(e[0][0], e[0][1], e[0][3],
					e[1][0], e[1][1], e[1][3],
					e[3][0], e[3][1], e[3][3]) / det;
	inverse.e[2][3] = -det3(e[0][0], e[0][1], e[0][3],
					e[1][0], e[1][1], e[1][3],
					e[2][0], e[2][1], e[2][3]) / det;

	inverse.e[3][0] = -det3(e[1][0], e[1][1], e[1][2],
					e[2][0], e[2][1], e[2][2],
					e[3][0], e[3][1], e[3][2]) / det;
	inverse.e[3][1] =  det3(e[0][0], e[0][1], e[0][2],
					e[2][0], e[2][1], e[2][2],
					e[3][0], e[3][1], e[3][2]) / det;
	inverse.e[3][2] = -det3(e[0][0], e[0][1], e[0][2],
					e[1][0], e[1][1], e[1][2],
					e[3][0], e[3][1], e[3][2]) / det;
	inverse.e[3][3] =  det3(e[0][0], e[0][1], e[0][2],
					e[1][0], e[1][1], e[1][2],
					e[2][0], e[2][1], e[2][2]) / det;

	*this = inverse;
}

void Matrix::transpose()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			float temp = e[i][j];
			e[i][j] = e[j][i];
			e[j][i] = temp;
		}
	}
}

Matrix Matrix::getInverse() const
{
	Matrix ret = *this;
	ret.invert();
	return ret;
}

Matrix Matrix::getTranspose() const
{
	Matrix ret = *this;
	ret.transpose();
	return ret;
}

Matrix& Matrix::operator+=(const Matrix& right)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			e[i][j] += right.e[i][j];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& right)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			e[i][j] -= right.e[i][j];
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& right)
{
	Matrix ret = *this;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			float sum = 0;
			for(int k = 0; k < 4; k++)
				sum += ret.e[i][k] * right.e[k][j];
			e[i][j] = sum;
		}
	}
	
	return *this;
}

Matrix& Matrix::operator*=(float right)
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			e[i][j] *= right;
	return *this;
}
	
ostream& operator<<(ostream& out, const Matrix& m)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			out << setprecision(3) << setw(10) << m.e[i][j];
		out << endl;
	}
	return out;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
	Matrix ret;
	
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			ret.e[i][j] = left.e[i][j] + right.e[i][j];
	return ret;
}

Matrix operator-(const Matrix& left, const Matrix& right)
{
	Matrix ret;
	
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			ret.e[i][j] = left.e[i][j] - right.e[i][j];
	return ret;
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
	Matrix ret;

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			float subt = 0;
			for(int k = 0; k < 4; k++)
				subt += left.e[i][k] * right.e[k][j];
			ret.e[i][j] = subt;
		}
	
	return ret;
}

Vector operator*(const Matrix& left, const Vector& right)
{
	Vector ret;
	float temp;

	ret.e[0] = right.e[0] * left.e[0][0] + right.e[1] * left.e[0][1] + right.e[2] * left.e[0][2] + left.e[0][3];
	ret.e[1] = right.e[0] * left.e[1][0] + right.e[1] * left.e[1][1] + right.e[2] * left.e[1][2] + left.e[1][3];
	ret.e[2] = right.e[0] * left.e[2][0] + right.e[1] * left.e[2][1] + right.e[2] * left.e[2][2] + left.e[2][3];
	temp   = right.e[0] * left.e[3][0] + right.e[1] * left.e[3][1] + right.e[2] * left.e[3][2] + left.e[3][3];

	ret /= temp;
	return ret;
}

Point operator*(const Matrix& left, const Point& right)
{
	Point ret;
	float temp;

	ret.e[0] = right.e[0] * left.e[0][0] + right.e[1] * left.e[0][1] + right.e[2] * left.e[0][2] + left.e[0][3];
	ret.e[1] = right.e[0] * left.e[1][0] + right.e[1] * left.e[1][1] + right.e[2] * left.e[1][2] + left.e[1][3];
	ret.e[2] = right.e[0] * left.e[2][0] + right.e[1] * left.e[2][1] + right.e[2] * left.e[2][2] + left.e[2][3];
	temp   = right.e[0] * left.e[3][0] + right.e[1] * left.e[3][1] + right.e[2] * left.e[3][2] + left.e[3][3];

	ret = ret/temp;
	return ret;
}

Matrix operator*(const Matrix& left, float right)
{
	Matrix ret;
	
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			ret.e[i][j] = left.e[i][j] * right;
	return ret;
}
	
Vector transformLoc(const Matrix& left, const Vector& right)
{
	return left * right;
}

Point transformLoc(const Matrix& left, const Point& right)
{
	return left * right;
}

Vector transformVec(const Matrix& left, const Vector& right)
{
	Vector ret;
	
	ret.e[0] = right.e[0] * left.e[0][0] + right.e[1] * left.e[0][1] + right.e[2] * left.e[0][2];
	ret.e[1] = right.e[0] * left.e[1][0] + right.e[1] * left.e[1][1] + right.e[2] * left.e[1][2];
	ret.e[2] = right.e[0] * left.e[2][0] + right.e[1] * left.e[2][1] + right.e[2] * left.e[2][2];

	return ret;
}

Normal transformVec(const Matrix& left, const Normal& right)
{
	Normal ret;
	
	ret.e[0] = right.e[0] * left.e[0][0] + right.e[1] * left.e[0][1] + right.e[2] * left.e[0][2];
	ret.e[1] = right.e[0] * left.e[1][0] + right.e[1] * left.e[1][1] + right.e[2] * left.e[1][2];
	ret.e[2] = right.e[0] * left.e[2][0] + right.e[1] * left.e[2][1] + right.e[2] * left.e[2][2];

	return ret;
}

Matrix zeroMatrix()
{
	Matrix ret;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			ret.e[i][j] = 0;
	return ret;
}

Matrix identityMatrix()
{
	Matrix ret;
	ret.e[0][0] = 1.0;
	ret.e[0][1] = 0.0;
	ret.e[0][2] = 0.0;
	ret.e[0][3] = 0.0;
	ret.e[1][0] = 0.0;
	ret.e[1][1] = 1.0;
	ret.e[1][2] = 0.0;
	ret.e[1][3] = 0.0;
	ret.e[2][0] = 0.0;
	ret.e[2][1] = 0.0;
	ret.e[2][2] = 1.0;
	ret.e[2][3] = 0.0;
	ret.e[3][0] = 0.0;
	ret.e[3][1] = 0.0;
	ret.e[3][2] = 0.0;
	ret.e[3][3] = 1.0;
	return ret;
}

Matrix translate(float _x, float _y, float _z)
{
	Matrix ret = identityMatrix();
	ret.e[0][3] = _x;
	ret.e[1][3] = _y;
	ret.e[2][3] = _z;
	return ret;
}

Matrix scale(float _x, float _y, float _z)
{
	Matrix ret = zeroMatrix();
	ret.e[0][0] = _x;
	ret.e[1][1] = _y;
	ret.e[2][2] = _z;
	ret.e[3][3] = 1.0;
	return ret;
}

Matrix rotate(const Vector& axis, float angle)
{
	Vector _axis = axis;
	_axis.normalize();
	Matrix ret;
	float x = _axis.x();
	float y = _axis.y();
	float z = _axis.z();
	float cosine = cos(angle);
	float sine = sin(angle);
	float t = 1 - cosine;

	ret.e[0][0] = t * x * x + cosine;
	ret.e[0][1] = t * x * y - sine * y;
	ret.e[0][2] = t * x * z + sine * y;
	ret.e[0][3] = 0.0;

	ret.e[1][0] = t * x * y + sine * z;
	ret.e[1][1] = t * y * y + cosine;
	ret.e[1][2] = t * y * z - sine * x;
	ret.e[1][3] = 0.0;

	ret.e[2][0] = t * x * z - sine * y;
	ret.e[2][1] = t * y * z + sine * x;
	ret.e[2][2] = t * z * z + cosine;
	ret.e[2][3] = 0.0;

	ret.e[3][0] = 0.0;
	ret.e[3][1] = 0.0;
	ret.e[3][2] = 0.0;
	ret.e[3][3] = 1.0;

	return ret;
}

Matrix rotateX(float angle)
{
	Matrix ret = identityMatrix();
	float cosine = cos(angle);
	float sine = sin(angle);
	
	ret.e[1][1] = cosine;
	ret.e[1][2] = -sine;
	ret.e[2][1] = sine;
	ret.e[2][2] = cosine;

	return ret;
}

Matrix rotateY(float angle)
{
	Matrix ret = identityMatrix();
	float cosine = cos(angle);
	float sine = sin(angle);

	ret.e[0][0] = cosine;
	ret.e[0][2] = sine;
	ret.e[2][0] = -sine;
	ret.e[2][2] = cosine;

	return ret;
}

Matrix rotateZ(float angle)
{
	Matrix ret = identityMatrix();
	float cosine = cos(angle);
	float sine = sin(angle);

	ret.e[0][0] = cosine;
	ret.e[0][1] = -sine;
	ret.e[1][0] = sine;
	ret.e[1][1] = cosine;

	return ret;
}
	
float Matrix::determinant()
{
	float det;
	det = e[0][0] * det3(e[1][1], e[1][2], e[1][3],
					e[2][1], e[2][2], e[2][3],
					e[3][1], e[3][2], e[3][3]);
	det -= e[0][1] * det3(e[1][0], e[1][2], e[1][3],
					e[2][0], e[2][2], e[2][3],
					e[3][0], e[3][2], e[3][3]);
	det += e[0][2] * det3(e[1][0], e[1][1], e[1][3],
					e[2][0], e[2][1], e[2][3],
					e[3][0], e[3][1], e[3][3]);
	det -= e[0][3] * det3(e[1][0], e[1][1], e[1][2],
					e[2][0], e[2][1], e[2][2],
					e[3][0], e[3][1], e[3][2]);

	return det;
}
