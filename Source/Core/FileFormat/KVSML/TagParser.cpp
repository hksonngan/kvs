/****************************************************************************/
/**
 *  @file TagParser.cpp
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
#include "TagParser.h"


namespace kvs
{

namespace TagParser
{

/*==========================================================================*/
/**
 *  Find the node.
 *  @param document [in] pointer to the XML document
 *  @param name [in] node name
 *  @return pointer to the found node
 */
/*==========================================================================*/
TiXmlNode* FindNode( const kvs::XMLDocument* document, const std::string& name )
{
    TiXmlNode* node = document->FirstChild();
    while( node )
    {
        if( node->Value() == name ) return( node );

        node = node->NextSibling();
    }

    return( NULL );
}

/*==========================================================================*/
/**
 *  Find the child node.
 *  @param node [in] pointer to the node
 *  @param name [in] node name
 *  @return pointer to the child node
 */
/*==========================================================================*/
TiXmlNode* FindChildNode( const TiXmlNode* node, const std::string& name )
{
    TiXmlNode* child_node = node->FirstChild();
    while( child_node )
    {
        if( child_node->Value() == name ) return( child_node );

        child_node = child_node->NextSibling();
    }

    return( NULL );
}

/*==========================================================================*/
/**
 *  Convert the node to the element.
 *  @param node [in] pointer to the node
 *  @return pointer to the element
 */
/*==========================================================================*/
TiXmlElement* NodeToElement( const TiXmlNode* node )
{
    return( node->ToElement() );
}

/*==========================================================================*/
/**
 *  Convert the node to the text.
 *  @param node [in] pointer to the node
 *  @return pointer to the text
 */
/*==========================================================================*/
TiXmlText* NodeToText( const TiXmlNode* node )
{
    TiXmlElement* e = NodeToElement( node );
    TiXmlNode*    n = e->FirstChild();
    TiXmlText*    t = n->ToText();

    return( t );
}

/*==========================================================================*/
/**
 *  Get the attribute value.
 *  @param element [in] pointer to the element
 *  @param name [in] attribute name
 *  @return attribute value
 */
/*==========================================================================*/
std::string GetAttributeValue( const TiXmlElement* element, const std::string& name )
{
    const std::string* value = element->Attribute( name );
    if( !value ) return( "" );

    return( *value );
}

} // end of namespace TagParser

} // end of namespace kvs
