/****************************************************************************/
/**
 *  @file KVSMLTransferFunction.h
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
#ifndef KVS_CORE_KVSML_KVSML_TRANSFER_FUNCTION_H_INCLUDE
#define KVS_CORE_KVSML_KVSML_TRANSFER_FUNCTION_H_INCLUDE

#include "../FileFormatBase.h"
#include <kvs/ValueArray>
#include <kvs/Type>


namespace kvs
{

class KVSMLTransferFunction : public kvs::FileFormatBase
{
    kvsClassName( KVSMLTransferFunction );

protected:

    kvs::ValueArray<kvs::Real32> m_opacities;  ///< opacity array
    kvs::ValueArray<kvs::UInt8>  m_colors;     ///< color(r,g,b) array

public:

    KVSMLTransferFunction( void );

    KVSMLTransferFunction( const std::string& filename );

    virtual ~KVSMLTransferFunction( void );

public:

    const kvs::ValueArray<kvs::Real32>& opacities( void ) const;

    const kvs::ValueArray<kvs::UInt8>& colors( void ) const;

public:

    void setOpacities( const kvs::ValueArray<kvs::Real32>& opacities );

    void setColors( const kvs::ValueArray<kvs::UInt8>& colors );

public:

    const bool read( const std::string& filename );

    const bool write( const std::string& filename );

public:

    static const bool CheckFileExtension( const std::string& filename );

    static const bool CheckFileFormat( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_KVSML_TRANSFER_FUNCTION_H_INCLUDE
