#include "Plane.h"

#include "Ray.h"
#include "ShadeRec.h"

static const double kEpsilon = 1e-6;

namespace spr
{
  Plane::Plane() : point(), normal() {}
  Plane::Plane(Vec3 point, Vec3 normal) : point(point), normal(normal) {}

  bool Plane::hit(Ray r, double& tmin, ShadeRec& sr)
  {
    double t = (point - r.o).dot(normal) / r.d.dot(normal);

    if (t > kEpsilon) {
      tmin = t;
      sr.normal = normal;
      sr.localHitPoint = r.o + r.d.scaled(t);

      return true;
    }
    else {
      return false;
    }
  }

}