#ifndef SPR_GEOMETRIC_OBJECT_H
#define SPR_GEOMETRIC_OBJECT_H

#include "Vec3.h"

namespace spr
{
  class Ray;
  class ShadeRec;
  class GeometricObject
  {
   public:
    virtual bool hit (Ray r, double& tmin, ShadeRec& sr) const = 0;
   protected:
    Vec3 color;
  };
}

#endif