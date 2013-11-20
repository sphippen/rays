#include "Tracer.h"

#include "Vec3.h"
#include "World.h"
#include "Ray.h"

namespace spr
{
  Tracer::Tracer(World& world) : world_(world) {}

  Vec3 Tracer::traceRay(Ray r) const
  {
    return Vec3::black();
  }
}