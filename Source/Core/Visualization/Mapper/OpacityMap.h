/****************************************************************************/
/**
 *  @file OpacityMap.h
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
#ifndef KVS_CORE_OPACITY_MAP_H_INCLUDE
#define KVS_CORE_OPACITY_MAP_H_INCLUDE

#include <kvs/ClassName>

#include <list>
#include <utility>

#include <kvs/ValueArray>


namespace kvs
{

/*==========================================================================*/
/**
 *  OpacityMap.
 */
/*==========================================================================*/
class OpacityMap
{
    kvsClassName( OpacityMap );

public:

    typedef kvs::ValueArray<float>   Table;
    typedef std::pair<size_t, float> Point;
    typedef std::list<Point>         Points;

private:

    Points m_points; ///< Control point list.
    Table  m_table;  ///< Value table.

public:

    OpacityMap( void );

    explicit OpacityMap( const size_t resolution );

    explicit OpacityMap( const Table& table );

    OpacityMap( const OpacityMap& other );

    virtual ~OpacityMap( void );

public:

    const size_t resolution( void ) const;

    const Table& table( void ) const;

public:

    void create( const size_t resolution );

public:

    const kvs::Real32 operator []( const size_t index ) const;

public:

    OpacityMap& operator =( const OpacityMap& rhs );
};

} // end of namespace kvs

#endif // KVS_CORE_OPACITY_MAP_H_INCLUDE
