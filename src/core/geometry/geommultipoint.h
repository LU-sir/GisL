//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMMULTIPOINT_H
#define GISL_GEOMMULTIPOINT_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"

namespace GisL {

    class GeomMultiPoint : public AbstractGeometry {
    public:
        explicit GeomMultiPoint( OGRMultiPoint &ogrMultiPoint );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        ~GeomMultiPoint( );

        OGRGeometry *getGeometry( ) const override;

    private:
        OGRMultiPoint *pmMultiPoint;
    };

}

#endif //GISL_GEOMMULTIPOINT_H