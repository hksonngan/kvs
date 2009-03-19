/*****************************************************************************/
/**
 *  @file   KVSMLTag.h
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
#ifndef KVS__KVSML__KVSML_TAG_H_INCLUDE
#define KVS__KVSML__KVSML_TAG_H_INCLUDE

#include <string>
#include <kvs/XMLDocument>
#include <kvs/XMLNode>


namespace kvs
{

namespace kvsml
{

class KVSMLTag
{
protected:

    kvs::XMLNode::SuperClass* m_node; ///< pointer to the node of the XML tree
    bool m_has_version; ///< flag to check whether 'version' is specified or not
    std::string m_version; ///< KVSML version

public:

    KVSMLTag( void );

    virtual ~KVSMLTag( void );

public:

    kvs::XMLNode::SuperClass* node( void );

    const kvs::XMLNode::SuperClass* node( void ) const;

public:

    const bool hasVersion( void ) const;

    const std::string& version( void ) const;

public:

    void setVersion( const std::string& version );

public:

    const bool read( const kvs::XMLDocument* document );

    const bool write( kvs::XMLDocument* document );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__KVSML_TAG_H_INCLUDE
