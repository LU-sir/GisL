/*!
 * @author tau 
 * @date 12/20/20
*/

#include "vectorfeature.h"

#include <ogr_feature.h>

#include "geometry/geompoint.h"
#include "geometry/geomlinestring.h"
#include "geometry/geompolygon.h"
#include "geometry/geommultipoint.h"
#include "geometry/geommultilinestring.h"
#include "geometry/geommultipolygon.h"
#include "geometry/geometryfactory.h"
#include "../utils/ptroperate.h"

namespace gisl {

    int VectorFeature::fidInFeature = 10100;

    void VectorFeature::seed( const int fidInLayer ) {
        VectorFeature::fidInFeature = fidInLayer * 100;
    }

    VectorFeature::VectorFeature( OGRFeature &poFeature ) {

        fid = ++VectorFeature::fidInFeature;
        pmFeature = &poFeature;

        pmFeatureProperty = new FeatureProperty( *pmFeature );

        pmGeometry = nullptr;
        geoType = AbstractGeometry::WkbType::NoGeometry;
        defineGeo();
        pmGeometry->setFeatureName( pmFeature->GetFieldAsString( "JDNAME" ));
    }

    void VectorFeature::defineGeo( ) {
        OGRGeometry *pGeom = pmFeature->GetGeometryRef();
        auto type = pGeom->getGeometryType();
        switch ( type ) {
            default:
                break;
            case wkbUnknown:

            case wkbNone: {
//                mError = MError::GisLError::ErrGeometry;
                break;
            }
            case wkbPoint: {
                pmGeometry = new GeomPoint( *pGeom->toPoint());
                break;
            }
            case wkbLineString: {
                pmGeometry = new GeomLineString( *pGeom->toLineString());
                break;
            }
            case wkbPolygon: {
                pmGeometry = new GeomPolygon( *pGeom->toPolygon());
                break;
            }
            case wkbMultiPoint: {
                pmGeometry = new GeomMultiPoint( *pGeom->toMultiPoint());
                break;
            }
            case wkbMultiLineString: {
                pmGeometry = new GeomMultiLineString( *pGeom->toMultiLineString());
                break;
            }
            case wkbMultiPolygon: {
                pmGeometry = new GeomMultiPolygon( *pGeom->toMultiPolygon());
                break;
            }
        }
    }

    VectorFeature &VectorFeature::operator=( const VectorFeature &rhs ) {
        return *this;
    }

    VectorFeature::~VectorFeature( ) {
        PtrOperate::clear( pmFeatureProperty );
        PtrOperate::clear( pmGeometry );

    }

    int VectorFeature::getFid( ) const {
        return fid;
    }

    FeatureProperty *VectorFeature::getPmFeatureProperty( ) const {
        return pmFeatureProperty;
    }

    void VectorFeature::draw( PainterFactory &p ) {
        pmGeometry->draw( p );
    }

    Rectangle *VectorFeature::boundary( ) {
//        if ( pmGeometry == nullptr ) {
//            return nullptr;
//        } else {
        auto p = pmGeometry->boundary();
        return p;
//        }
    }

    std::string VectorFeature::getFieldAsString( const std::string &s ) {
        return pmFeature->GetFieldAsString( s.c_str());
    }

}