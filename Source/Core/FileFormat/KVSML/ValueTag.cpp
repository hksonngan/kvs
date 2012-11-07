/*****************************************************************************/
/**
 *  @file   ValueTag.cpp
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
#include "ValueTag.h"
#include <kvs/Message>
#include <kvs/String>
#include <kvs/XMLNode>
#include <kvs/XMLElement>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new value tag class.
 */
/*===========================================================================*/
ValueTag::ValueTag():
    kvs::kvsml::TagBase( "Value" ),
    m_has_label( false ),
    m_has_veclen( false ),
    m_has_min_value( false ),
    m_has_max_value( false ),
    m_label( "" ),
    m_veclen( 0 ),
    m_min_value( 0.0 ),
    m_max_value( 0.0 )
{
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the 'label' is specified or not.
 *  @return true, if the 'label' is specified
 */
/*===========================================================================*/
bool ValueTag::hasLabel() const
{
    return m_has_label;
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the 'veclen' is specified or not.
 *  @return true, if the 'veclen' is specified
 */
/*===========================================================================*/
bool ValueTag::hasVeclen() const
{
    return m_has_veclen;
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the 'min_value' is specified or not.
 *  @return true, if the 'min_value' is specified
 */
/*===========================================================================*/
bool ValueTag::hasMinValue() const
{
    return m_has_min_value;
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the 'max_value' is specified or not.
 *  @return true, if the 'max_value' is specified
 */
/*===========================================================================*/
bool ValueTag::hasMaxValue() const
{
    return m_has_max_value;
}

/*===========================================================================*/
/**
 *  @brief  Returns a data label that is specified by 'veclen'.
 *  @return data label
 */
/*===========================================================================*/
const std::string& ValueTag::label() const
{
    return m_label;
}

/*===========================================================================*/
/**
 *  @brief  Returns a vector length that is specified by 'veclen'.
 *  @return vector length
 */
/*===========================================================================*/
size_t ValueTag::veclen() const
{
    return m_veclen;
}

/*===========================================================================*/
/**
 *  @brief  Returns a minimum value that is specified by 'min_value'.
 *  @return minimum value
 */
/*===========================================================================*/
double ValueTag::minValue() const
{
    return m_min_value;
}

/*===========================================================================*/
/**
 *  @brief  Returns a maximum value that is specified by 'max_value'.
 *  @return maximum value
 */
/*===========================================================================*/
double ValueTag::maxValue() const
{
    return m_max_value;
}

/*===========================================================================*/
/**
 *  @brief  Sets a data lebel.
 *  @param  label [in] data label
 */
/*===========================================================================*/
void ValueTag::setLabel( const std::string& label )
{
    m_has_label = true;
    m_label = label;
}

/*===========================================================================*/
/**
 *  @brief  Sets a vector length.
 *  @param  veclen [in] vector length
 */
/*===========================================================================*/
void ValueTag::setVeclen( const size_t veclen )
{
    m_has_veclen = true;
    m_veclen = veclen;
}

/*===========================================================================*/
/**
 *  @brief  Sets a minimum value.
 *  @param  min_value [in] minimum value
 */
/*===========================================================================*/
void ValueTag::setMinValue( const double min_value )
{
    m_has_min_value = true;
    m_min_value = min_value;
}

/*===========================================================================*/
/**
 *  @brief  Sets a maximum value.
 *  @param  max_value [in] maximum value
 */
/*===========================================================================*/
void ValueTag::setMaxValue( const double max_value )
{
    m_has_max_value = true;
    m_max_value = max_value;
}

/*===========================================================================*/
/**
 *  @brief  Reads the value tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
bool ValueTag::read( const kvs::XMLNode::SuperClass* parent )
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

    // label="xxx"
    const std::string label = kvs::XMLElement::AttributeValue( element, "label" );
    if ( label != "" )
    {
        m_has_label = true;
        m_label = label;
    }

    // veclen="xxx"
    const std::string veclen = kvs::XMLElement::AttributeValue( element, "veclen" );
    if ( veclen != "" )
    {
        m_has_veclen = true;
        m_veclen = static_cast<size_t>( atoi( veclen.c_str() ) );
    }

    // min_value="xxx"
    const std::string min_value = kvs::XMLElement::AttributeValue( element, "min_value" );
    if ( min_value != "" )
    {
        m_has_min_value = true;
        m_min_value = atof( min_value.c_str() );
    }

    // max_value="xxx"
    const std::string max_value = kvs::XMLElement::AttributeValue( element, "max_value" );
    if ( max_value != "" )
    {
        m_has_max_value = true;
        m_max_value = atof( max_value.c_str() );
    }

    return true;
}

/*===========================================================================*/
/**
 *  @brief  Writes the value tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
bool ValueTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element( BaseClass::name() );

    if ( m_has_label )
    {
        element.setAttribute( "label", m_label );
    }

    if ( m_has_veclen )
    {
        element.setAttribute( "veclen", m_veclen );
    }
    else
    {
        kvsMessageError( "'veclen' is not specified in <%s>.", BaseClass::name().c_str() );
        return false;
    }

    if ( m_has_min_value )
    {
        element.setAttribute( "min_value", m_min_value );
    }

    if ( m_has_max_value )
    {
        element.setAttribute( "max_value", m_max_value );
    }

    return BaseClass::write_with_element( parent, element );
}

} // end of namespace kvsml

} // end of namespace kvs
