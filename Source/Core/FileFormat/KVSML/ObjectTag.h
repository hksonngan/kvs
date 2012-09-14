/*****************************************************************************/
/**
 *  @file   ObjectTag.h
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
#ifndef KVS__KVSML__OBJECT_TAG_H_INCLUDE
#define KVS__KVSML__OBJECT_TAG_H_INCLUDE

#include <string>
#include <kvs/Vector3>
#include <kvs/XMLDocument>
#include <kvs/XMLNode>
#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Object>.
 */
/*===========================================================================*/
class ObjectTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

protected:

    bool m_has_type; ///< flag to check whether 'type' is specified or not
    std::string m_type; ///< object type
    bool m_has_external_coord; ///< flag to check whether 'external_coord' is specified or not
    kvs::Vector3f m_min_external_coord; ///< min. external coordinate
    kvs::Vector3f m_max_external_coord; ///< max. external coordinate
    bool m_has_object_coord; ///< flag to check whether 'object_coord' is specified or not
    kvs::Vector3f m_min_object_coord; ///< min. object coordinate
    kvs::Vector3f m_max_object_coord; ///< max. object coordinate

public:

    ObjectTag();
    virtual ~ObjectTag();

public:

    bool hasType() const;
    const std::string& type() const;
    bool hasExternalCoord() const;
    const kvs::Vector3f& minExternalCoord() const;
    const kvs::Vector3f& maxExternalCoord() const;
    bool hasObjectCoord() const;
    const kvs::Vector3f& minObjectCoord() const;
    const kvs::Vector3f& maxObjectCoord() const;

public:

    void setType( const std::string& type );
    void setMinMaxExternalCoords( const kvs::Vector3f& min_coord, const kvs::Vector3f& max_coord );
    void setMinMaxObjectCoords( const kvs::Vector3f& min_coord, const kvs::Vector3f& max_coord );

public:

    bool read( const kvs::XMLNode::SuperClass* parent );
    bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__OBJECT_TAG_H_INCLUDE
