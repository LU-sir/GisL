//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMPOINT_H
#define GISL_GEOMPOINT_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"
#include "../../utils/ptroperate.h"

namespace GisL {
    class GeomPoint : public AbstractGeometry {
    public:
        explicit GeomPoint( OGRPoint &ogrPoint );

        ~GeomPoint( );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        OGRGeometry *getGeometry( ) const override;

    private:
        OGRPoint *pmPoint;
    };

}

#endif //GISL_GEOMPOINT_H