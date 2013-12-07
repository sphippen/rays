#ifndef SPR_WORLD_H
#define SPR_WORLD_H

#include <functional>
#include <memory>
#include <vector>
#include "Vec3.h"
#include "ViewPlane.h"
#include "Tracer.h"

namespace spr
{
  class Ray;
  class GeometricObject;
  class ShadeRec;
  class World
  {
   public:
    ViewPlane vp;
    Vec3 bgColor;
    std::unique_ptr<Tracer> tracer;
    std::vector<std::shared_ptr<GeometricObject> > objects;

    World();
    void build(int hres, int vres);
    void addObject(std::shared_ptr<GeometricObject> obj);

    ShadeRec hitBareBonesObjects(Ray ray) const;

    void render_scene(int xMin, int xMax, int yMin, int yMax, std::function<void (int x, int y, Vec3 color)> setPixel) const;
  };
}

#endif