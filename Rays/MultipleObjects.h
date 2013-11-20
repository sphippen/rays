#ifndef SPR_MULTIPLE_OBJECTS_H
#define SPR_MULTIPLE_OBJECTS_H

#include "Tracer.h"

namespace spr
{
  class World;
  class Vec3;
  class Ray;
  class MultipleObjects : public Tracer
  {
   public:
    MultipleObjects(World& world);

    virtual Vec3 traceRay(Ray r) const;
  };
}

#endif