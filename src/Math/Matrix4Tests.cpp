#include "Math/Matrix4.h"
#include <Doctest/doctest.h>

TEST_CASE("Empty constructor initializes identity matrix") {
    Matrix4 mat{};

    int checked = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        if (mat.m_data[i][j] == 0.0f)
            checked++;

    CHECK_EQ(checked, 12);
    if (mat.m_data[0][0] == 1.0f) checked++;
    if (mat.m_data[1][1] == 1.0f) checked++;
    if (mat.m_data[2][2] == 1.0f) checked++;
    if (mat.m_data[3][3] == 1.0f) checked++;
    CHECK_EQ(checked, 16);
}

TEST_CASE("Multiplying a matrix with a vector") {
    Matrix4 m{
            9, 2, 8, 8,
            2, 4, 7, 7,
            1, 7, 0, 0,
            2, 1, 8, 9,
    };
    Vector4 v{6, 3, 4, 7};
    Vector4 res{78, 59, 125, 132};

    CHECK_EQ(m * v, res);
}

TEST_CASE("Multiplying matrices") {
    Matrix4 a{
            9, 2, 8, 8,
            2, 4, 7, 7,
            1, 7, 0, 0,
            2, 1, 8, 9,
    };
    Matrix4 b{
            2, 9, 3, 3,
            4, 1, 3, 5,
            2, 6, 5, 7,
            7, 8, 5, 6,
    };
    Matrix4 ab{
            45, 64, 103, 106,
            51, 38, 79, 84,
            49, 70, 114, 121,
            96, 87, 160, 166,
    };

    CHECK_EQ(a * b, ab);
}


TEST_CASE("Empty constructor initializes identity matrix") {
    Matrix4 mat{};
    Vector4 v{5.5f, 15.6f, 30.3f};

    Vector4 u = mat * v;

    CHECK_EQ(u, v);
}

TEST_CASE("Copying a matrix via constructor") {
    Matrix4 mat{};
    mat.m_data[0][3] = 3.0f;
    mat.m_data[3][0] = 5.5f;

    Matrix4 copy{mat};

    CHECK_EQ(copy, mat);
}

TEST_CASE("Translating a point") {
    Matrix4 mat = Matrix4::Translate(3.0f, -5.5f, 7.25f);
    Vector4 v{10.0f, 10.0f, 10.0f, 1.0f};
    Vector4 u{13.0f, 4.5f, 17.25f, 1.0f};

    v = mat * v;

    CHECK_EQ(v, u);
}

TEST_CASE("Scaling a point") {
    Matrix4 mat = Matrix4::Scale(2.0f, -1.0f, 0.5f);
    Vector4 v{10.0f, 10.0f, 10.0f};
    Vector4 u{20.0f, -10.0f, 5.0f};

    v = mat * v;

    CHECK_EQ(v, u);
}

TEST_CASE("Rotating a point around X axis") {
    Matrix4 mat = Matrix4::RotateX(90);
    Vector4 v{1.0f, 2.0f, 3.0f, 1.0f};
    Vector4 u{1.0f, -3.0f, 2.0f, 1.0f};

    v = mat * v;

    CHECK_EQ(v, u);
}

TEST_CASE("Rotating a point around Y axis") {
    Matrix4 mat = Matrix4::RotateY(90);
    Vector4 v{1.0f, 2.0f, 3.0f};
    Vector4 u{3.0f, 2.0f, -1.0f};

    v = mat * v;

    CHECK_EQ(v, u);
}

TEST_CASE("Rotating a point around Z axis") {
    Matrix4 mat = Matrix4::RotateZ(90);
    Vector4 v{1.0f, 2.0f, 3.0f};
    Vector4 u{-2.0f, 1.0f, 3.0f};

    v = mat * v;

    CHECK_EQ(v, u);
}

TEST_CASE("Rotating a point around a vector #1") {
    Matrix4 mat = Matrix4::Rotate({0.0f, 1.0f, 0.0f}, 180);
    Vector4 v{1.0f, 3.0f, 0.0f, 1.0f};
    Vector4 u{-1.0f, 3.0f, 0.0f, 1.0f};

    v = mat * v;

    CHECK_EQ(v, u);
}

TEST_CASE("Determinant of a matrix #1") {
    Matrix4 mat{};

    CHECK_EQ(mat.det(), 1.0f);
}

TEST_CASE("Determinant of a matrix #2") {
    Matrix4 mat{};
    mat.m_data[0][1] = 3.0f;
    mat.m_data[1][0] = 2.0f;

    CHECK_EQ(mat.det(), -5.0f);
}

TEST_CASE("Compare Rotate and RotateX/Y/Z") {
    CHECK_EQ(Matrix4::Rotate({1, 0, 0}, 70), Matrix4::RotateX(70));
    CHECK_EQ(Matrix4::Rotate({1, 0, 0}, 150), Matrix4::RotateX(150));
    CHECK_EQ(Matrix4::Rotate({1, 0, 0}, -999), Matrix4::RotateX(-999));
    CHECK_EQ(Matrix4::Rotate({0, 1, 0}, 70), Matrix4::RotateY(70));
    CHECK_EQ(Matrix4::Rotate({0, 1, 0}, 150), Matrix4::RotateY(150));
    CHECK_EQ(Matrix4::Rotate({0, 1, 0}, -999), Matrix4::RotateY(-999));
    CHECK_EQ(Matrix4::Rotate({0, 0, 1}, 70), Matrix4::RotateZ(70));
    CHECK_EQ(Matrix4::Rotate({0, 0, 1}, 150), Matrix4::RotateZ(150));
    CHECK_EQ(Matrix4::Rotate({0, 0, 1}, -999), Matrix4::RotateZ(-999));
}

TEST_CASE("Composite Transformations") {
    Matrix4 mat{};
    mat = Matrix4::Translate(-1, 2, 4) * mat;
    mat = Matrix4::Scale(2, 3, 4) * mat;
    mat = Matrix4::RotateZ(90) * mat;

    Vector4 v{0, 0, 0, 1};
    Vector4 u{-6, -2, 16, 1};

    v = mat * v;

    CHECK_EQ(v, u);
}
