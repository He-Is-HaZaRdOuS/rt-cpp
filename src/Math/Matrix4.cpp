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

Matrix4 Matrix4::Col(const f32 f1, const f32 f2, const f32 f3, const f32 f4, const f32 f5, const f32 f6, const f32 f7, const f32 f8, const f32 f9, const f32 f10, const f32 f11, const f32 f12, const f32 f13, const f32 f14, const f32 f15, const f32 f16)
{
	Matrix4 tmp = Matrix4();
	tmp.m_data[0][0] = f1;
	tmp.m_data[0][1] = f2;
	tmp.m_data[0][2] = f3;
	tmp.m_data[0][3] = f4;
	tmp.m_data[1][0] = f5;
	tmp.m_data[1][1] = f6;
	tmp.m_data[1][2] = f7;
	tmp.m_data[1][3] = f8;
	tmp.m_data[2][0] = f9;
	tmp.m_data[2][1] = f10;
	tmp.m_data[2][2] = f11;
	tmp.m_data[2][3] = f12;
	tmp.m_data[3][0] = f13;
	tmp.m_data[3][1] = f14;
	tmp.m_data[3][2] = f15;
	tmp.m_data[3][3] = f16;
	return tmp;
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
	Matrix4 translationMatrix;

	translationMatrix.m_data[0][3] = tx;
	translationMatrix.m_data[1][3] = ty;
	translationMatrix.m_data[2][3] = tz;

	return translationMatrix;
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
	Matrix4 tmp = Matrix4::Zero();
	tmp.m_data[0][0] = 1.0;  // Set the diagonal to 1
	tmp.m_data[3][3] = 1.0;  // Set the diagonal to 1

	const f32 rad = static_cast<f32>(angle * M_PI / 180.0);
	const f32 radc = static_cast<f32>(cos(rad));
	const f32 rads = static_cast<f32>(sin(rad));

	tmp.m_data[1][1] = radc;
	tmp.m_data[1][2] = -rads;
	tmp.m_data[2][1] = rads;
	tmp.m_data[2][2] = radc;
	return tmp;
}

Matrix4 Matrix4::RotateY(const f32 angle)
{
	Matrix4 tmp = Matrix4();
	const f32 rad = static_cast<f32>(angle * M_PI / 180.0);
	const f32 radc = static_cast<f32>(cos(rad));
	const f32 rads = static_cast<f32>(sin(rad));
	tmp.m_data[0][0] = radc;
	tmp.m_data[2][0] = -rads;
	tmp.m_data[0][2] = rads;
	tmp.m_data[2][2] = radc;
	return tmp;
}

Matrix4 Matrix4::RotateZ(const f32 angle)
{
	Matrix4 tmp = Matrix4();
	const f32 rad = static_cast<f32>(angle * M_PI / 180.0);
	const f32 radc = static_cast<f32>(cos(rad));
	const f32 rads = static_cast<f32>(sin(rad));
	tmp.m_data[0][0] = radc;
	tmp.m_data[1][0] = rads;
	tmp.m_data[0][1] = -rads;
	tmp.m_data[1][1] = radc;
	return tmp;
}

Matrix4 Matrix4::Rotate(f32 x, f32 y, f32 z, const f32 angle)
{
	Matrix4 tmp = Matrix4();
	const f32 rad = static_cast<f32>(angle * M_PI / 180.0);
	const f32 radc = static_cast<f32>(cos(rad));
	const f32 rads = static_cast<f32>(sin(rad));
	const f32 t = static_cast<f32>(1.0 - radc);

	const f32 normalizer = static_cast<f32>(1.0 / sqrt(x * x + y * y + z * z));
	x = x * normalizer;
	y = y * normalizer;
	z = z * normalizer;

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

Matrix4 Matrix4::inverse() const {

f32 A2323 = m_data[2][2] * m_data[3][3] - m_data[2][3] * m_data[3][2];
f32 A1323 = m_data[2][1] * m_data[3][3] - m_data[2][3] * m_data[3][1];
f32 A1223 = m_data[2][1] * m_data[3][2] - m_data[2][2] * m_data[3][1];
f32 A0323 = m_data[2][0] * m_data[3][3] - m_data[2][3] * m_data[3][0];
f32 A0223 = m_data[2][0] * m_data[3][2] - m_data[2][2] * m_data[3][0];
f32 A0123 = m_data[2][0] * m_data[3][1] - m_data[2][1] * m_data[3][0];
f32 A2313 = m_data[1][2] * m_data[3][3] - m_data[1][3] * m_data[3][2];
f32 A1313 = m_data[1][1] * m_data[3][3] - m_data[1][3] * m_data[3][1];
f32 A1213 = m_data[1][1] * m_data[3][2] - m_data[1][2] * m_data[3][1];
f32 A2312 = m_data[1][2] * m_data[2][3] - m_data[1][3] * m_data[2][2];
f32 A1312 = m_data[1][1] * m_data[2][3] - m_data[1][3] * m_data[2][1];
f32 A1212 = m_data[1][1] * m_data[2][2] - m_data[1][2] * m_data[2][1];
f32 A0313 = m_data[1][0] * m_data[3][3] - m_data[1][3] * m_data[3][0];
f32 A0213 = m_data[1][0] * m_data[3][2] - m_data[1][2] * m_data[3][0];
f32 A0312 = m_data[1][0] * m_data[2][3] - m_data[1][3] * m_data[2][0];
f32 A0212 = m_data[1][0] * m_data[2][2] - m_data[1][2] * m_data[2][0];
f32 A0113 = m_data[1][0] * m_data[3][1] - m_data[1][1] * m_data[3][0];
f32 A0112 = m_data[1][0] * m_data[2][1] - m_data[1][1] * m_data[2][0];

f32 detr = m_data[0][0] * ( m_data[1][1] * A2323 - m_data[1][2] * A1323 + m_data[1][3] * A1223 )
    - m_data[0][1] * ( m_data[1][0] * A2323 - m_data[1][2] * A0323 + m_data[1][3] * A0223 )
    + m_data[0][2] * ( m_data[1][0] * A1323 - m_data[1][1] * A0323 + m_data[1][3] * A0123 )
    - m_data[0][3] * ( m_data[1][0] * A1223 - m_data[1][1] * A0223 + m_data[1][2] * A0123 );
detr = 1 / detr;

return Col(
   detr *   ( m_data[1][1] * A2323 - m_data[1][2] * A1323 + m_data[1][3] * A1223 ),
   detr * - ( m_data[0][1] * A2323 - m_data[0][2] * A1323 + m_data[0][3] * A1223 ),
   detr *   ( m_data[0][1] * A2313 - m_data[0][2] * A1313 + m_data[0][3] * A1213 ),
   detr * - ( m_data[0][1] * A2312 - m_data[0][2] * A1312 + m_data[0][3] * A1212 ),
   detr * - ( m_data[1][0] * A2323 - m_data[1][2] * A0323 + m_data[1][3] * A0223 ),
   detr *   ( m_data[0][0] * A2323 - m_data[0][2] * A0323 + m_data[0][3] * A0223 ),
   detr * - ( m_data[0][0] * A2313 - m_data[0][2] * A0313 + m_data[0][3] * A0213 ),
   detr *   ( m_data[0][0] * A2312 - m_data[0][2] * A0312 + m_data[0][3] * A0212 ),
   detr *   ( m_data[1][0] * A1323 - m_data[1][1] * A0323 + m_data[1][3] * A0123 ),
   detr * - ( m_data[0][0] * A1323 - m_data[0][1] * A0323 + m_data[0][3] * A0123 ),
   detr *   ( m_data[0][0] * A1313 - m_data[0][1] * A0313 + m_data[0][3] * A0113 ),
   detr * - ( m_data[0][0] * A1312 - m_data[0][1] * A0312 + m_data[0][3] * A0112 ),
   detr * - ( m_data[1][0] * A1223 - m_data[1][1] * A0223 + m_data[1][2] * A0123 ),
   detr *   ( m_data[0][0] * A1223 - m_data[0][1] * A0223 + m_data[0][2] * A0123 ),
   detr * - ( m_data[0][0] * A1213 - m_data[0][1] * A0213 + m_data[0][2] * A0113 ),
   detr *   ( m_data[0][0] * A1212 - m_data[0][1] * A0212 + m_data[0][2] * A0112 ));

	/////
	//const f32 detr = det();

    Matrix4 tmp = Matrix4();

	const Matrix3 m00 = Matrix3(m_data[1][1], m_data[1][2], m_data[1][3],
	                            m_data[2][1], m_data[2][2], m_data[2][3],
	                            m_data[3][1], m_data[3][2], m_data[3][3]);

	const Matrix3 m01 = Matrix3(m_data[1][0], m_data[1][2], m_data[1][3],
	                            m_data[2][0], m_data[2][2], m_data[2][3],
	                            m_data[3][0], m_data[3][2], m_data[3][3]);

	const Matrix3 m02 = Matrix3(m_data[1][0], m_data[1][1], m_data[1][3],
	                            m_data[2][0], m_data[2][1], m_data[2][3],
	                            m_data[3][0], m_data[3][1], m_data[3][3]);

    const Matrix3 m03 = Matrix3(m_data[1][0], m_data[1][1], m_data[1][2],
                          m_data[2][0], m_data[2][1], m_data[2][2],
                          m_data[3][0], m_data[3][1], m_data[3][2]);

    const Matrix3 m10 = Matrix3(m_data[0][1], m_data[0][2], m_data[0][3],
                          m_data[2][1], m_data[2][2], m_data[2][3],
                          m_data[3][1], m_data[3][2], m_data[3][3]);

    const Matrix3 m11 = Matrix3(m_data[0][0], m_data[0][2], m_data[0][3],
                          m_data[2][0], m_data[2][2], m_data[2][3],
                          m_data[3][0], m_data[3][2], m_data[3][3]);

    const Matrix3 m12 = Matrix3(m_data[0][0], m_data[0][1], m_data[0][3],
                          m_data[2][0], m_data[2][1], m_data[2][3],
                          m_data[3][0], m_data[3][1], m_data[3][3]);

    const Matrix3 m13 = Matrix3(m_data[0][0], m_data[0][1], m_data[0][2],
                          m_data[2][0], m_data[2][1], m_data[2][2],
                          m_data[3][0], m_data[3][1], m_data[3][2]);

    const Matrix3 m20 = Matrix3(m_data[0][1], m_data[0][2], m_data[0][3],
                          m_data[1][1], m_data[1][2], m_data[1][3],
                          m_data[3][1], m_data[3][2], m_data[3][3]);

    const Matrix3 m21 = Matrix3(m_data[0][0], m_data[0][2], m_data[0][3],
                          m_data[1][0], m_data[1][2], m_data[1][3],
                          m_data[3][0], m_data[3][2], m_data[3][3]);

    const Matrix3 m22 = Matrix3(m_data[0][0], m_data[0][1], m_data[0][3],
                          m_data[1][0], m_data[1][1], m_data[1][3],
                          m_data[3][0], m_data[3][1], m_data[3][3]);

    const Matrix3 m23 = Matrix3(m_data[0][0], m_data[0][1], m_data[0][2],
                          m_data[1][0], m_data[1][1], m_data[1][2],
                          m_data[3][0], m_data[3][1], m_data[3][2]);

    const Matrix3 m30 = Matrix3(m_data[0][1], m_data[0][2], m_data[0][3],
                          m_data[1][1], m_data[1][2], m_data[1][3],
                          m_data[2][1], m_data[2][2], m_data[2][3]);

    const Matrix3 m31 = Matrix3(m_data[0][0], m_data[0][2], m_data[0][3],
                          m_data[1][0], m_data[1][2], m_data[1][3],
                          m_data[2][0], m_data[2][2], m_data[2][3]);

    const Matrix3 m32 = Matrix3(m_data[0][0], m_data[0][1], m_data[0][3],
                          m_data[1][0], m_data[1][1], m_data[1][3],
                          m_data[2][0], m_data[2][1], m_data[2][3]);

    const Matrix3 m33 = Matrix3(m_data[0][0], m_data[0][1], m_data[0][2],
                          m_data[1][0], m_data[1][1], m_data[1][2],
                          m_data[2][0], m_data[2][1], m_data[2][2]);

    tmp.m_data[0][0] = m00.det()/detr;
    tmp.m_data[1][0] = -m10.det()/detr;
    tmp.m_data[2][0] = m20.det()/detr;
    tmp.m_data[3][0] = -m30.det()/detr;
    tmp.m_data[0][1] = -m01.det()/detr;
    tmp.m_data[1][1] = m11.det()/detr;
    tmp.m_data[2][1] = -m21.det()/detr;
    tmp.m_data[3][1] = m31.det()/detr;
    tmp.m_data[0][2] = m02.det()/detr;
    tmp.m_data[1][2] = -m12.det()/detr;
    tmp.m_data[2][2] = m22.det()/detr;
    tmp.m_data[3][2] = -m32.det()/detr;
    tmp.m_data[0][3] = -m03.det()/detr;
    tmp.m_data[1][3] = m13.det()/detr;
    tmp.m_data[2][3] = -m23.det()/detr;
    tmp.m_data[3][3] = m33.det()/detr;

    return tmp;
}

Matrix4 Matrix4::transpose() const {
    Matrix4 tmp = Matrix4();

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            tmp.m_data[i][j] = m_data[j][i];
        }
    }

    return tmp;
}

bool operator==(const Matrix4 &self, const Matrix4 &other) {
	bool r1 = (self.m_data[0][0] == other.m_data[0][0] && self.m_data[0][1] == other.m_data[0][1] && self.m_data[0][2] == other.m_data[0][2] && self.m_data[0][3] == other.m_data[0][3]);
	bool r2 = (self.m_data[1][0] == other.m_data[1][0] && self.m_data[1][1] == other.m_data[1][1] && self.m_data[1][2] == other.m_data[1][2] && self.m_data[1][3] == other.m_data[1][3]);
	bool r3 = (self.m_data[2][0] == other.m_data[2][0] && self.m_data[2][1] == other.m_data[2][1] && self.m_data[2][2] == other.m_data[2][2] && self.m_data[2][3] == other.m_data[2][3]);
	bool r4 = (self.m_data[3][0] == other.m_data[3][0] && self.m_data[3][1] == other.m_data[3][1] && self.m_data[3][2] == other.m_data[3][2] && self.m_data[3][3] == other.m_data[3][3]);
	return r1 && r2 && r3 && r4;
}
