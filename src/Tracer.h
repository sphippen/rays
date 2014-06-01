#ifndef SPR_TRACER_H
#define SPR_TRACER_H

namespace spr
{
  class Vec3;
  class Ray;
  class World;
  class Tracer
  {
   public:
    Tracer(World& world);
    virtual ~Tracer() {}

    virtual Vec3 traceRay(Ray r) const;
   protected:
    World& world_;
  };
}

#endif