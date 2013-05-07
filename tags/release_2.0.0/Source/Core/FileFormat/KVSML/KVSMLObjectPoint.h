/****************************************************************************/
/**
 *  @file KVSMLObjectPoint.h
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
#ifndef KVS__KVSML_OBJECT_POINT_H_INCLUDE
#define KVS__KVSML_OBJECT_POINT_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include <kvs/Indent>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSML point object format.
 */
/*===========================================================================*/
class KVSMLObjectPoint : public kvs::FileFormatBase
{
public:

    typedef kvs::FileFormatBase BaseClass;

    enum WritingDataType
    {
        Ascii = 0,     ///< ascii data type
        ExternalAscii, ///< external ascii data type
        ExternalBinary ///< external binary data type
    };

private:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< KVSML tag information
    kvs::kvsml::ObjectTag m_object_tag; ///< Object tag information
    WritingDataType m_writing_type; ///< writing data type
    kvs::ValueArray<kvs::Real32> m_coords; ///< coordinate array
    kvs::ValueArray<kvs::UInt8> m_colors; ///< color(r,g,b) array
    kvs::ValueArray<kvs::Real32> m_normals; ///< normal array
    kvs::ValueArray<kvs::Real32> m_sizes; ///< size array

public:

    static bool CheckExtension( const std::string& filename );
    static bool CheckFormat( const std::string& filename );

public:

    KVSMLObjectPoint();
    KVSMLObjectPoint( const std::string& filename );

    const kvs::kvsml::KVSMLTag& KVSMLTag() const;
    const kvs::kvsml::ObjectTag& objectTag() const;
    const kvs::ValueArray<kvs::Real32>& coords() const;
    const kvs::ValueArray<kvs::UInt8>& colors() const;
    const kvs::ValueArray<kvs::Real32>& normals() const;
    const kvs::ValueArray<kvs::Real32>& sizes() const;

    void setWritingDataType( const WritingDataType writing_type );
    void setCoords( const kvs::ValueArray<kvs::Real32>& coords );
    void setColors( const kvs::ValueArray<kvs::UInt8>& colors );
    void setNormals( const kvs::ValueArray<kvs::Real32>& normals );
    void setSizes( const kvs::ValueArray<kvs::Real32>& sizes );

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__KVSML_OBJECT_POINT_H_INCLUDE