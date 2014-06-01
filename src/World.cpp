#include "World.h"

#include "constants.h"
#include "Ray.h"
#include "Tracer.h"
#include "MultipleObjects.h"
#include "ShadeRec.h"
#include "GeometricObject.h"
#include "Sphere.h"
#include "Plane.h"

using std::unique_ptr;
using std::make_shared;

namespace spr
{
  World::World() {} 
  void World::build(int hres, int vres)
  {
    vp.setHres(hres);
    vp.setVres(vres);
    vp.setPixelSize(1.0);
    vp.setGamma(1.0);

    bgColor = Vec3::black();
    tracer = unique_ptr<Tracer>(new MultipleObjects(*this));

    auto sph = make_shared<Sphere>();
    sph->setCenter(Vec3(0, 0, 0));
    sph->setRadius(40);
    sph->setColor(Vec3::yellow());
    addObject(sph);

    sph = make_shared<Sphere>();
    sph->setCenter(Vec3(-29, 29, -20));
    sph->setRadius(27);
    sph->setColor(Vec3::orange());
    addObject(sph);

    sph = make_shared<Sphere>();
    sph->setCenter(Vec3(20, -40, -30));
    sph->setRadius(34);
    sph->setColor(Vec3::green());
    addObject(sph);
  }

  void World::addObject(std::shared_ptr<GeometricObject> obj)
  {
    objects.push_back(obj);
  }

  ShadeRec World::hitBareBonesObjects(Ray ray) const
  {
    ShadeRec sr(*this);
    double t;
    double tMin = kHugeValue;
    int nObj = objects.size();

    for (int j = 0; j < nObj; ++j) {
      if (objects[j]->hit(ray, t, sr) && (t < tMin)) {
        sr.hitAnObject = true;
        sr.color = objects[j]->color();
        tMin = t;
      }
    }

    return sr;
  }

  void World::render_scene(int xMin, int xMax, int yMin, int yMax, std::function<void (int x, int y, Vec3 color)> setPixel) const
  {
    Ray ray;
    double zw = 100.0;

    ray.d = Vec3(0.0, 0.0, -1.0);

    for (int r = 0; r < vp.vres(); ++r) {
      for (int c = 0; c < vp.hres(); ++c) {
        double x = vp.pixelSize() * (c + 0.5 - vp.hres()*0.5);
        double y = vp.pixelSize() * (r + 0.5 - vp.vres()*0.5);
        ray.o = Vec3(x, y, zw);
        Vec3 pixelColor = tracer->traceRay(ray);

        pixelColor = pixelColor.pow(vp.invGamma());
        setPixel(c, r, pixelColor);
      }
    }
  }
}