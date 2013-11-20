#include "ShadeRec.h"

namespace spr
{
  ShadeRec::ShadeRec(const World& w) : hitAnObject(false), localHitPoint(), normal(), color(Vec3::black()), w(w) {}
}
