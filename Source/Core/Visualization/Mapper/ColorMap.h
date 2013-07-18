/****************************************************************************/
/**
 *  @file   ColorMap.h
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
/****************************************************************************/
#ifndef KVS__COLOR_MAP_H_INCLUDE
#define KVS__COLOR_MAP_H_INCLUDE

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
public:

    typedef kvs::ValueArray<kvs::UInt8> Table;
    typedef std::pair<float,kvs::RGBColor> Point;
    typedef std::list<Point> Points;

private:

    size_t m_resolution; ///< table resolution
    float m_min_value; ///< min. value
    float m_max_value; ///< max. value
    Points m_points; ///< control point list
    Table m_table; ///< value table

public:

    ColorMap();
    explicit ColorMap( const size_t resolution );
    explicit ColorMap( const Table& table );
    ColorMap( const ColorMap& other );
    ColorMap( const size_t resolution, const float min_value, const float max_value );
    ColorMap( const Table& table, const float min_value, const float max_value );
    virtual ~ColorMap();

    float minValue() const;
    float maxValue() const;
    size_t resolution() const;
    const Points& points() const;
    const Table& table() const;
    bool hasRange() const;

    void setRange( const float min_value, const float max_value );
    void setResolution( const size_t resolution );
    void addPoint( const float value, const kvs::RGBColor color );
    void removePoint( const float value );
    void create();

    const kvs::RGBColor operator []( const size_t index ) const;
    const kvs::RGBColor at( const float value ) const;

    ColorMap& operator =( const ColorMap& rhs );
};

} // end of namespace kvs

#endif // KVS__COLOR_MAP_H_INCLUDE
