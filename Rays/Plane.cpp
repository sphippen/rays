#include "Plane.h"

#include "constants.h"
#include "Ray.h"
#include "ShadeRec.h"

namespace spr
{
  Plane::Plane() : point(), normal() {}
  Plane::Plane(Vec3 point, Vec3 normal) : point(point), normal(normal) {}

  bool Plane::hit(Ray r, double& tmin, ShadeRec& sr) const
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