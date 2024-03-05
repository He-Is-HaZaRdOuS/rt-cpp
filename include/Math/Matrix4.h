#pragma once
#include "Utilities/Macros.h"
#include "Math/Vector4.h"
#include <ostream>

class Matrix4 {
public:
	Matrix4();
	Matrix4(const Matrix4& other);
	Matrix4(f32 f1, f32 f2, f32 f3, f32 f4,
				f32 f5, f32 f6, f32 f7, f32 f8,
				f32 f9, f32 f10, f32 f11, f32 f12,
				f32 f13, f32 f14, f32 f15, f32 f16);

	~Matrix4() = default;

	static Matrix4 Zero();
	static Matrix4 Translate(f32 tx, f32 ty, f32 tz);
	static Matrix4 Scale(f32 sx, f32 sy, f32 sz);
	static Matrix4 RotateX(f32 angle);
	static Matrix4 RotateY(f32 angle);
	static Matrix4 RotateZ(f32 angle);
	static Matrix4 Rotate(f32 x, f32 y, f32 z, f32 angle);
	static Matrix4 Rotate(const Vector4& v, f32 angle);

	[[nodiscard]] Vector4 mult(const Vector4& v) const;
	[[nodiscard]] Matrix4 mult(const Matrix4& other) const;
	[[nodiscard]] f32 det() const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix4& matrix);
	friend Matrix4 operator*(const Matrix4& self, const Matrix4& other);
	friend Vector4 operator*(const Matrix4& self, const Vector4& other);

private:
	f32 m_data[4][4];
};
