#include "Sphere.h"

#include <cmath>
#include "Ray.h"
#include "ShadeRec.h"

static const double kEpsilon = 1e-6;

namespace spr
{
  Sphere::Sphere() : center(), radius(0.0) {}
  Sphere::Sphere(Vec3 center, double radius) : center(center), radius(radius) {}

  bool Sphere::hit(Ray r, double& tmin, ShadeRec& sr)
  {
    double a = r.d.dot(r.d);
    double b = 2 * ((r.o - center).dot(r.d));
    double c = (r.o-center).dot(r.o-center) - radius*radius;

    double discrim = b*b - 4*a*c;
    if (discrim < 0)
      return false;

    // Try the smaller root first
    double t = (-b - sqrt(discrim)) / (2.0 * a);
    if (t > kEpsilon) {
      tmin = t;
      sr.localHitPoint = r.o + r.d.scaled(t);
      sr.normal = (sr.localHitPoint - center).normalized();
      return true;
    }

    // The smaller root wasn't valid; try the larger one
    t = (-b + sqrt(discrim)) / (2.0 * a);
    if (t > kEpsilon) {
      tmin = t;
      sr.localHitPoint = r.o + r.d.scaled(t);
      sr.normal = (sr.localHitPoint - center).normalized();
      return true;
    }

    // If we got here, neither of the roots were valid
    return false;
  }
}