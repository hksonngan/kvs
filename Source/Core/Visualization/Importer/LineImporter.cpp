/****************************************************************************/
/**
 *  @file LineImporter.cpp
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
#include "LineImporter.h"
#include <kvs/KVSMLObjectLine>
#include <kvs/Math>
#include <kvs/Vector3>
#include <string>


namespace
{

/*==========================================================================*/
/**
 *  Get the line type from the given string.
 *  @param line_type [in] line type string
 *  @return line type
 */
/*==========================================================================*/
const kvs::LineObject::LineType StringToLineType( const std::string& line_type )
{
    if (      line_type == "strip"    ) { return( kvs::LineObject::Strip ); }
    else if ( line_type == "uniline"  ) { return( kvs::LineObject::Uniline ); }
    else if ( line_type == "polyline" ) { return( kvs::LineObject::Polyline ); }
    else if ( line_type == "segment"  ) { return( kvs::LineObject::Segment ); }
    else
    {
        kvsMessageError( "Unknown line type '%s'.", line_type.c_str() );
        return( kvs::LineObject::UnknownLineType );
    }
}

/*==========================================================================*/
/**
 *  Get the line color type from the given string.
 *  @param color_type [in] line color type string
 *  @return line color type
 */
/*==========================================================================*/
const kvs::LineObject::ColorType StringToColorType( const std::string& color_type )
{
    if (      color_type == "vertex" ) { return( kvs::LineObject::VertexColor ); }
    else if ( color_type == "line"   ) { return( kvs::LineObject::LineColor ); }
    else
    {
        kvsMessageError( "Unknown line color type '%s'.", color_type.c_str() );
        return( kvs::LineObject::UnknownColorType );
    }
}

} // end of namespace


namespace kvs
{

/*==========================================================================*/
/**
 *  Default constructor.
 */
/*==========================================================================*/
LineImporter::LineImporter( void )
{
}

LineImporter::LineImporter( const std::string& filename )
{
    if ( kvs::KVSMLObjectLine::CheckFileExtension( filename ) )
    {
        kvs::KVSMLObjectLine* file_format = new kvs::KVSMLObjectLine( filename );
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
LineImporter::LineImporter( const kvs::FileFormatBase* file_format )
{
    if ( !this->exec( file_format ) ) BaseClass::m_is_success = true;
}

LineImporter::~LineImporter( void )
{
}

kvs::ObjectBase* LineImporter::exec( const kvs::FileFormatBase* file_format )
{
    const std::string class_name = file_format->className();
    if ( class_name == "KVSMLObjectLine" )
    {
        this->import( reinterpret_cast<const kvs::KVSMLObjectLine*>( file_format ) );
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
 *  @param kvsml [in] pointer to the KVSML document
 */
/*==========================================================================*/
void LineImporter::import( const kvs::KVSMLObjectLine* kvsml )
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

    m_line_type   = ::StringToLineType( kvsml->lineType() );
    m_color_type  = ::StringToColorType( kvsml->colorType() );
    m_coords      = kvsml->coords();
    m_colors      = kvsml->colors();
    m_connections = kvsml->connections();
    m_sizes       = kvsml->sizes();

    this->set_min_max_coord();
}

/*==========================================================================*/
/**
 *  Calculate min/max coordinate values.
 */
/*==========================================================================*/
void LineImporter::set_min_max_coord( void )
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
