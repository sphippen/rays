#include "ViewPlane.h"

#include <cassert>

namespace spr
{
  ViewPlane::ViewPlane() : hres_(1), vres_(1), s_(1.0), gamma_(1.0), invGamma_(1.0) {}

  int ViewPlane::hres() const
  {
    return hres_;
  }
  void ViewPlane::setHres(int hres)
  {
    assert(hres > 0 && "hres must be positive");
    hres_ = hres;
  }

  int ViewPlane::vres() const
  {
    return vres_;
  }
  void ViewPlane::setVres(int vres)
  {
    assert(vres > 0 && "vres must be positive");
    vres_ = vres;
  }

  float ViewPlane::pixelSize() const
  {
    return s_;
  }
  void ViewPlane::setPixelSize(float pixelSize)
  {
    assert(pixelSize > 0 && "pixelSize must be positive");
    s_ = pixelSize;
  }

  float ViewPlane::gamma() const
  {
    return gamma_;
  }
  void ViewPlane::setGamma(float gamma)
  {
    assert(gamma > 0.0 && "gamma must be positive");
    gamma_ = gamma;
    invGamma_ = 1.0f / gamma;
  }

  float ViewPlane::invGamma() const
  {
    return invGamma_;
  }
  void ViewPlane::setInvGamma(float invGamma)
  {
    assert(invGamma > 0.0 && "invGamma must be positive");
    invGamma_ = invGamma;
    gamma_ = 1.0 / invGamma;
  }

}