#include "ShadeRec.h"

namespace spr
{
  ShadeRec::ShadeRec(World& w) : hitAnObject(false), localHitPoint(), normal(), color(Vec3::black()), w(w) {}
}
