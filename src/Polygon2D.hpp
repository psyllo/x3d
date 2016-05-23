#ifndef __X3D_POLYGON2D_HPP
#define __X3D_POLYGON2D_HPP

// See: l3d_0.4/source/app/lib/geom/polygon/polygon.h

#include "Rasterizer.hpp"

namespace x3d {
  class Polygon2D {
  public:
    Polygon2D() { }
    Polygon2D(const Polygon2D& r);
    virtual ~Polygon2D() { }
    virtual void draw(Rasterizer *r) { }
    virtual Polygon2D* clone() { return new Polygon2D(*this); }
  };
}

#endif
