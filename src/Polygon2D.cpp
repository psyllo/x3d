#include "Polygon2D.hpp"


namespace x3d {

  Polygon2D::Polygon2D(const Polygon2D& r) {

    // TODO: Write copy constructor
    // Copied from: l3d_0.4/source/app/lib/geom/polygon/polygon.cc

    // //  iv_items_factory = new l3d_polygon_ivertex_items_factory;
    // //  ^^ error! why? what if the right hand side polygon has a different
    // //     factory? ask the factory to clone itself, too!!!!!

    // // iv_items_factory = r.iv_items_factory;
    // // ^^ error! why? the new polygon must have ITS OWN COPY of the
    // //    factory, not a reference to the old factory!

    // iv_items_factory = r.iv_items_factory->clone();
    // init(DEFAULT_IVERTICES_PER_POLY);

    // vlist = r.vlist;
    // *ivertices = *r.ivertices;
    // *clip_ivertices = *r.clip_ivertices;
    // *temp_clip_ivertices = *r.temp_clip_ivertices;
  }
}
