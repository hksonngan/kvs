/****************************************************************************/
/**
 *  @file PolygonImporter.cpp
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
#include "PolygonImporter.h"
#include <kvs/KVSMLObjectPolygon>
#include <kvs/Math>
#include <kvs/Vector3>



namespace
{

/*==========================================================================*/
/**
 *  Get the polygon type from the given string.
 *  @param polygon_type [in] polygon type string
 *  @return polygon type
 */
/*==========================================================================*/
const kvs::PolygonObject::PolygonType StringToPolygonType( const std::string& polygon_type )
{
    if (      polygon_type == "triangle"   ) { return( kvs::PolygonObject::Triangle ); }
    else if ( polygon_type == "quadrangle" ) { return( kvs::PolygonObject::Quadrangle ); }
    else
    {
        kvsMessageError( "Unknown polygon type '%s'.", polygon_type.c_str() );
        return( kvs::PolygonObject::UnknownPolygonType );
    }
}

/*==========================================================================*/
/**
 *  Get the polygon color type from the given string.
 *  @param color_type [in] polygon color type string
 *  @return polygon color type
 */
/*==========================================================================*/
const kvs::PolygonObject::ColorType StringToColorType( const std::string& color_type )
{
    if (      color_type == "vertex"  ) { return( kvs::PolygonObject::VertexColor ); }
    else if ( color_type == "polygon" ) { return( kvs::PolygonObject::PolygonColor ); }
    else
    {
        kvsMessageError( "Unknown polygon color type '%s'.", color_type.c_str() );
        return( kvs::PolygonObject::UnknownColorType );
    }
}

/*==========================================================================*/
/**
 *  Get the polygon normal type from the given string.
 *  @param normal_type [in] polygon normal type string
 *  @return polygon normal type
 */
/*==========================================================================*/
const kvs::PolygonObject::NormalType StringToNormalType( const std::string& normal_type )
{
    if (      normal_type == "vertex"  ) { return( kvs::PolygonObject::VertexNormal ); }
    else if ( normal_type == "polygon" ) { return( kvs::PolygonObject::PolygonNormal ); }
    else
    {
        kvsMessageError( "Unknown polygon normal type '%s'.", normal_type.c_str() );
        return( kvs::PolygonObject::UnknownNormalType );
    }
}

} // end of namespace


namespace kvs
{

/*==========================================================================*/
/**
 *  Default constructer
 */
/*==========================================================================*/
PolygonImporter::PolygonImporter( void )
{
}

PolygonImporter::PolygonImporter( const std::string& filename )
{
    if ( kvs::KVSMLObjectPolygon::CheckFileExtension( filename ) )
    {
        kvs::KVSMLObjectPolygon* file_format = new kvs::KVSMLObjectPolygon( filename );
        if( !file_format )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            return;
        }

        if( file_format->isFailure() )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            delete file_format;
            return;
        }

        this->import( file_format );
        delete file_format;
    }
    else if ( kvs::Stl::CheckFileExtension( filename ) )
    {
        kvs::Stl* file_format = new kvs::Stl( filename );
        if( !file_format )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            return;
        }

        if( file_format->isFailure() )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            delete file_format;
            return;
        }

        this->import( file_format );
        delete file_format;
    }
    else
    {
        kvsMessageError("Cannot import '%s'.",filename.c_str());
        return;
    }
}

/*==========================================================================*/
/**
 *  Constructor for the KVSML document.
 *  @param file_format [in] pointer to the file format
 */
/*==========================================================================*/
PolygonImporter::PolygonImporter( const kvs::FileFormatBase* file_format )
{
    this->exec( file_format );
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
PolygonImporter::~PolygonImporter( void )
{
}

kvs::ObjectBase* PolygonImporter::exec( const kvs::FileFormatBase* file_format )
{
    const std::string class_name = file_format->className();
    if ( class_name == "KVSMLObjectPolygon" )
    {
        this->import( reinterpret_cast<const kvs::KVSMLObjectPolygon*>( file_format ) );
    }
    else if ( class_name == "Stl" )
    {
        this->import( reinterpret_cast<const kvs::Stl*>( file_format ) );
    }
    else
    {
        kvsMessageError( "Unsupported class '%s'.", class_name.c_str() );
    }

    return( this );
}

/*==========================================================================*/
/**
 *  Import the KVSML document.
 *  @param document [in] pointer to the KVSML document
 */
/*==========================================================================*/
void PolygonImporter::import( const kvs::KVSMLObjectPolygon* kvsml )
{
    if ( kvsml->objectTag().hasExternalCoord() )
    {
        const kvs::Vector3f min_coord( kvsml->objectTag().minExternalCoord() );
        const kvs::Vector3f max_coord( kvsml->objectTag().maxExternalCoord() );
        SuperClass::setMinMaxExternalCoords( min_coord, max_coord );
    }

    if ( kvsml->objectTag().hasObjectCoord() )
    {
        const kvs::Vector3f min_coord( kvsml->objectTag().minObjectCoord() );
        const kvs::Vector3f max_coord( kvsml->objectTag().maxObjectCoord() );
        SuperClass::setMinMaxObjectCoords( min_coord, max_coord );
    }

    SuperClass::setPolygonType( ::StringToPolygonType( kvsml->polygonType() ) );
    SuperClass::setColorType( ::StringToColorType( kvsml->colorType() ) );
    SuperClass::setNormalType( ::StringToNormalType( kvsml->normalType() ) );
    SuperClass::setCoords( kvsml->coords() );
    SuperClass::setColors( kvsml->colors() );
    SuperClass::setNormals( kvsml->normals() );
    SuperClass::setConnections( kvsml->connections() );
    SuperClass::setOpacities( kvsml->opacities() );
//    SuperClass::updateMinMaxCoords();
    this->set_min_max_coord();

    BaseClass::m_is_success = true;
}

/*==========================================================================*/
/**
 *  Import the STL format file.
 *  @param stl [in] pointer to the STL format file
 */
/*==========================================================================*/
void PolygonImporter::import( const kvs::Stl* stl )
{
    m_polygon_type = kvs::PolygonObject::Triangle;
    m_color_type = kvs::PolygonObject::PolygonColor;
    m_normal_type = kvs::PolygonObject::PolygonNormal;

    m_coords = stl->coords();
    m_normals = stl->normals();

    m_colors.allocate( 3 );
    m_colors[0] = 255;
    m_colors[1] = 255;
    m_colors[2] = 255;

    m_opacities.allocate( 1 );
    m_opacities[0] = 255;

    this->set_min_max_coord();

    BaseClass::m_is_success = true;
}

/*==========================================================================*/
/**
 *  Calculate min/max coordinate value.
 */
/*==========================================================================*/
void PolygonImporter::set_min_max_coord( void )
{
    kvs::Vector3f min_coord( m_coords[0], m_coords[1], m_coords[2] );
    kvs::Vector3f max_coord( min_coord );
    const size_t  dimension = 3;
    const size_t  nvertices = m_coords.size() / dimension;
    size_t        index3    = 3;
    for ( size_t i = 1; i < nvertices; i++, index3 += 3 )
    {
        min_coord.x() = kvs::Math::Min( min_coord.x(), m_coords[index3] );
        min_coord.y() = kvs::Math::Min( min_coord.y(), m_coords[index3 + 1] );
        min_coord.z() = kvs::Math::Min( min_coord.z(), m_coords[index3 + 2] );

        max_coord.x() = kvs::Math::Max( max_coord.x(), m_coords[index3] );
        max_coord.y() = kvs::Math::Max( max_coord.y(), m_coords[index3 + 1] );
        max_coord.z() = kvs::Math::Max( max_coord.z(), m_coords[index3 + 2] );
    }

    this->setMinMaxObjectCoords( min_coord, max_coord );
    this->setMinMaxExternalCoords( min_coord, max_coord );
}

} // end of namespace kvs
