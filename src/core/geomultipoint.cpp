//
// Created by omega on 14/12/2020.
//

#include "geomultipoint.h"

namespace GisL {

    GeoMultiPoint::GeoMultiPoint( OGRGeometry &poGeometry ) : Geometry( poGeometry ) {

    }

    GeoMultiPoint::~GeoMultiPoint( ) {

    }
}