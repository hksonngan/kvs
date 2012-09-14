/*****************************************************************************/
/**
 *  @file   GriddedBinaryDataFile.cpp
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
#include "GriddedBinaryDataFile.h"
#include <fstream>
#include <kvs/Endian>


namespace kvs
{

namespace grads
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new GriddedBinaryDataFile class.
 */
/*===========================================================================*/
GriddedBinaryDataFile::GriddedBinaryDataFile():
    m_sequential( false ),
    m_big_endian( false ),
    m_filename("")
{
}

/*===========================================================================*/
/**
 *  @brief  Sets sequential dat flag.
 *  @param  sequential [in] sequential data flag
 */
/*===========================================================================*/
void GriddedBinaryDataFile::setSequential( const bool sequential )
{
    m_sequential = sequential;
}

/*===========================================================================*/
/**
 *  @brief  Sets big endian flag.
 *  @param  big_endian [in] big endian flag
 */
/*===========================================================================*/
void GriddedBinaryDataFile::setBigEndian( const bool big_endian )
{
    m_big_endian = big_endian;
}

/*===========================================================================*/
/**
 *  @brief  Sets data filename.
 *  @param  filename [in] data filename
 */
/*===========================================================================*/
void GriddedBinaryDataFile::setFilename( const std::string& filename )
{
    m_filename = filename;
}

/*===========================================================================*/
/**
 *  @brief  Returns data filename.
 *  @return data filename
 */
/*===========================================================================*/
const std::string& GriddedBinaryDataFile::filename() const
{
    return m_filename;
}

/*===========================================================================*/
/**
 *  @brief  Returns data values.
 *  @return data values
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& GriddedBinaryDataFile::values() const
{
    return m_values;
}

/*===========================================================================*/
/**
 *  @brief  Loads data values from the specified data file.
 *  @return true, if the loading process is done successfully
 */
/*===========================================================================*/
bool GriddedBinaryDataFile::load() const
{
    if ( m_filename.length() == 0 )
    {
        kvsMessageError("Filename of binary data has not been specified.");
        return false;
    }

    std::ifstream ifs( m_filename.c_str(), std::ios::binary | std::ios::in );
    if( !ifs.is_open() )
    {
        kvsMessageError( "Cannot open %s.", m_filename.c_str() );
        return false;
    }

    ifs.seekg( 0, std::ios::end );
    const size_t end = ifs.tellg();

    ifs.seekg( 0, std::ios::beg );
    const size_t begin = ifs.tellg();

    const size_t file_size = end - begin; // [byte]
    const size_t nelements = file_size / sizeof( kvs::Real32 );
    m_values.allocate( nelements );

    if ( m_sequential )
    {
        for ( size_t i = 0; i < nelements; i++ )
        {
            kvs::Int16 padding[4];
            kvs::Real32 value;
            ifs.read( (char*)( padding + 0 ), sizeof( kvs::Int16 ) );
            ifs.read( (char*)( padding + 1 ), sizeof( kvs::Int16 ) );
            ifs.read( (char*)( &value ), sizeof( kvs::Real32 ) );
            ifs.read( (char*)( padding + 2 ), sizeof( kvs::Int16 ) );
            ifs.read( (char*)( padding + 3 ), sizeof( kvs::Int16 ) );
            m_values[i] = value;
        }
    }
    else
    {
        ifs.read( (char*)( m_values.data() ), file_size );
    }

    if ( m_big_endian != kvs::Endian::IsBig() )
    {
        kvs::Endian::Swap( m_values.data(), m_values.size() );
    }

    ifs.close();

    return true;
}

/*===========================================================================*/
/**
 *  @brief  Free loaded data values.
 */
/*===========================================================================*/
void GriddedBinaryDataFile::free() const
{
    m_values.release();
}

} // end of namespace grads

} // end of namespace kvs
