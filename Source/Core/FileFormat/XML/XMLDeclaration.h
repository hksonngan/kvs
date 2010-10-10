/****************************************************************************/
/**
 *  @file XMLDeclaration.h
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
#ifndef KVS__XML_DECLARATION_H_INCLUDE
#define KVS__XML_DECLARATION_H_INCLUDE

#include <string>
#include "TinyXML.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  XML declaration class.
 */
/*==========================================================================*/
class XMLDeclaration : public TiXmlDeclaration
{
public:

    typedef TiXmlDeclaration SuperClass;

public:

    XMLDeclaration( void );

    XMLDeclaration(
        const std::string& version,
        const std::string& encoding = "",
        const std::string& standalone = "" );

    virtual ~XMLDeclaration( void );
};

} // end of namespace kvs

#endif // KVS__XML_DECLARATION_H_INCLUDE
