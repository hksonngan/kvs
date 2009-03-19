/****************************************************************************/
/**
 *  @file OpacityMap.cpp
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
#include "OpacityMap.h"

#include <kvs/Assert>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
OpacityMap::OpacityMap( void )
    : m_points()
    , m_table()
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param resolution [in] resolution
 */
/*==========================================================================*/
OpacityMap::OpacityMap( const size_t resolution )
    : m_points()
    , m_table()
{
    this->create( resolution );
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param table [in] opacity value table
 */
/*==========================================================================*/
OpacityMap::OpacityMap( const OpacityMap::Table& table )
    : m_points()
    , m_table( table )
{
    m_table = table;
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param opacity_map [in] opacity map
 */
/*==========================================================================*/
OpacityMap::OpacityMap( const OpacityMap& other )
    : m_points( other.m_points )
    , m_table( other.m_table )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
OpacityMap::~OpacityMap( void )
{
}

/*==========================================================================*/
/**
 *  Returns the resolution of the opacity map.
 *  @return resolusion
 */
/*==========================================================================*/
const size_t OpacityMap::resolution( void ) const
{
    return( m_table.size() );
}

/*==========================================================================*/
/**
 *  Returns the opacity map table.
 *  @return opacity map table
 */
/*==========================================================================*/
const OpacityMap::Table& OpacityMap::table( void ) const
{
    return( m_table );
}

/*==========================================================================*/
/**
 *  Creates the opacity map.
 *  @param resolution [in] resolution of the opacity map
 */
/*==========================================================================*/
void OpacityMap::create( const size_t resolution )
{
    m_points.clear();
    m_table.allocate( resolution );

    const float scale = 1.0f / static_cast<float>( resolution - 1 );
    for ( size_t i = 0; i < resolution; ++i )
    {
        m_table[i] = scale * static_cast<float>( i );
    }
}

/*==========================================================================*/
/**
 *  Access operator [].
 *  @param index [in] index of the opacity map.
 *  @retval opacity value
 */
/*==========================================================================*/
const kvs::Real32 OpacityMap::operator []( const size_t index ) const
{
    KVS_ASSERT( index < this->resolution() );

    return( m_table[index] );
}

/*==========================================================================*/
/**
 *  Substitution operator =.
 *  @param opacity_map [in] opacity map
 *  @retval opacity map
 */
/*==========================================================================*/
OpacityMap& OpacityMap::operator =( const OpacityMap& rhs )
{
    m_points = rhs.m_points;
    m_table  = rhs.m_table;

    return( *this );
}

} // end of namespace kvs
