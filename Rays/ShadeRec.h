#ifndef SPR_SHADE_REC_H
#define SPR_SHADE_REC_H

#include "Vec3.h"

namespace spr
{
  class World;
  class ShadeRec
  {
   public:
    bool hitAnObject;
    Vec3 localHitPoint;
    Vec3 normal;
    Vec3 color;
    World& w;

    ShadeRec(World& w);
  };
}

#endif