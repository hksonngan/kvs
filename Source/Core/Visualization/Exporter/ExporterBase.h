/*****************************************************************************/
/**
 *  @file   ExporterBase.h
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
#ifndef KVS__EXPORTER_BASE_H_INCLUDE
#define KVS__EXPORTER_BASE_H_INCLUDE

#include <kvs/Module>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Exporter base class.
 */
/*===========================================================================*/
template <typename FileFormatType>
class ExporterBase : public FileFormatType
{
    kvsModuleName( kvs::ExporterBase );

protected:

    bool m_is_success; ///< check flag for exporting

public:

    ExporterBase();
    virtual ~ExporterBase();

    virtual FileFormatType* exec( const kvs::ObjectBase* object ) = 0;

    bool isSuccess() const;
    bool isFailure() const;
};

/*===========================================================================*/
/**
 *  @brief  Constructs a new ExporterBase class.
 */
/*===========================================================================*/
template <typename FileFormatType>
ExporterBase<FileFormatType>::ExporterBase()
{
}

/*===========================================================================*/
/**
 *  @brief  Destroys the ExporterBase class.
 */
/*===========================================================================*/
template <typename FileFormatType>
ExporterBase<FileFormatType>::~ExporterBase()
{
}

/*===========================================================================*/
/**
 *  @brief  Test whether the export process is done successfully.
 *  @return true if the export process is done successfully
 */
/*===========================================================================*/
template <typename FileFormatType>
bool ExporterBase<FileFormatType>::isSuccess() const
{
    return m_is_success;
}

/*===========================================================================*/
/**
 *  @brief  Test whether the export process is failed.
 *  @return true if the export process is failed
 */
/*===========================================================================*/
template <typename FileFormatType>
bool ExporterBase<FileFormatType>::isFailure() const
{
    return !m_is_success;
}

} // end of namespace kvs

#endif // KVS__EXPORTER_BASE_H_INCLUDE
