/*****************************************************************************/
/**
 *  @file   GrADS.h
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
#ifndef KVS__GRADS_H_INCLUDE
#define KVS__GRADS_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/ClassName>
#include "DataDescriptorFile.h"
#include "GriddedBinaryDataFile.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  GrADS class.
 */
/*===========================================================================*/
class GrADS : public kvs::FileFormatBase
{
    kvsClassName( kvs::GrADS );

public:

    typedef kvs::FileFormatBase BaseClass;
    typedef kvs::grads::DataDescriptorFile DataDescriptorFile;
    typedef kvs::grads::GriddedBinaryDataFile GriddedBinaryDataFile;
    typedef std::vector<GriddedBinaryDataFile> GriddedBinaryDataFileList;

protected:

    DataDescriptorFile m_data_descriptor; ///< data descriptor file
    GriddedBinaryDataFileList m_data_list; ///< gridded binary data file list

public:

    GrADS();
    GrADS( const std::string& filename );
    virtual ~GrADS();

public:

    const DataDescriptorFile& dataDescriptor() const;
    const GriddedBinaryDataFileList& dataList() const;
    const GriddedBinaryDataFile& data( const size_t index ) const;
    bool read( const std::string& filename );

private:

    bool write( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__GRADS_H_INCLUDE
