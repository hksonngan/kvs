/*****************************************************************************/
/**
 *  @file   ImageObjectTag.cpp
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
#include "ImageObjectTag.h"
#include <kvs/XMLNode>
#include <kvs/XMLElement>
#include <kvs/Tokenizer>
#include <kvs/String>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new image object tag class.
 */
/*===========================================================================*/
ImageObjectTag::ImageObjectTag():
    kvs::kvsml::TagBase( "ImageObject" ),
    m_has_width( false ),
    m_width( 0 ),
    m_has_height( false ),
    m_height( 0 )
{
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the image object tag has 'width' or not.
 *  @return true, if the image object tag has 'width'
 */
/*===========================================================================*/
bool ImageObjectTag::hasWidth() const
{
    return m_has_width;
}

/*===========================================================================*/
/**
 *  @brief  Returns a image width.
 *  @return image width
 */
/*===========================================================================*/
size_t ImageObjectTag::width() const
{
    return m_width;
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the image object tag has 'height' or not.
 *  @return true, if the image object tag has 'height'
 */
/*===========================================================================*/
bool ImageObjectTag::hasHeight() const
{
    return m_has_height;
}

/*===========================================================================*/
/**
 *  @brief  Returns a image height.
 *  @return image height
 */
/*===========================================================================*/
size_t ImageObjectTag::height() const
{
    return m_height;
}

/*===========================================================================*/
/**
 *  @brief  Sets a image width.
 *  @param  width [in] image width
 */
/*===========================================================================*/
void ImageObjectTag::setWidth( const size_t width )
{
    m_has_width = true;
    m_width = width;
}

/*===========================================================================*/
/**
 *  @brief  Sets a image height.
 *  @param  height [in] image height
 */
/*===========================================================================*/
void ImageObjectTag::setHeight( const size_t height )
{
    m_has_height = true;
    m_height = height;
}

/*===========================================================================*/
/**
 *  @brief  Reads the image object tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
bool ImageObjectTag::read( const kvs::XMLNode::SuperClass* parent )
{
    const std::string tag_name = BaseClass::name();

    BaseClass::m_node = kvs::XMLNode::FindChildNode( parent, tag_name );
    if ( !BaseClass::m_node )
    {
        kvsMessageError( "Cannot find <%s>.", tag_name.c_str() );
        return false;
    }

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( BaseClass::m_node );

    // width="xxx"
    const std::string width = kvs::XMLElement::AttributeValue( element, "width" );
    if ( width != "" )
    {
        m_has_width = true;
        m_width = static_cast<size_t>( atoi( width.c_str() ) );
    }

    // height="xxx"
    const std::string height = kvs::XMLElement::AttributeValue( element, "height" );
    if ( height != "" )
    {
        m_has_height = true;
        m_height = static_cast<size_t>( atoi( height.c_str() ) );
    }

    return true;
}

/*===========================================================================*/
/**
 *  @brief  Writes the structured volume object tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
bool ImageObjectTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element( BaseClass::name() );

    if ( m_has_width )
    {
        element.setAttribute( "width", m_width );
    }

    if ( m_has_height )
    {
        element.setAttribute( "height", m_height );
    }

    return BaseClass::write_with_element( parent, element );
}

} // end of namespace kvsml

} // end of namespace kvs
