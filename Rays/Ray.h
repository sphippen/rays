#ifndef SPR_RAY_H
#define SPR_RAY_H

#include "Vec3.h"

namespace spr
{
  class Ray
  {
   public:
    Vec3 o;
    Vec3 d;

    Ray();
    Ray(Vec3 o, Vec3 d);
  };
}

#endif