/*****************************************************************************/
/**
 *  @file   CellTag.cpp
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
#include "CellTag.h"
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
 *  @brief  Constructs a new CellTag class.
 */
/*===========================================================================*/
CellTag::CellTag():
    kvs::kvsml::TagBase( "Cell" ),
    m_has_ncells( false ),
    m_ncells( 0 )
{
}

/*===========================================================================*/
/**
 *  @brief  Checks whether the ncells is specified or not
 *  @return true, if the ncells is specified
 */
/*===========================================================================*/
bool CellTag::hasNCells() const
{
    return m_has_ncells;
}

/*===========================================================================*/
/**
 *  @brief  Returns a number of cells.
 *  @return number of cells
 */
/*===========================================================================*/
size_t CellTag::ncells() const
{
    return m_ncells;
}

/*===========================================================================*/
/**
 *  @brief  Sets a number of cells.
 *  @param  ncells [in] number of cells
 */
/*===========================================================================*/
void CellTag::setNCells( const size_t ncells )
{
    m_has_ncells = true;
    m_ncells = ncells;
}

/*===========================================================================*/
/**
 *  @brief  Reads the cell tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
bool CellTag::read( const kvs::XMLNode::SuperClass* parent )
{
    BaseClass::read( parent );

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( BaseClass::m_node );

    // ncells="xxx"
    const std::string ncells = kvs::XMLElement::AttributeValue( element, "ncells" );
    if ( ncells != "" )
    {
        m_has_ncells = true;
        m_ncells = static_cast<size_t>( atoi( ncells.c_str() ) );
    }

    return true;
}

/*===========================================================================*/
/**
 *  @brief  Writes the cell tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
bool CellTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element( BaseClass::name() );

    if ( m_has_ncells )
    {
        element.setAttribute( "ncells", m_ncells );
    }

    return BaseClass::write_with_element( parent, element );
}

} // end of namespace kvsml

} // end of namespace kvs
