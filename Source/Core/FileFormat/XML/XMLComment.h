/****************************************************************************/
/**
 *  @file XMLComment.h
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
#ifndef KVS_CORE_XML_COMMENT_H_INCLUDE
#define KVS_CORE_XML_COMMENT_H_INCLUDE

#include "TinyXML.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  XML comment class.
 */
/*==========================================================================*/
class XMLComment : public TiXmlComment
{
public:

    typedef TiXmlComment SuperClass;

public:

    XMLComment( void );

    XMLComment( const char* comment );

    virtual ~XMLComment( void );
};

} // end of namespace kvs

#endif // KVS_CORE_XML_COMMENT_H_INCLUDE
