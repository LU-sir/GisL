set(GISL_CORE_VACTOR_SRCS
        core/vector/featureproperty.cpp
        core/vector/featureproperty.h
        core/vector/layerpropertytable.cpp
        core/vector/layerpropertytable.h
        core/vector/vectorfeature.cpp
        core/vector/vectorfeature.h
        core/vector/vectorlayer.cpp
        core/vector/vectorlayer.h
        )
set(GISL_CORE_PROVIDER_SRCS
        core/provider/dataprovider.h
        core/provider/dataprovider.cpp
        core/provider/rasterprovider.cpp
        core/provider/rasterprovider.h
        core/provider/vectorprovider.cpp
        core/provider/vectorprovider.h
        )
set(GISL_CORE_LAYER_SRCS
        core/layer/layertree.cpp
        core/layer/layertree.h
        core/layer/layer.cpp
        core/layer/layer.h
        )
set(GISL_CORE_RASTER_SRCS
        core/raster/rasterband.cpp
        core/raster/rasterband.h
        )
set(GISL_CORE_GEO_SRCS
        core/geometry/abstractgeometry.cpp
        core/geometry/abstractgeometry.h
        core/geometry/geometryfactory.cpp
        core/geometry/geometryfactory.h
        core/geometry/geomlinestring.cpp
        core/geometry/geomlinestring.h
        core/geometry/geommultilinestring.cpp
        core/geometry/geommultilinestring.h
        core/geometry/geommultipoint.cpp
        core/geometry/geommultipoint.h
        core/geometry/geommultipolygon.cpp
        core/geometry/geommultipolygon.h
        core/geometry/geompoint.cpp
        core/geometry/geompoint.h
        core/geometry/geompolygon.cpp
        core/geometry/geompolygon.h
        core/geometry/rectangle.cpp
        core/geometry/rectangle.h
        )

set(GISL_CORE_SRCS
        ${GISL_CORE_GEO_SRCS}
        ${GISL_CORE_RASTER_SRCS}
        ${GISL_CORE_PROVIDER_SRCS}
        ${GISL_CORE_VACTOR_SRCS}
        ${GISL_CORE_LAYER_SRCS}
        core/coordinatetransform.cpp
        core/coordinatetransform.h
        core/layer/layertree.cpp
        core/layer/layertree.h
        core/spatialreference.cpp
        core/spatialreference.h
        )
set(GISL_GUI_RENDER_SRCS
        gui/render/multipolygonfs.h
        gui/render/multipolygonvs.h
        gui/render/imgviewwidget.cpp
        gui/render/imgviewwidget.h
        gui/render/chooserasterrgbwidget.cpp
        gui/render/chooserasterrgbwidget.h
        )
set(GISL_GUI_COMMAND_SRCS
        gui/command/command.cpp
        gui/command/command.h
        gui/command/commandhistory.cpp
        gui/command/commandhistory.h
        gui/command/opensldcommand.cpp
        gui/command/opensldcommand.h
        gui/command/openrastercommand.cpp
        gui/command/openrastercommand.h
        gui/command/openvectorcommand.cpp
        gui/command/openvectorcommand.h
        )
set(GISL_GUI_PAINTER_SRCS
        gui/painter/glpainterfactory.cpp
        gui/painter/glpainterfactory.h
        gui/painter/painterfactory.cpp
        gui/painter/painterfactory.h
        )
set(GISL_GUI_SYMBOLIZER_SRCS
        gui/symbolizer/abstractsymbolizer.cpp
        gui/symbolizer/abstractsymbolizer.h
        gui/symbolizer/polygonsymbolizer.cpp
        gui/symbolizer/polygonsymbolizer.h
        gui/symbolizer/symbolizerfactory.cpp
        gui/symbolizer/symbolizerfactory.h
        gui/symbolizer/textsymbolizer.cpp
        gui/symbolizer/textsymbolizer.h
        )
set(GISL_GUI_SRCS
        ${GISL_GUI_COMMAND_SRCS}
        ${GISL_GUI_PAINTER_SRCS}
        ${GISL_GUI_SYMBOLIZER_SRCS}
        ${GISL_GUI_RENDER_SRCS}
        gui/layertreewidget.cpp
        gui/layertreewidget.h
        gui/editmenu.cpp
        gui/editmenu.h
        gui/glcanvas.cpp
        gui/glcanvas.h
        gui/layerrender.cpp
        gui/layerrender.h
        gui/mainwindow.cpp
        gui/mainwindow.h
        gui/menubar.cpp
        gui/menubar.h
        gui/sld.cpp
        gui/sld.h
        )

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/codecvt)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui)

add_library(gisl_core_lib ${LIBRARY_TYPE}
        ${GISL_CORE_SRCS}
        ${GISL_GUI_SRCS}
        ${QM_FILES}
        )

target_link_libraries(gisl_core_lib
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        ${GDAL_LIBRARY}
        absl::strings
        Eigen3::Eigen
        Qwt::Qwt
        PRIVATE
        gisl_utils_lib
        gisl_codecvt_lib
        )

####################################################
# main core software
add_executable(gisl
        main.cpp
        )

target_link_libraries(gisl
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        PRIVATE
        gisl_core_lib
        )

####################################################
# other modules
if (WITH_ANALYSIS)
    add_subdirectory(analysis)
endif ()
