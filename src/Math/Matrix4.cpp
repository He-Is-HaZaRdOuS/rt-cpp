#include "Math/Matrix4.h"
#include <cstring>
#include <cmath>

Matrix4::Matrix4()
{
	m_data[0][0] = 1.0;
	m_data[0][1] = 0.0;
	m_data[0][2] = 0.0;
	m_data[0][3] = 0.0;
	m_data[1][0] = 0.0;
	m_data[1][1] = 1.0;
	m_data[1][2] = 0.0;
	m_data[1][3] = 0.0;
	m_data[2][0] = 0.0;
	m_data[2][1] = 0.0;
	m_data[2][2] = 1.0;
	m_data[2][3] = 0.0;
	m_data[3][0] = 0.0;
	m_data[3][1] = 0.0;
	m_data[3][2] = 0.0;
	m_data[3][3] = 1.0;
}

Matrix4::Matrix4(const Matrix4& other)
{
	memcpy(m_data, other.m_data, sizeof(m_data));
}

Matrix4::Matrix4(const f32 f1, const f32 f2, const f32 f3, const f32 f4, const f32 f5, const f32 f6, const f32 f7, const f32 f8, const f32 f9, const f32 f10, const f32 f11, const f32 f12, const f32 f13, const f32 f14, const f32 f15, const f32 f16)
{
	m_data[0][0] = f1;
	m_data[1][0] = f2;
	m_data[2][0] = f3;
	m_data[3][0] = f4;
	m_data[0][1] = f5;
	m_data[1][1] = f6;
	m_data[2][1] = f7;
	m_data[3][1] = f8;
	m_data[0][2] = f9;
	m_data[1][2] = f10;
	m_data[2][2] = f11;
	m_data[3][2] = f12;
	m_data[0][3] = f13;
	m_data[1][3] = f14;
	m_data[2][3] = f15;
	m_data[3][3] = f16;
}

Matrix4 Matrix4::Zero()
{
	Matrix4 tmp = Matrix4();
	tmp.m_data[0][0] = 0.0;
	tmp.m_data[1][1] = 0.0;
	tmp.m_data[2][2] = 0.0;
	tmp.m_data[3][3] = 0.0;
	return tmp;
}

Matrix4 Matrix4::Translate(const f32 tx,const f32 ty,const f32 tz)
{
	Matrix4 tmp = Matrix4();
	tmp.m_data[0][3] = tx;
	tmp.m_data[1][3] = ty;
	tmp.m_data[2][3] = tz;
	return tmp;
}

Matrix4 Matrix4::Scale(const f32 sx,const f32 sy,const f32 sz)
{
	Matrix4 tmp = Matrix4();
	tmp.m_data[0][0] = sx;
	tmp.m_data[1][1] = sy;
	tmp.m_data[2][2] = sz;
	return tmp;
}

Matrix4 Matrix4::RotateX(const f32 angle)
{
	Matrix4 tmp = Matrix4();
	f32 rad = angle * M_PI / 180.0;
	f32 radc = cos(rad);
	f32 rads = sin(rad);
	tmp.m_data[1][1] = radc;
	tmp.m_data[1][2] = -rads;
	tmp.m_data[2][1] = rads;
	tmp.m_data[2][2] = radc;
	return tmp;
}

Matrix4 Matrix4::RotateY(const f32 angle)
{
	Matrix4 tmp = Matrix4();
	f32 rad = angle * M_PI / 180.0;
	f32 radc = cos(rad);
	f32 rads = sin(rad);
	tmp.m_data[0][0] = radc;
	tmp.m_data[0][2] = rads;
	tmp.m_data[2][0] = -rads;
	tmp.m_data[2][2] = radc;
	return tmp;
}

Matrix4 Matrix4::RotateZ(const f32 angle)
{
	Matrix4 tmp = Matrix4();
	f32 rad = angle * M_PI / 180.0;
	f32 radc = cos(rad);
	f32 rads = sin(rad);
	tmp.m_data[0][0] = radc;
	tmp.m_data[0][1] = -rads;
	tmp.m_data[1][0] = rads;
	tmp.m_data[1][1] = radc;
	return tmp;
}

Matrix4 Matrix4::Rotate(f32 x, f32 y, f32 z, const f32 angle)
{
	Matrix4 tmp = Matrix4();
	const f32 rad = angle * M_PI / 180.0;
	const f32 radc = cos(rad);
	const f32 rads = sin(rad);
	const f32 t = 1.0 - radc;

	const f32 normalizer = 1.0 / sqrt(x * x + y * y + z * z);
	x = x * normalizer;
	y = y * normalizer;
	z = z / normalizer;

	const f32 tx = t * x;
	const f32 ty = t * y;
	const f32 tz = t * z;

	const f32 txx = tx * x;
	const f32 txy = tx * y;
	const f32 txz = tx * z;

	const f32 tyy = ty * y;
	const f32 tyz = ty * z;
	
	const f32 tzz = tz * z;
	
	const f32 radsx = rads * x;
	const f32 radsy = rads * y;
	const f32 radsz = rads * z;

	tmp.m_data[0][0] = txx + radc;
	tmp.m_data[0][1] = txy - radsz;
	tmp.m_data[0][2] = txz + radsy;

	tmp.m_data[1][0] = txy + radsz;
	tmp.m_data[1][1] = tyy + radc;
	tmp.m_data[1][2] = tyz - radsx;

	tmp.m_data[2][0] = txz - radsy;
	tmp.m_data[2][1] = tyz + radsx;
	tmp.m_data[2][2] = tzz + radc;

	tmp.m_data[3][0] = 0.0;
	tmp.m_data[3][1] = 0.0;
	tmp.m_data[3][2] = 0.0;

	return tmp;
}

Matrix4 Matrix4::Rotate(const Vector4& v, const f32 angle)
{
	return Rotate(v.get_x(), v.get_y(), v.get_z(), angle);
}

Vector4 Matrix4::mult(const Vector4& v) const
{
	return { m_data[0][0] * v.get_x() + m_data[0][1] * v.get_y() + m_data[0][2] * v.get_z() + m_data[0][3] * v.get_w(),
		m_data[1][0] * v.get_x() + m_data[1][1] * v.get_y() + m_data[1][2] * v.get_z() + m_data[1][3] * v.get_w(),
		m_data[2][0] * v.get_x() + m_data[2][1] * v.get_y() + m_data[2][2] * v.get_z() + m_data[2][3] * v.get_w(),
		m_data[3][0] * v.get_x() + m_data[3][1] * v.get_y() + m_data[3][2] * v.get_z() + m_data[3][3] * v.get_w() };
}

Matrix4 Matrix4::mult(const Matrix4& other) const
{
	Matrix4 tmp = Matrix4::Zero();

	for (u32 i = 0; i < 4; ++i) {
		for (u32 k = 0; k < 4; ++k) {
			for (u32 j = 0; j < 4; ++j) {
				tmp.m_data[i][j] = tmp.m_data[i][j] + m_data[i][k] * other.m_data[k][j];
			}
		}
	}

	return tmp;
}

f32 Matrix4::det() const
{
        f32 det = 0.0f;

        det += m_data[0][0] * (m_data[1][1] * (m_data[2][2] * m_data[3][3] - m_data[2][3] * m_data[3][2]) - m_data[1][2] * (m_data[2][1] * m_data[3][3] - m_data[2][3] * m_data[3][1]) + m_data[1][3] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1]));
        det -= m_data[0][1] * (m_data[1][0] * (m_data[2][2] * m_data[3][3] - m_data[2][3] * m_data[3][2]) - m_data[1][2] * (m_data[2][0] * m_data[3][3] - m_data[2][3] * m_data[3][0]) + m_data[1][3] * (m_data[2][0] * m_data[3][2] - m_data[2][2] * m_data[3][0]));
        det += m_data[0][2] * (m_data[1][0] * (m_data[2][1] * m_data[3][3] - m_data[2][3] * m_data[3][1]) - m_data[1][1] * (m_data[2][0] * m_data[3][3] - m_data[2][3] * m_data[3][0]) + m_data[1][3] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]));
        det -= m_data[0][3] * (m_data[1][0] * (m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1]) - m_data[1][1] * (m_data[2][0] * m_data[3][2] - m_data[2][2] * m_data[3][0]) + m_data[1][2] * (m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0]));

        return det;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
{
	os << "[";
	for (u32 i = 0; i < 4; ++i) {
		os << "[";
		for (u32 j = 0; j < 4; ++j) {
			os << matrix.m_data[i][j];
			if (j != 3)
				os << ", ";
		}
		os << "]";
	}
	os << "]";
	return os;
}

Matrix4 operator*(const Matrix4& self, const Matrix4& other)
{
	return self.mult(other);
}

Vector4 operator*(const Matrix4& self, const Vector4& other)
{
	return self.mult(other);
}
