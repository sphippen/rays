#include <cmath>
#include "Vec3.h"

namespace spr
{
  Vec3::Vec3() : x(0.0), y(0.0), z(0.0) {}
  Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

  Vec3& Vec3::operator+=(spr::Vec3 a)
  {
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
  }

  Vec3& Vec3::operator-=(spr::Vec3 a)
  {
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
  }

  Vec3 Vec3::operator-()
  {
    return Vec3(-x, -y, -z);
  }

  void Vec3::scale(double s)
  {
    x *= s;
    y *= s;
    z *= s;
  }

  Vec3 Vec3::scaled(double s)
  {
    Vec3 v(*this);
    v.scale(s);
    return v;
  }

  double Vec3::norm() const
  {
    return sqrt(x*x + y*y + z*z);
  }

  void Vec3::normalize()
  {
    double divBy = norm();
    x /= divBy;
    y /= divBy;
    z /= divBy;
  }

  Vec3 Vec3::normalized() const
  {
    Vec3 v(*this);
    v.normalize();
    return v;
  }

  Vec3 Vec3::pow(double c) const
  {
    return Vec3(::pow(x, c), ::pow(y, c), ::pow(z, c));
  }

  double Vec3::dot(Vec3 a) const
  {
    return x*a.x + y*a.y + z*a.z;
  }

  Vec3 Vec3::cross(Vec3 a) const
  {
    return Vec3(y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x);
  }

  double Vec3::distance(Vec3 a) const
  {
    return (*this - a).norm();
  }

  Vec3 Vec3::zero() { return Vec3(0.0, 0.0, 0.0); }

  Vec3 Vec3::black() { return Vec3(0.0, 0.0, 0.0); }
  Vec3 Vec3::red() { return Vec3(1.0, 0.0, 0.0); }
  Vec3 Vec3::green() { return Vec3(0.0, 1.0, 0.0); }
  Vec3 Vec3::blue() { return Vec3(0.0, 0.0, 1.0); }
  Vec3 Vec3::yellow() { return Vec3(1.0, 1.0, 0.0); }
}

spr::Vec3 operator+(spr::Vec3 a, spr::Vec3 b)
{
  a += b;
  return a;
}

spr::Vec3 operator-(spr::Vec3 a, spr::Vec3 b)
{
  a -= b;
  return a;
}