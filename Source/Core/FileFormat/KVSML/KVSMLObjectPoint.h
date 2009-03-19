/****************************************************************************/
/**
 *  @file KVSMLObjectPoint.h
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
#ifndef KVS_CORE_KVSML_KVSML_OBJECT_POINT_H_INCLUDE
#define KVS_CORE_KVSML_KVSML_OBJECT_POINT_H_INCLUDE

#include "../FileFormatBase.h"
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector3>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSML point object format.
 */
/*===========================================================================*/
class KVSMLObjectPoint : public kvs::FileFormatBase
{
    kvsClassName( KVSMLObjectPoint );

public:

    enum WritingDataType
    {
        Ascii = 0,
        ExternalAscii,
        ExternalBinary
    };

protected:

    bool m_has_external_coord; ///< flag to check whether 'external_coord' is specified or not
    kvs::Vector3f m_min_external_coord; ///< min. external coordinate
    kvs::Vector3f m_max_external_coord; ///< max. external coordinate
    bool m_has_object_coord; ///< flag to check whether 'object_coord' is specified or not
    kvs::Vector3f m_min_object_coord; ///< min. object coordinate
    kvs::Vector3f m_max_object_coord; ///< max. object coordinate

    WritingDataType              m_writing_type; ///< writing data type
    kvs::ValueArray<kvs::Real32> m_coords;       ///< coordinate array
    kvs::ValueArray<kvs::UInt8>  m_colors;       ///< color(r,g,b) array
    kvs::ValueArray<kvs::Real32> m_normals;      ///< normal array
    kvs::ValueArray<kvs::Real32> m_sizes;        ///< size array

public:

    KVSMLObjectPoint( void );

    KVSMLObjectPoint( const std::string& filename );

    virtual ~KVSMLObjectPoint( void );

public:

    const bool hasExternalCoord( void ) const;

    const kvs::Vector3f& minExternalCoord( void ) const;

    const kvs::Vector3f& maxExternalCoord( void ) const;

    const bool hasObjectCoord( void ) const;

    const kvs::Vector3f& minObjectCoord( void ) const;

    const kvs::Vector3f& maxObjectCoord( void ) const;

public:

    const kvs::ValueArray<kvs::Real32>& coords( void ) const;

    const kvs::ValueArray<kvs::UInt8>& colors( void ) const;

    const kvs::ValueArray<kvs::Real32>& normals( void ) const;

    const kvs::ValueArray<kvs::Real32>& sizes( void ) const;

public:

    void setWritingDataType( const WritingDataType writing_type );

    void setCoords( const kvs::ValueArray<kvs::Real32>& coords );

    void setColors( const kvs::ValueArray<kvs::UInt8>& colors );

    void setNormals( const kvs::ValueArray<kvs::Real32>& normals );

    void setSizes( const kvs::ValueArray<kvs::Real32>& sizes );

public:

    const bool read( const std::string& filename );

    const bool write( const std::string& filename );

public:

    static const bool CheckFileExtension( const std::string& filename );

    static const bool CheckFileFormat( const std::string& filename );

    friend std::ostream& operator <<( std::ostream& os, const KVSMLObjectPoint& rhs );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_KVSML_OBJECT_POINT_H_INCLUDE
