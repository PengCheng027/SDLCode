#pragma once
#ifndef MATH_HEAD
#define MATH_HEAD
class Vector2
{
public:
    float x;
    float y;
    Vector2() : x(0.0f), y(0.0f){};
    Vector2(const float &x_, const float &y_) : x(x_), y(y_){};
    Vector2(const Vector2 &v) : x(v.x), y(v.y){};
    ~Vector2(){};

    // Set both x and y
    void Set(const float &x_, const float &y_);

    // Vector addition
    Vector2 operator+(const Vector2 &v) const;
    // Vector subtraction
    Vector2 operator-(const Vector2 &v) const;
    // Scalar multiplication
    Vector2 operator*(const float &number) const;
    friend Vector2 operator*(const float &number, const Vector2 &v);
    // Dot product
    float operator*(const Vector2 &v) const;
    // Scalar division
    Vector2 operator/(const float &number) const;

    // Vector addition
    Vector2 &operator+=(const Vector2 &v);
    // Vector subtraction
    Vector2 &operator-=(const Vector2 &v);
    // Scalar multiplication
    Vector2 &operator*=(const float &number);
    // Scalar division
    Vector2 &operator/=(const float &number);

    // Length of the vector
    float Length() const;
    // Length of the vector squared
    float LengthSquared() const;
    // Normalize the vector
    void Normalize();
    // Normalize the proveded vector
    static Vector2 Normalize(const Vector2 &v);
    // Lerp from vector a to vector b
    static Vector2 Lerp(const Vector2 &a, const Vector2 &b, const float &f);
    // Reflect vector a on vector b
    static Vector2 Reflcet(const Vector2 &a, const Vector2 &n);

    static const Vector2 Zero;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    static const Vector2 NegUnitX;
    static const Vector2 NegUnitY;
};
#endif // MATH_HEAD
