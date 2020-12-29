//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMPOLYGON_H
#define GISL_GEOMPOLYGON_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"

namespace GisL {

    class GeomPolygon : virtual public AbstractGeometry, virtual public OGRPolygon {
    public:
        explicit GeomPolygon( );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        ~GeomPolygon( ) override;

    private:

    };

}

#endif //GISL_GEOMPOLYGON_H
