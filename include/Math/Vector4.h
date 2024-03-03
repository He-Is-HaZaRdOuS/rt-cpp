#pragma once
#include <ostream>

class Vector4 {
public:
	Vector4();
	Vector4(float f1, float f2, float f3);
	Vector4(float f1, float f2, float f3, float f4);
	Vector4(const Vector4& other);

	~Vector4() = default;

	static Vector4 Zero();

	/* Accessors */
	float get_x() const { return m_data[0]; }
	float get_y() const { return m_data[1]; }
	float get_z() const { return m_data[2]; }
	float get_w() const { return m_data[3]; }
	float get_r() const { return m_data[0]; }
	float get_g() const { return m_data[1]; }
	float get_b() const { return m_data[2]; }
	float get_a() const { return m_data[3]; }
				  
	/* Mutators */
	void set_x(float x) { m_data[0] = x; }
	void set_y(float y) { m_data[1] = y; }
	void set_z(float z) { m_data[2] = z; }
	void set_w(float w) { m_data[3] = w; }
	void set_r(float r) { m_data[0] = r; }
	void set_g(float g) { m_data[1] = g; }
	void set_b(float b) { m_data[2] = b; }
	void set_a(float a) { m_data[3] = a; }

	float magnitude() const;
	float dot(const Vector4& other) const;
	Vector4 cross(const Vector4& other) const;
	Vector4 cross_zero(const Vector4& other) const;
	void normalize();

	friend std::ostream& operator<<(std::ostream& os, const Vector4& vector);
	friend Vector4 operator+(const Vector4& self, const Vector4& other);
	friend Vector4 operator-(const Vector4& self, const Vector4& other);

private:
	float m_data[4];
};
