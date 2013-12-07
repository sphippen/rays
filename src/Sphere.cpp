#include "Sphere.h"

#include <cmath>
#include <cassert>
#include "constants.h"
#include "Ray.h"
#include "ShadeRec.h"

namespace spr
{
  Sphere::Sphere() : center_(), radius_(0.0) {}
  Sphere::Sphere(Vec3 center, double radius) : center_(center), radius_(radius) {}

  Vec3 Sphere::center() const
  {
    return center_;
  }
  void Sphere::setCenter(Vec3 center)
  {
    center_ = center;
  }

  double Sphere::radius() const
  {
    return radius_;
  }
  void Sphere::setRadius(double radius)
  {
    assert(radius > 0.0 && "radius must be positive");
    radius_ = radius;
  }

  bool Sphere::hit(Ray r, double& tmin, ShadeRec& sr) const
  {
    double a = r.d.dot(r.d);
    double b = 2 * ((r.o - center_).dot(r.d));
    double c = (r.o-center_).dot(r.o-center_) - radius_*radius_;

    double discrim = b*b - 4*a*c;
    if (discrim < 0)
      return false;

    // Try the smaller root first
    double t = (-b - sqrt(discrim)) / (2.0 * a);
    if (t > kEpsilon) {
      tmin = t;
      sr.localHitPoint = r.o + r.d.scaled(t);
      sr.normal = (sr.localHitPoint - center_).normalized();
      return true;
    }

    // The smaller root wasn't valid; try the larger one
    t = (-b + sqrt(discrim)) / (2.0 * a);
    if (t > kEpsilon) {
      tmin = t;
      sr.localHitPoint = r.o + r.d.scaled(t);
      sr.normal = (sr.localHitPoint - center_).normalized();
      return true;
    }

    // If we got here, neither of the roots were valid
    return false;
  }
}