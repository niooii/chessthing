#pragma once

#include <cmath>

class Vector2 {

public:
    double x{}, y{};
    Vector2();
    Vector2(double x, double y);

    void normalize();

    double magnitude();

    double dot(Vector2 const& vec);
    Vector2 operator/(double d);
    Vector2 operator-(Vector2 const& vec);
    Vector2 operator-();
    Vector2 operator+(Vector2 const& vec);
    Vector2 operator*(double d);

    bool operator==(Vector2& v);
};