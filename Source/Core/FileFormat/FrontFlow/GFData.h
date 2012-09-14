/*****************************************************************************/
/**
 *  @file   GFData.h
 *  @author Naohisa Sakamoto
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
#ifndef KVS__GF_DATA_H_INCLUDE
#define KVS__GF_DATA_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/ClassName>
#include "FlowData.h"
#include "MeshData.h"
#include "BoundaryData.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  GF file format class.
 */
/*===========================================================================*/
class GFData : public kvs::FileFormatBase
{
    kvsClassName_without_virtual( kvs::GFData );

public:

    typedef kvs::FileFormatBase BaseClass;

protected:

    kvs::gf::MeshData m_mesh_data; ///< GF mesh data
    kvs::gf::FlowData m_flow_data; ///< GF flow data
    kvs::gf::BoundaryData m_boundary_data; ///< GF doundary condition data

public:

    GFData();
    GFData( const std::string& filename );
    GFData( const std::string& mesh_file, const std::string& flow_file, const std::string& boundary_file = "" );

public:

    const kvs::gf::FlowData& flowData() const;
    const kvs::gf::MeshData& meshData() const;
    const kvs::gf::BoundaryData& boundaryData() const;

public:

    bool read( const std::string& filename );
    bool read( const std::string& mesh_file, const std::string& flow_file, const std::string& boundary_file = "" );

private:

    bool write( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__GF_DATA_H_INCLUDE
