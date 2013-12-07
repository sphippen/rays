#include "GeometricObject.h"

namespace spr
{
  Vec3 GeometricObject::color() const
  {
    return color_;
  }

  void GeometricObject::setColor(Vec3 color)
  {
    color_ = color;
  }
}