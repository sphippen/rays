#ifndef SPR_VEC3_H
#define SPR_VEC3_H

namespace spr
{

  class Vec3
  {
   public:
    double x;
    double y;
    double z;
   
    Vec3(double x, double y, double z);

    Vec3& operator+=(spr::Vec3 a);
    Vec3& operator-=(spr::Vec3 a);

    Vec3 operator-();

    void scale(double s);

    double norm() const;

    void normalize();
    Vec3 normalized() const;

    double dot(Vec3 a) const;
    Vec3 cross(Vec3 a) const;

    double distance(Vec3 a) const;

    static Vec3 zero();
  };

}

spr::Vec3 operator+(spr::Vec3 a, spr::Vec3 b);
spr::Vec3 operator-(spr::Vec3 a, spr::Vec3 b);

#endif
