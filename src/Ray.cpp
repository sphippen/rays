#include "Ray.h"

namespace spr
{
  Ray::Ray() : o(), d() {}
  Ray::Ray(Vec3 o, Vec3 d) : o(o), d(d) {}
}