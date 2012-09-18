/****************************************************************************/
/**
 *  @file KVSMLObjectPolygon.h
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
#ifndef KVS__KVSML_OBJECT_POLYGON_H_INCLUDE
#define KVS__KVSML_OBJECT_POLYGON_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSML polygon object format.
 */
/*===========================================================================*/
class KVSMLObjectPolygon : public kvs::FileFormatBase
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
    std::string m_polygon_type; ///< polygon type
    std::string m_color_type; ///< polygon color type
    std::string m_normal_type; ///< polygon normal type
    kvs::ValueArray<kvs::Real32> m_coords; ///< coordinate array
    kvs::ValueArray<kvs::UInt32> m_connections; ///< connection array
    kvs::ValueArray<kvs::UInt8> m_colors; ///< color (r,g,b) array
    kvs::ValueArray<kvs::UInt8> m_opacities; ///< opacity array
    kvs::ValueArray<kvs::Real32> m_normals; ///< normal array

public:

    static bool CheckFileExtension( const std::string& filename );
    static bool CheckFileFormat( const std::string& filename );

public:

    KVSMLObjectPolygon();
    KVSMLObjectPolygon( const std::string& filename );
    virtual ~KVSMLObjectPolygon();

    const kvs::kvsml::KVSMLTag& KVSMLTag() const;
    const kvs::kvsml::ObjectTag& objectTag() const;
    const std::string& polygonType() const;
    const std::string& colorType() const;
    const std::string& normalType() const;
    const kvs::ValueArray<kvs::Real32>& coords() const;
    const kvs::ValueArray<kvs::UInt32>& connections() const;
    const kvs::ValueArray<kvs::UInt8>& colors() const;
    const kvs::ValueArray<kvs::UInt8>& opacities() const;
    const kvs::ValueArray<kvs::Real32>& normals() const;

    void setWritingDataType( const WritingDataType writing_type );
    void setPolygonType( const std::string& polygon_type );
    void setColorType( const std::string& color_type );
    void setNormalType( const std::string& normal_type );
    void setCoords( const kvs::ValueArray<kvs::Real32>& coords );
    void setConnections( const kvs::ValueArray<kvs::UInt32>& connections );
    void setColors( const kvs::ValueArray<kvs::UInt8>& colors );
    void setOpacities( const kvs::ValueArray<kvs::UInt8>& opacities );
    void setNormals( const kvs::ValueArray<kvs::Real32>& normals );

    void print( std::ostream& os, const size_t indent = 0 ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );
};

} // end of namesapce kvs

#endif // KVS__KVSML_OBJECT_POLYGON_H_INCLUDE
