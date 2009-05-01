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
#ifndef KVS__KVSML__KVSML_TRANSFER_FUNCTION_H_INCLUDE
#define KVS__KVSML__KVSML_TRANSFER_FUNCTION_H_INCLUDE

#include "../FileFormatBase.h"
#include <kvs/ValueArray>
#include <kvs/Type>
#include "KVSMLTag.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSMLTransferFunction file format class.
 */
/*===========================================================================*/
class KVSMLTransferFunction : public kvs::FileFormatBase
{
    kvsClassName( KVSMLTransferFunction );

public:

    enum WritingDataType
    {
        Ascii = 0,
        ExternalAscii,
        ExternalBinary
    };

protected:

    kvs::kvsml::KVSMLTag         m_kvsml_tag;    ///< KVSML tag information
    WritingDataType              m_writing_type; ///< writing data type
    size_t                       m_resolution;   ///< resolution
    kvs::ValueArray<kvs::Real32> m_opacities;    ///< opacity array
    kvs::ValueArray<kvs::UInt8>  m_colors;       ///< color (r,g,b) array

public:

    KVSMLTransferFunction( void );

    KVSMLTransferFunction( const std::string& filename );

    virtual ~KVSMLTransferFunction( void );

public:

    const kvs::kvsml::KVSMLTag& KVSMLTag( void ) const;

public:

    const size_t resolution( void ) const;

    const kvs::ValueArray<kvs::Real32>& opacities( void ) const;

    const kvs::ValueArray<kvs::UInt8>& colors( void ) const;

public:

    void setResolution( const size_t resolution );

    void setWritingDataType( const WritingDataType writing_type );

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

#endif // KVS__KVSML__KVSML_TRANSFER_FUNCTION_H_INCLUDE
