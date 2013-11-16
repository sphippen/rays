#ifndef SPR_WORLD_H
#define SPR_WORLD_H

#include "Vec3.h"
#include "ViewPlane.h"
#include "Sphere.h"

namespace spr
{
  class Tracer;
  class World
  {
   public:
    ViewPlane vp;
    Vec3 bgColor;
    Sphere sphere;
    Tracer* tracer_ptr;

    World();
    void build();

    void render_scene(int hres, int vres) const;

    void display_pixel(int x, int y, Vec3 pxColor) const;
  };
}

#endif