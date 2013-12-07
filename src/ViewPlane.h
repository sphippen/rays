#ifndef SPR_VIEW_PLANE_H
#define SPR_VIEW_PLANE_H

namespace spr
{
  class ViewPlane
  {
   public:
    ViewPlane();

    int hres() const;
    void setHres(int hres);
    int vres() const;
    void setVres(int vres);

    float pixelSize() const;
    void setPixelSize(float pixelSize);

    float gamma() const;
    void setGamma(float gamma);
    float invGamma() const;
    void setInvGamma(float invGamma);

   private:
    int hres_;
    int vres_;
    float s_;
    float gamma_;
    float invGamma_;
  };
}

#endif