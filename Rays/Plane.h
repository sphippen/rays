#ifndef SPR_PLANE_H
#define SPR_PLANE_H

#include "GeometricObject.h"
#include "Vec3.h"

namespace spr
{
  class Ray;
  class ShadeRec;
  class Plane : public GeometricObject
  {
   public:
    Plane();
    Plane(Vec3 point, Vec3 normal);

    virtual bool hit(Ray r, double& tmin, ShadeRec& sr) const;
   private:
    Vec3 point;
    Vec3 normal;
  };
}

#endif