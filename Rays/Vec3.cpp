#include <cmath>
#include "Vec3.h"

namespace spr {

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