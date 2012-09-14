/*****************************************************************************/
/**
 *  @file   KVSMLTag.h
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
#ifndef KVS__KVSML__KVSML_TAG_H_INCLUDE
#define KVS__KVSML__KVSML_TAG_H_INCLUDE

#include <string>
#include <kvs/XMLDocument>
#include <kvs/XMLNode>
#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <KVSML>.
 */
/*===========================================================================*/
class KVSMLTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

protected:

    bool m_has_version; ///< flag to check whether 'version' is specified or not
    std::string m_version; ///< KVSML version

public:

    KVSMLTag();
    virtual ~KVSMLTag();

public:

    bool hasVersion() const;
    const std::string& version() const;

public:

    void setVersion( const std::string& version );

public:

    bool read( const kvs::XMLDocument* document );
    bool write( kvs::XMLDocument* document );

private:

    bool read( const kvs::XMLNode::SuperClass* parent );
    bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__KVSML_TAG_H_INCLUDE
