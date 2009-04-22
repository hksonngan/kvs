/*****************************************************************************/
/**
 *  @file   TransferFunctionTag.h
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
#ifndef KVS__KVSML__TRANSFER_FUNCTION_TAG_H_INCLUDE
#define KVS__KVSML__TRANSFER_FUNCTION_TAG_H_INCLUDE

#include <kvs/XMLNode>
#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <TransferFunction>
 */
/*===========================================================================*/
class TransferFunctionTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

protected:

    bool m_has_file; ///< flag to check whether 'file' is specified or not
    std::string m_file; ///< name of external file for 'argb' data
    bool m_has_resolution; ///< flag to check whether 'resolution' is specified or not
    size_t m_resolution; ///< resolution

public:

    TransferFunctionTag( void );

    virtual ~TransferFunctionTag( void );

public:

    const bool hasFile( void ) const;

    const std::string& file( void ) const;

    const bool hasResolution( void ) const;

    const size_t resolution( void ) const;

public:

    void setFile( const std::string& file );

    void setResolution( const size_t resolution );

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__TRANSFER_FUNCTION_TAG_H_INCLUDE
