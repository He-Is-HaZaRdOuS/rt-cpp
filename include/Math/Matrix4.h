#pragma once
#include "Math/Vector4.h"
#include <ostream>

class Matrix4 {
public:
	Matrix4();
	Matrix4(const Matrix4& other);
	Matrix4(float f1, float f2, float f3, float f4,
				float f5, float f6, float f7, float f8,
				float f9, float f10, float f11, float f12,
				float f13, float f14, float f15, float f16);

	~Matrix4() = default;

	static Matrix4 Zero();
	static Matrix4 Translate(float tx, float ty, float tz);
	static Matrix4 Scale(float sx, float sy, float sz);
	static Matrix4 RotateX(float angle);
	static Matrix4 RotateY(float angle);
	static Matrix4 RotateZ(float angle);
	static Matrix4 Rotate(float x, float y, float z, float angle);
	static Matrix4 Rotate(const Vector4& v, float angle);

	[[nodiscard]] Vector4 mult(const Vector4& v) const;
	[[nodiscard]] Matrix4 mult(const Matrix4& other) const;
	[[nodiscard]] float det() const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix4& matrix);
	friend Matrix4 operator*(const Matrix4& self, const Matrix4& other);
	friend Vector4 operator*(const Matrix4& self, const Vector4& other);

private:
	float m_data[4][4];
};
