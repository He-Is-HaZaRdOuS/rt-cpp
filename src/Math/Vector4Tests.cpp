#include "Math/Vector4.h"
#include <Doctest/doctest.h>

TEST_CASE("Creating a Vector4 using empty constructor") {
    Vector4 vec{};

    CHECK_EQ(vec.get_x(), .0f);
    CHECK_EQ(vec.get_y(), .0f);
    CHECK_EQ(vec.get_z(), .0f);
    CHECK_EQ(vec.get_w(), .0f);
}

TEST_CASE("Creating a Vector4 using x,y,z constructor") {
    Vector4 vec{1.0f, 2.0f, 3.0f};

    CHECK_EQ(vec.get_x(), 1.0f);
    CHECK_EQ(vec.get_y(), 2.0f);
    CHECK_EQ(vec.get_z(), 3.0f);
    CHECK_EQ(vec.get_w(), 1.0f);
}

TEST_CASE("Creating a Vector4 using x,y,z,w constructor") {
    Vector4 vec{1.0f, 2.0f, 3.0f, 4.0f};

    CHECK_EQ(vec.get_x(), 1.0f);
    CHECK_EQ(vec.get_y(), 2.0f);
    CHECK_EQ(vec.get_z(), 3.0f);
    CHECK_EQ(vec.get_w(), 4.0f);
}

TEST_CASE("Creating a Vector4 using copy constructor") {
    Vector4 vec{Vector4(1.0f, 2.0f, 3.0f, 4.0f)};

    CHECK_EQ(vec.get_x(), 1.0f);
    CHECK_EQ(vec.get_y(), 2.0f);
    CHECK_EQ(vec.get_z(), 3.0f);
    CHECK_EQ(vec.get_w(), 4.0f);
}

TEST_CASE("Magnitude of a Vector4") {
    Vector4 vec{9.0f, 12.0f, 8.0f, 144.0f};
    // Pythagorean triples
    // 9-12-15
    // 8-15-17
    // 17-144-145

    CHECK_EQ(vec.magnitude(), 17.0f);
}

TEST_CASE("Magnitude3 of a Vector4") {
    Vector4 vec{9.0f, 12.0f, 8.0f, 144.0f};
    // Pythagorean triples
    // 9-12-15
    // 8-15-17
    // 17-144-145

    CHECK_EQ(vec.magnitude(), 17.0f);
}

TEST_CASE("Dot product of two Vectors") {
    Vector4 v1{1.0f, 2.0f, 3.0f, 4.0f};
    Vector4 v2{3.0f, 5.0f, 7.0f, 9.0f};

    CHECK_EQ(v1.dot(v2), 34.0f);
}

TEST_CASE("Cross product of two Vectors") {
    Vector4 v1{1.0f, 2.0f, 3.0f, .0f};
    Vector4 v2{3.0f, 5.0f, 7.0f, .0f};

    CHECK_EQ(v1.cross(v2), Vector4(-1.f, 2.f, -1.f, 0.0f));
}

TEST_CASE("Normalizing a vector") {
    Vector4 vec{5.0f, 10.0f, 15.0f, .0f};

    vec.normalize();

    CHECK_EQ(vec.magnitude(), 1.0f);
}

/*
 * Overloaded operator tests
 */

TEST_CASE("Vector equality (v == u)") {
    Vector4 v{2.0f, 4.0f, 6.0f, 8.0f};
    Vector4 u{2.0f, 4.0f, 6.0f, 8.0f};

    CHECK_EQ(v == u, true);
    CHECK_EQ(v != u, false);
}

TEST_CASE("Vector inequality (v != u)") {
    Vector4 v{2.0f, 4.0f, 6.0f, 10.0f};
    Vector4 u{3.0f, 5.0f, 10.0f, .0f};

    CHECK_EQ(v == u, false);
    CHECK_EQ(v != u, true);
}

TEST_CASE("Vector addition (v + u)") {
    Vector4 v{2.0f, 4.0f, 6.0f, 10.0f};
    Vector4 u{3.0f, 5.0f, 10.0f, .0f};

    CHECK_EQ(v + u, Vector4(5.f, 9.f, 16.f, 10.f));
}

TEST_CASE("Vector Subtraction (v - u)") {
    Vector4 v{2.0f, 4.0f, 6.0f, 10.0f};
    Vector4 u{3.0f, 5.0f, 10.0f, .0f};

    CHECK_EQ(v - u, Vector4(-1.f, -1.f, -4.f, 10.f));
}

TEST_CASE("Vector scaling (v * float(x))") {
    Vector4 v{2.0f, 4.0f, 6.0f, 10.0f};

    CHECK_EQ(v * 2, Vector4(4.f, 8.f, 12.f, 10.f));
}

TEST_CASE("Vector scaling (v / float(x))") {
    Vector4 v{2.0f, 4.0f, 6.0f, 10.0f};

    CHECK_EQ(v / 2, Vector4(1.f, 2.f, 3.f, 5.f));
}
