#ifndef SPR_SPHERE_H
#define SPR_SPHERE_H

#include "GeometricObject.h"
#include "Vec3.h"

namespace spr
{
  class Ray;
  class ShadeRec;
  class Sphere : public GeometricObject
  {
   public:
    Sphere();
    Sphere(Vec3 center, double radius);

    virtual bool hit(Ray r, double& tmin, ShadeRec& sr) const;
   private:
    Vec3 center;
    double radius;
  };
}
#endif