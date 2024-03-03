#include "Math/Vector4.h"
#include <cstring>
#include <cmath>

Vector4::Vector4()
{
	m_data[0] = 0.0;
	m_data[1] = 0.0;
	m_data[2] = 0.0;
	m_data[3] = 1.0;
}

Vector4::Vector4(const f32 f1, const f32 f2, const f32 f3)
{
	m_data[0] = f1;
	m_data[1] = f2;
	m_data[2] = f3;
	m_data[3] = 1.0;
}

Vector4::Vector4(const f32 f1, const f32 f2, const f32 f3, const f32 f4)
{
	m_data[0] = f1;
	m_data[1] = f2;
	m_data[2] = f3;
	m_data[3] = f4;
}

Vector4::Vector4(const Vector4& other)
{
	memcpy(m_data, other.m_data, sizeof(m_data));
}

Vector4 Vector4::Zero()
{
	return {0.0, 0.0, 0.0, 0.0};
}

f32 Vector4::magnitude() const {
	return sqrt(m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2]);
}

f32 Vector4::dot(const Vector4& other) const {
	return m_data[0] * other.m_data[0] + m_data[1] * other.m_data[1] + m_data[2] * other.m_data[2]; 
}

Vector4 Vector4::cross(const Vector4& other) const
{
	const f32 f1 = m_data[1] * other.m_data[2] - other.m_data[2] * m_data[1];
	const f32 f2 = m_data[2] * other.m_data[0] - other.m_data[0] * m_data[2];
	const f32 f3 = m_data[0] * other.m_data[1] - other.m_data[1] * m_data[0];
	const f32 f4 = m_data[3];

	return {f1, f2, f3, f4};
}

Vector4 Vector4::cross_zero(const Vector4& other) const
{
	const f32 f1 = m_data[1] * other.m_data[2] - other.m_data[2] * m_data[1];
	const f32 f2 = m_data[2] * other.m_data[0] - other.m_data[0] * m_data[2];
	const f32 f3 = m_data[0] * other.m_data[1] - other.m_data[1] * m_data[0];

	return {f1, f2, f3, 0.0};
}

void Vector4::normalize()
{
	const f32 mag = 1 / magnitude();
	m_data[0] = m_data[0] * mag;
	m_data[1] = m_data[1] * mag;
	m_data[2] = m_data[2] * mag;
}

std::ostream& operator<<(std::ostream& os, const Vector4& vector)
{
	os << "[";
	for (u32 i = 0; i < 4; ++i) {
		os << vector.m_data[i];
		if (i != 3)
			os << ", ";
	}
	os << "]";
	return os;
}

Vector4 operator+(const Vector4& self, const Vector4& other)
{
	return {self.m_data[0] + other.m_data[0], self.m_data[1] + other.m_data[1], self.m_data[2] + other.m_data[2], 1.0};
}

Vector4 operator-(const Vector4& self, const Vector4& other)
{
	return {self.m_data[0] - other.m_data[0], self.m_data[1] - other.m_data[1], self.m_data[2] - other.m_data[2], 1.0};
}
