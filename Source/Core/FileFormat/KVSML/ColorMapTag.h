/*****************************************************************************/
/**
 *  @file   ColorMapTag.h
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
#ifndef KVS__KVSML__COLOR_MAP_TAG_H_INCLUDE
#define KVS__KVSML__COLOR_MAP_TAG_H_INCLUDE

#include <kvs/XMLNode>
#include <kvs/XMLElement>
#include <kvs/RGBColor>
#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <ColorMap>
 */
/*===========================================================================*/
class ColorMapTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

public:

    ColorMapTag();

};


/*===========================================================================*/
/**
 *  @brief  <ColorMapValue> tag class.
 */
/*===========================================================================*/
class ColorMapValueTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

private:

    float m_scalar; ///< scalr value
    kvs::RGBColor m_color; ///< color value

public:

    ColorMapValueTag();

public:

    float scalar() const;
    const kvs::RGBColor& color() const;
    void setScalar( const float scalar );
    void setColor( const kvs::RGBColor& color );

public:

    bool read( const kvs::XMLNode::SuperClass* parent );
    bool read( const kvs::XMLElement::SuperClass* element );
    bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__COLOR_MAP_TAG_H_INCLUDE
