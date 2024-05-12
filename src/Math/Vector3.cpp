#include "Math/Vector3.h"
#include <cstring>
#include <cmath>

Vector3::Vector3() {
    m_data[0] = 0.0;
    m_data[1] = 0.0;
    m_data[2] = 0.0;
}

Vector3::Vector3(const f32 f1, const f32 f2, const f32 f3)
{
    m_data[0] = f1;
    m_data[1] = f2;
    m_data[2] = f3;
}

Vector3::Vector3(const Vector3& other)
{
    m_data[0] = other.get_x();
    m_data[1] = other.get_y();
    m_data[2] = other.get_z();
}

Vector3 Vector3::Zero()
{
    return {0.0, 0.0, 0.0};
}

f32 Vector3::length2() const {
    return m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2];
}

f32 Vector3::magnitude() const {
    return static_cast<f32>(sqrt(m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2]));
}

f32 Vector3::dot(const Vector3& other) const {
    return m_data[0] * other.m_data[0] + m_data[1] * other.m_data[1] + m_data[2] * other.m_data[2];
}

Vector3 Vector3::cross(const Vector3& other) const
{
    const f32 f1 = m_data[1] * other.m_data[2] - other.m_data[1] * m_data[2];
    const f32 f2 = m_data[2] * other.m_data[0] - other.m_data[2] * m_data[0];
    const f32 f3 = m_data[0] * other.m_data[1] - other.m_data[0] * m_data[1];

    return {f1, f2, f3};
}

void Vector3::normalize()
{
    const f32 mag = 1 / magnitude();
    m_data[0] = m_data[0] * mag;
    m_data[1] = m_data[1] * mag;
    m_data[2] = m_data[2] * mag;
}

void Vector3::clampup() {
    m_data[0] = std::max(m_data[0], 0.0f);
    m_data[1] = std::max(m_data[1], 0.0f);
    m_data[2] = std::max(m_data[2], 0.0f);
}

void Vector3::clampdown() {
    m_data[0] = std::min(m_data[0], 1.0f);
    m_data[1] = std::min(m_data[1], 1.0f);
    m_data[2] = std::min(m_data[2], 1.0f);
}

void Vector3::clamp() {
    clampdown();
    clampup();
}

std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
    os << "[";
    for (u32 i = 0; i < 3; ++i) {
        os << vector.m_data[i];
        if (i != 2)
            os << ", ";
    }
    os << "]";
    return os;
}

Vector3 operator+(const Vector3& self, const Vector3& other)
{
    return {self.m_data[0] + other.m_data[0], self.m_data[1] + other.m_data[1], self.m_data[2] + other.m_data[2]};
}

Vector3 operator-(const Vector3& self, const Vector3& other)
{
    return {self.m_data[0] - other.m_data[0], self.m_data[1] - other.m_data[1], self.m_data[2] - other.m_data[2]};
}

Vector3 operator+(const Vector3 &self, f32 other) {
    return {self.m_data[0] + other, self.m_data[1] + other, self.m_data[2] + other};
}

Vector3 operator*(const Vector3 &self, f32 other) {
    return {self.m_data[0] * other, self.m_data[1] * other, self.m_data[2] * other};
}

Vector3 operator-(const Vector3 &self) {
    return {-self.m_data[0], -self.m_data[1], -self.m_data[2]};
}

Vector3 operator*(const Vector3 &self, const Vector3 &other) {
    return {self.m_data[0] * other.m_data[0], self.m_data[1] * other.m_data[1], self.m_data[2] * other.m_data[2]};
}

Vector3 operator/(const Vector3 &self, const Vector3 &other) {
    return {self.m_data[0] / other.m_data[0], self.m_data[1] / other.m_data[1], self.m_data[2] / other.m_data[2]};
}

Vector3 operator*(f32 other, const Vector3 &self) {
    return self * other;
}


