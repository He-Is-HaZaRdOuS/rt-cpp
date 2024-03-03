#pragma once
#include "Macros.h"
#include <ostream>

class Vector4 {
public:
	Vector4();
	Vector4(f32 f1, f32 f2, f32 f3);
	Vector4(f32 f1, f32 f2, f32 f3, f32 f4);
	Vector4(const Vector4& other);

	~Vector4() = default;

	static Vector4 Zero();

	/* Accessors */
	[[nodiscard]] f32 get_x() const { return m_data[0]; }
	[[nodiscard]] f32 get_y() const { return m_data[1]; }
	[[nodiscard]] f32 get_z() const { return m_data[2]; }
	[[nodiscard]] f32 get_w() const { return m_data[3]; }
	[[nodiscard]] f32 get_r() const { return m_data[0]; }
	[[nodiscard]] f32 get_g() const { return m_data[1]; }
	[[nodiscard]] f32 get_b() const { return m_data[2]; }
	[[nodiscard]] f32 get_a() const { return m_data[3]; }
				  
	/* Mutators */
	void set_x(f32 x) { m_data[0] = x; }
	void set_y(f32 y) { m_data[1] = y; }
	void set_z(f32 z) { m_data[2] = z; }
	void set_w(f32 w) { m_data[3] = w; }
	void set_r(f32 r) { m_data[0] = r; }
	void set_g(f32 g) { m_data[1] = g; }
	void set_b(f32 b) { m_data[2] = b; }
	void set_a(f32 a) { m_data[3] = a; }

	[[nodiscard]] f32 magnitude() const;
	[[nodiscard]] f32 dot(const Vector4& other) const;
	[[nodiscard]] Vector4 cross(const Vector4& other) const;
	[[nodiscard]] Vector4 cross_zero(const Vector4& other) const;
	void normalize();

	friend std::ostream& operator<<(std::ostream& os, const Vector4& vector);
	friend Vector4 operator+(const Vector4& self, const Vector4& other);
	friend Vector4 operator-(const Vector4& self, const Vector4& other);

private:
	f32 m_data[4];
};
