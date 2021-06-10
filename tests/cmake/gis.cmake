add_library(gis "")

target_sources(gis
        PRIVATE
        ../../src/core/provider/vectorprovider.cpp ../../src/core/vector/vectorlayer.cpp ../../src/core/vector/vectorfeature.cpp ../../src/core/spatialreference.cpp ../../src/core/geometry.cpp ../../src/core/geopoint.cpp ../../src/core/geoline.cpp ../../src/core/geopolygon.cpp ../../src/core/geomultipoint.cpp ../../src/core/geomultiline.cpp ../../src/core/geomultipolygon.cpp
        PUBLIC
        ../../src/core/provider/vectorprovider.h ../../src/core/vector/vectorlayer.h ../../src/core/vector/vectorfeature.h ../../src/core/spatialreference.h ../../src/core/geometry.h ../../src/core/geopoint.h ../../src/core/geoline.h ../../src/core/geopolygon.h ../../src/core/geomultipoint.h ../../src/core/geomultiline.h ../../src/core/geomultipolygon.h
        )

target_include_directories(gis
        PUBLIC
        ../../src/core
        )
