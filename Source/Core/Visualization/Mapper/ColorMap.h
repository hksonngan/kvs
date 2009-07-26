/****************************************************************************/
/**
 *  @file ColorMap.h
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
#ifndef KVS_CORE_COLOR_MAP_H_INCLUDE
#define KVS_CORE_COLOR_MAP_H_INCLUDE

#include <kvs/ClassName>

#include <list>
#include <utility>

#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/RGBColor>


namespace kvs
{

/*==========================================================================*/
/**
 *  Color map class.
 */
/*==========================================================================*/
class ColorMap
{
    kvsClassName( ColorMap );

public:

    typedef kvs::ValueArray<kvs::UInt8>   Table;
    typedef std::pair<size_t, kvs::UInt8> Point;
    typedef std::list<Point>              Points;

private:

    Points m_points; ///< Control point list.
    Table  m_table;  ///< Value table.

public:

    ColorMap( void );

    explicit ColorMap( const size_t resolution );

    explicit ColorMap( const Table& table );

    ColorMap( const ColorMap& other );

    virtual ~ColorMap( void );

public:

    const size_t resolution( void ) const;

    const Table& table( void ) const;

public:

    void create( const size_t resolution );

public:

    const kvs::RGBColor operator []( const size_t index ) const;

    const kvs::RGBColor at( const float index ) const;

public:

    ColorMap& operator =( const ColorMap& rhs );
};

} // end of namespace kvs

#endif // KVS_CORE_COLOR_MAP_H_INCLUDE
