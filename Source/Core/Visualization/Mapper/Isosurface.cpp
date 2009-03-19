/****************************************************************************/
/**
 *  @file Isosurface.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "Isosurface.h"
#include <kvs/MarchingCubes>
#include <kvs/MarchingTetrahedra>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructs a new Isosurface class.
 */
/*==========================================================================*/
Isosurface::Isosurface( void ):
    kvs::MapperBase(),
    kvs::PolygonObject(),
    m_isolevel( 0 ),
    m_duplication( true )
{
}

Isosurface::Isosurface(
    const kvs::VolumeObjectBase* volume,
    const double                 isolevel,
    const NormalType             normal_type ):
    kvs::MapperBase(),
    kvs::PolygonObject(),
    m_isolevel( isolevel ),
    m_duplication( true )
{
    SuperClass::m_normal_type = normal_type;

    // In the case of VertexNormal-type, the duplicated vertices are forcibly deleted.
    if ( normal_type == kvs::PolygonObject::VertexNormal )
    {
        m_duplication = false;
    }

    // Extract the surfaces.
    this->exec( volume );
}

/*==========================================================================*/
/**
 *  Constructs and creates a polygon object.
 *  @param volume [in] pointer to the volume object
 *  @param isolevel [in] level of the isosurfaces
 *  @param normal_type [in] type of the normal vector
 *  @param duplication [in] duplication flag
 *  @param transfer_function [in] transfer function
 */
/*==========================================================================*/
Isosurface::Isosurface(
    const kvs::VolumeObjectBase* volume,
    const double                 isolevel,
    const NormalType             normal_type,
    const bool                   duplication,
    const kvs::TransferFunction& transfer_function ):
    kvs::MapperBase( transfer_function ),
    kvs::PolygonObject(),
    m_isolevel( isolevel ),
    m_duplication( duplication )
{
    SuperClass::m_normal_type = normal_type;

    // In the case of VertexNormal-type, the duplicated vertices are forcibly deleted.
    if ( normal_type == kvs::PolygonObject::VertexNormal )
    {
        m_duplication = false;
    }

    // Extract the surfaces.
    this->exec( volume );
}

/*==========================================================================*/
/**
 *  Destructs.
 */
/*==========================================================================*/
Isosurface::~Isosurface( void )
{
}

void Isosurface::setIsolevel( const double isolevel )
{
    m_isolevel = isolevel;
}

kvs::ObjectBase* Isosurface::exec( const kvs::ObjectBase* object )
{
    if ( object->objectType() == kvs::ObjectBase::Volume )
    {
        this->mapping( reinterpret_cast<const kvs::VolumeObjectBase*>( object ) );
    }
    else
    {
        kvsMessageError( "Geometry object is inputed." );
    }

    return( this );
}

/*==========================================================================*/
/**
 *  Extracts the surfaces.
 *  @param volume [in] pointer to the volume object
 */
/*==========================================================================*/
void Isosurface::mapping( const kvs::VolumeObjectBase* volume )
{
    // Check whether the volume can be processed or not.
    if ( volume->veclen() != 1 )
    {
        kvsMessageError("The input volume is not a sclar field data.");
        return;
    }

    if ( volume->volumeType() == kvs::VolumeObjectBase::Structured )
    {
        const kvs::StructuredVolumeObject* structured_volume =
            reinterpret_cast<const kvs::StructuredVolumeObject*>( volume );

        kvs::PolygonObject* polygon = new kvs::MarchingCubes(
            structured_volume,
            m_isolevel,
            SuperClass::normalType(),
            m_duplication,
            BaseClass::transferFunction() );
        if ( !polygon )
        {
            kvsMessageError("Cannot create isosurfaces.");
            return;
        }

        // Shallow copy.
        SuperClass::m_coords       = polygon->coords();
        SuperClass::m_colors       = polygon->colors();
        SuperClass::m_normals      = polygon->normals();
        SuperClass::m_connections  = polygon->connections();
        SuperClass::m_opacities    = polygon->opacities();
        SuperClass::m_polygon_type = polygon->polygonType();
        SuperClass::m_color_type   = polygon->colorType();
        SuperClass::m_normal_type  = polygon->normalType();

        SuperClass::setMinMaxObjectCoords(
            polygon->minObjectCoord(),
            polygon->maxObjectCoord() );
        SuperClass::setMinMaxExternalCoords(
            polygon->minExternalCoord(),
            polygon->maxExternalCoord() );

        delete polygon;
    }
    else // volume->volumeType() == kvs::VolumeObjectBase::Unstructured
    {
        const kvs::UnstructuredVolumeObject* unstructured_volume =
            reinterpret_cast<const kvs::UnstructuredVolumeObject*>( volume );

        kvs::PolygonObject* polygon = new kvs::MarchingTetrahedra(
            unstructured_volume,
            m_isolevel,
            SuperClass::normalType(),
            m_duplication,
            BaseClass::transferFunction() );
        if ( !polygon )
        {
            kvsMessageError("Cannot create isosurfaces.");
            return;
        }

        // Shallow copy.
        SuperClass::m_coords       = polygon->coords();
        SuperClass::m_colors       = polygon->colors();
        SuperClass::m_normals      = polygon->normals();
        SuperClass::m_connections  = polygon->connections();
        SuperClass::m_opacities    = polygon->opacities();
        SuperClass::m_polygon_type = polygon->polygonType();
        SuperClass::m_color_type   = polygon->colorType();
        SuperClass::m_normal_type  = polygon->normalType();

        SuperClass::setMinMaxObjectCoords(
            polygon->minObjectCoord(),
            polygon->maxObjectCoord() );
        SuperClass::setMinMaxExternalCoords(
            polygon->minExternalCoord(),
            polygon->maxExternalCoord() );

        delete polygon;
    }
}

} // end of namespace kvs
