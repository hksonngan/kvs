/*****************************************************************************/
/**
 *  @file   PreIntegrationTable.h
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
/*----------------------------------------------------------------------------
 *
 * Acknowledgements:
 * Original source code was developped by University of Utah and can be
 * downloaded at http://havs.sourceforge.net/
 */
/*****************************************************************************/
#ifndef KVS__PRE_INTEGRATION_TABLE_H_INCLUDE
#define KVS__PRE_INTEGRATION_TABLE_H_INCLUDE

#include <kvs/Vector4>
#include <kvs/TransferFunction>
#include <kvs/Texture3D>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  PreItegrationTable class.
 */
/*===========================================================================*/
class PreIntegrationTable
{
protected:

    kvs::Vector4f* m_transfer_function; ///< transfer function data
    kvs::Vector4f* m_table; ///< pre-integration table
    kvs::Texture3D m_table_texture; ///< pre-integration table texture
    int m_size_scalar; ///< table size for the scalar axis
    int m_size_depth; ///< table size for the depth axis

public:

    PreIntegrationTable();
    PreIntegrationTable( const int size_scalar, const int size_depth );
    ~PreIntegrationTable();

    const kvs::Texture3D& texture() const;
    int sizeDepth() const;

    void setTableSize( const int size_scalar, const int size_depth );
    void setTransferFunction( const kvs::TransferFunction& transfer_function, const float min_scalar, const float max_scalar );

    void create( const float max_size_of_cell );
    void download();
    void bind();
    void unbind();
    void release();
    bool isTexture();
    bool isDownloaded();

private:

    void compute_exact_level( const int level, const float dl );
    void compute_incremental_level(
        const int current_level,
        const int previous_level,
        const int first_level,
        const float l,
        const float dl );
};

} // end of namespace kvs

#endif // KVS__PRE_INTEGRATION_TABLE_H_INCLUDE
