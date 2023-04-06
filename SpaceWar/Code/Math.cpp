#include "Math.h"
#include <cmath>

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::UnitX = Vector2(1.0f, 0.0f);
const Vector2 Vector2::UnitY = Vector2(0.0f, 1.0f);
const Vector2 Vector2::NegUnitX = Vector2(-1.0f, 0.0f);
const Vector2 Vector2::NegUnitY = Vector2(0.0f, -1.0f);

void Vector2::Set(const float &x_, const float &y_)
{
    x = x_;
    y = y_;
}

Vector2 Vector2::operator+(const Vector2 &v) const
{
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 &v) const
{
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const float &number) const
{
    return Vector2(x * number, y * number);
}

Vector2 operator*(const float &number, const Vector2 &v)
{
    return Vector2(v.x * number, v.y * number);
}

float Vector2::operator*(const Vector2 &v) const
{
    return x * v.x + y * v.y;
}

Vector2 Vector2::operator/(const float &number) const
{
    return Vector2(x / number, y / number);
}

Vector2 &Vector2::operator+=(const Vector2 &v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2 &Vector2::operator*=(const float &number)
{
    x *= number;
    y *= number;
    return *this;
}

Vector2 &Vector2::operator/=(const float &number)
{
    x /= number;
    y /= number;
    return *this;
}

float Vector2::Length() const
{
    return sqrtf(x * x + y * y);
}

float Vector2::LengthSquared() const
{
    return x * x + y * y;
}

void Vector2::Normalize()
{
    float length = Length();
    x /= length;
    y /= length;
}

Vector2 Vector2::Normalize(const Vector2 &v)
{
    float length = v.Length();
    return Vector2(v.x / length, v.y / length);
}

Vector2 Vector2::Lerp(const Vector2 &a, const Vector2 &b, const float &f)
{
    return a + f * (b - a);
}

Vector2 Vector2::Reflcet(const Vector2 &a, const Vector2 &n)
{
    return a - 2.0f * (a * n) * n;
}
