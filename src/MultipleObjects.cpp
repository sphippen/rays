#include "MultipleObjects.h"

#include "World.h"
#include "Vec3.h"
#include "Ray.h"
#include "ShadeRec.h"

namespace spr
{
  MultipleObjects::MultipleObjects(World& world) : Tracer(world) {}

  Vec3 MultipleObjects::traceRay(Ray r) const
  {
    ShadeRec sr = world_.hitBareBonesObjects(r);
    if (sr.hitAnObject)
      return sr.color;
    else
      return world_.bgColor;
  }
}