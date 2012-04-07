/*****************************************************************************/
/**
 *  @file   Gis.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__GIS_H_INCLUDE
#define KVS__GIS_H_INCLUDE

#include <vector>
#include <kvs/FileFormatBase>
#include <kvs/ClassName>
#include <kvs/Vector2>
#include <kvs/RGBColor>
#include "Mesh.h"
#include "Area.h"
#include "oceanValue.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  GIS (Geographical Information System) class.
 */
/*===========================================================================*/
class Gis : public kvs::FileFormatBase
{
    kvsClassName( kvs::Gis );

private:

    std::vector<kvs::gis::Mesh*> m_meshes; ///< mesh list
    kvs::gis::Area m_area; ///< area of all meshes
    kvs::gis::Area m_render_area; ///< render area of the mesh
    kvs::RGBColor m_ocean_color; ///< ocean color

public:

    Gis();

    Gis(
        const std::string& filename,
        const kvs::gis::Area& render_area = kvs::gis::Area( 0.0f, 999.0f, 0.0f, 999.0f ) );

    virtual ~Gis();

public:

    void setRenderArea( const kvs::gis::Area& render_area );

    void setOceanColor( const kvs::RGBColor& color );

public:

    const kvs::gis::Area& area() const;

    const kvs::gis::Area& renderArea() const;

    const std::vector<kvs::gis::Mesh*>& meshes() const;

    const kvs::gis::Mesh* mesh( const size_t index ) const;

    kvs::RGBColor oceanColor() const;

    const bool read( const std::string& filenames );

private:

    bool read_mesh( const std::string& filename );

    const bool write( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__GIS_H_INCLUDE
