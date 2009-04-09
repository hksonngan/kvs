/*****************************************************************************/
/**
 *  @file   PolygonTag.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__KVSML__POLYGON_TAG_H_INCLUDE
#define KVS__KVSML__POLYGON_TAG_H_INCLUDE

#include <kvs/XMLNode>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Polygon>
 */
/*===========================================================================*/
class PolygonTag
{
protected:

    kvs::XMLNode::SuperClass* m_node; ///< pointer to the node of the XML tree
    bool m_has_npolygons; ///< flag to check whether 'npolygons' is specified or not
    size_t m_npolygons; ///< number of polygons

public:

    PolygonTag( void );

    virtual ~PolygonTag( void );

public:

    kvs::XMLNode::SuperClass* node( void );

    const kvs::XMLNode::SuperClass* node( void ) const;

public:

    const bool hasNPolygons( void ) const;

    const size_t npolygons( void ) const;

public:

    void setNPolygons( const size_t npolygons );

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__POLYGONS_TAG_H_INCLUDE
