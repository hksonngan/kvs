/****************************************************************************/
/**
 *  @file KVSMLObjectStructuredVolume.h
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
#ifndef KVS__KVSML_OBJECT_STRUCTURED_VOLUME_H_INCLUDE
#define KVS__KVSML_OBJECT_STRUCTURED_VOLUME_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/AnyValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include <string>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSML structured volume object format.
 */
/*===========================================================================*/
class KVSMLObjectStructuredVolume : public kvs::FileFormatBase
{
    kvsClassName( kvs::KVSMLObjectStructuredVolume );

public:

    enum WritingDataType
    {
        Ascii = 0,
        ExternalAscii,
        ExternalBinary
    };

protected:

    kvs::kvsml::KVSMLTag m_kvsml_tag;   ///< KVSML tag information
    kvs::kvsml::ObjectTag m_object_tag; ///< Object tag information

    WritingDataType    m_writing_type; ///< writing data type
    std::string        m_grid_type;    ///< grid type
    size_t             m_veclen;       ///< vector length
    kvs::Vector3ui     m_resolution;   ///< grid resolution
    kvs::AnyValueArray m_values;       ///< field value array

public:

    KVSMLObjectStructuredVolume( void );

    KVSMLObjectStructuredVolume( const std::string& filename );

    virtual ~KVSMLObjectStructuredVolume( void );

public:

    const kvs::kvsml::KVSMLTag& KVSMLTag( void ) const;

    const kvs::kvsml::ObjectTag& objectTag( void ) const;

public:

    const std::string& gridType( void ) const;

    const size_t veclen( void ) const;

    const kvs::Vector3ui& resolution( void ) const;

    const kvs::AnyValueArray& values( void ) const;

public:

    void setWritingDataType( const WritingDataType writing_type );

    void setGridType( const std::string& grid_type );

    void setVeclen( const size_t veclen );

    void setResolution( const kvs::Vector3ui& resolution );

    void setValues( const kvs::AnyValueArray& values );

public:

    const bool read( const std::string& filename );

    const bool write( const std::string& filename );

public:

    static const bool CheckFileExtension( const std::string& filename );

    static const bool CheckFileFormat( const std::string& filename );

    friend std::ostream& operator <<( std::ostream& os, const KVSMLObjectStructuredVolume& rhs );
};

} // end of namespace kvs

#endif // KVS__KVSML_OBJECT_STRUCTURED_VOLUME_H_INCLUDE
