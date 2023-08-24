#include "Vector2.h"

Vector2::Vector2() = default;

Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}

void Vector2::normalize() {
    using std::pow, std::sqrt;
    //magnitude of vec
    double m = magnitude();
    x /= m;
    y /= m;
}

double Vector2::magnitude() {
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vector2 Vector2::operator/(double d) {
    Vector2 vec(x / d, y / d);
    return vec;
}

Vector2 Vector2::operator-(Vector2 const& vec) {
    Vector2 vect(x - vec.x, y - vec.y);
    return vect;
}

Vector2 Vector2::operator-() {
    Vector2 vect(-x, -y);
    return vect;
}

Vector2 Vector2::operator+(Vector2 const& vec) {
    Vector2 vect(x + vec.x, y + vec.y);
    return vect;
}

Vector2 Vector2::operator*(double d) {
    Vector2 vect(x * d, y * d);
    return vect;
}

bool Vector2::operator==(Vector2& v)
{
    return this->x == v.x && this->y == v.y;
}

double Vector2::dot(const Vector2 &vec) {
    return this->x * vec.x + this->y * vec.y;
}
