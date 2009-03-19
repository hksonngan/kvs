/****************************************************************************/
/**
 *  @file PointImporter.cpp
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
#include "PointImporter.h"
#include <kvs/KVSMLObjectPoint>
#include <kvs/Math>
#include <kvs/Vector3>
#include <string>


namespace kvs
{

/*==========================================================================*/
/**
 *  Default constructor.
 */
/*==========================================================================*/
PointImporter::PointImporter( void )
{
}

PointImporter::PointImporter( const std::string& filename )
{
    if ( kvs::KVSMLObjectPoint::CheckFileExtension( filename ) )
    {
        kvs::KVSMLObjectPoint* file_format = new kvs::KVSMLObjectPoint( filename );
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
        kvsMessageError("Cannot import '%'.",filename.c_str());
        return;
    }

    BaseClass::m_is_success = true;
}

/*==========================================================================*/
/**
 *  Constructor for the KVSML document.
 *  @param file_format [in] pointer to the file format
 */
/*==========================================================================*/
PointImporter::PointImporter( const kvs::FileFormatBase* file_format )
{
    if ( this->exec( file_format ) ) BaseClass::m_is_success = true;
}

PointImporter::~PointImporter( void )
{
}

kvs::ObjectBase* PointImporter::exec( const kvs::FileFormatBase* file_format )
{
    const std::string class_name = file_format->className();
    if ( class_name == "KVSMLObjectPoint" )
    {
        this->import( reinterpret_cast<const kvs::KVSMLObjectPoint*>( file_format ) );
    }
    else
    {
        kvsMessageError( "Unsupported class '%s'.", class_name.c_str() );
        return( NULL );
    }

    return( this );
}

/*==========================================================================*/
/**
 *  Import the KVSML document.
 *  @param kvsml [in] pointer to KVSML document
 */
/*==========================================================================*/
void PointImporter::import( const kvs::KVSMLObjectPoint* kvsml )
{
    if ( kvsml->hasExternalCoord() )
    {
        const kvs::Vector3f min_coord( kvsml->minExternalCoord() );
        const kvs::Vector3f max_coord( kvsml->maxExternalCoord() );
        SuperClass::setMinMaxExternalCoords( min_coord, max_coord );
    }

    if ( kvsml->hasObjectCoord() )
    {
        const kvs::Vector3f min_coord( kvsml->minObjectCoord() );
        const kvs::Vector3f max_coord( kvsml->maxObjectCoord() );
        SuperClass::setMinMaxObjectCoords( min_coord, max_coord );
    }

    m_coords  = kvsml->coords();
    m_colors  = kvsml->colors();
    m_normals = kvsml->normals();
    m_sizes   = kvsml->sizes();

    this->set_min_max_coord();
}

/*==========================================================================*/
/**
 *  Calculate min/max coordinate values.
 */
/*==========================================================================*/
void PointImporter::set_min_max_coord( void )
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
