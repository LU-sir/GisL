//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMMULTIPOLYGON_H
#define GISL_GEOMMULTIPOLYGON_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"

namespace GisL {

    class GeomMultiPolygon : public AbstractGeometry {
    public:
        explicit GeomMultiPolygon( OGRMultiPolygon &ogrMultiPolygon );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        ~GeomMultiPolygon( );

        OGRGeometry *getGeometry( ) const override;

    private:
        OGRMultiPolygon *pmMultiPolygon;

    };

}

#endif //GISL_GEOMMULTIPOLYGON_H
