#include "Vector2.h"

Vector2::Vector2() : x(0), y(0)
{

}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

float Vector2::Magnitude() const
{
    return std::sqrt(x * x + y * y);
}

float Vector2::SqrMagnitude() const
{
    return (x * x + y * y);
}

float Vector2::DistanceTo(const Vector2& v) const
{
    int xDiff = this->x - v.x;
    int yDiff = this->y - v.y;
    return std::sqrt(xDiff * xDiff + yDiff * yDiff);
}

float Vector2::SqrDistanceTo(const Vector2& v) const
{
    int xDiff = this->x - v.x;
    int yDiff = this->y - v.y;
    return (xDiff * xDiff + yDiff * yDiff);
}

float Vector2::Dot(const Vector2& v)
{
    return (x * v.x) + (y * v.y);
}

float Vector2::GetAngle()
{
    return RadToDeg(std::atan2(x, y));
}

double Vector2::DegToRad(double degrees)
{
    return (M_PI / 180) * degrees;
}

double Vector2::RadToDeg(double radians)
{
    return (180 / M_PI) * radians;
}

Vector2 Vector2::Normalize()
{
    float mag = this->Magnitude();
    return Vector2(x / mag, y / mag);
}

std::string Vector2::ToString() const
{
    std::string s = "(";
    s.push_back(x);
    s.push_back(',');
    s.push_back(y);
    s.push_back(')');
    return s;
}

Vector2 Vector2::Rotate(double degrees) const
{
    float rad = DegToRad(degrees);
    float newX = x * cos(rad) - y * sin(rad);
    float newY = x * sin(rad) + y * cos(rad);

    return Vector2(newX, newY);
}

Vector2 operator*(const double multiplier, const Vector2& v1)
{
    return Vector2(v1.x * multiplier, v1.y * multiplier);
}

Vector2 operator*(const Vector2& v1, const double multiplier)
{
    return Vector2(v1.x * multiplier, v1.y * multiplier);
}

bool operator<(const Vector2& v1, const Vector2& v2)
{
    return v1.SqrMagnitude() < v2.SqrMagnitude();
}

bool operator>(const Vector2& v1, const Vector2& v2)
{
    return v1.SqrMagnitude() > v2.SqrMagnitude();
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& v2)
{
    x += v2.x;
    y += v2.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v2)
{
    x -= v2.x;
    y -= v2.y;
    return *this;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
    return Vector2(v1.x - v2.x, v1.y - v2.y);;
}

std::ostream& operator<< (std::ostream& out, const Vector2& v)
{
    out << '(' << v.x << ',' << v.y << ')';
    return out;
}