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
    virtual ~GeometricObject() {}
    virtual bool hit (Ray r, double& tmin, ShadeRec& sr) const = 0;
    Vec3 color() const;
    void setColor(Vec3 color);
   protected:
    Vec3 color_;
  };
}

#endif