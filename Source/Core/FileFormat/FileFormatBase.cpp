/****************************************************************************/
/**
 *  @file FileFormatBase.cpp
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
#include "FileFormatBase.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  @brief  Constructs a new empty FileFormatBase.
 */
/*==========================================================================*/
FileFormatBase::FileFormatBase():
    m_filename(""),
    m_is_success( false )
{
}

/*==========================================================================*/
/**
 *  @brief  Destroys the FileFormatBase.
 */
/*==========================================================================*/
FileFormatBase::~FileFormatBase()
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the filename.
 *  @return filename
 */
/*===========================================================================*/
const std::string& FileFormatBase::filename() const
{
    return m_filename;
}

/*==========================================================================*/
/**
 *  @brief  Returns true if the reading is success; otherwise returns false.
 *  @return true if the reading process is done successfully
 */
/*==========================================================================*/
bool FileFormatBase::isSuccess() const
{
    return m_is_success;
}

/*==========================================================================*/
/**
 *  @brief  Returns true if the reading is failure; otherwise returns false.
 *  @return Whether the reading is failure or not.
 */
/*==========================================================================*/
bool FileFormatBase::isFailure() const
{
    return !m_is_success;
}

/*===========================================================================*/
/**
 *  @brief  Sets a filename.
 *  @param  filename [in] filename
 */
/*===========================================================================*/
void FileFormatBase::setFilename( const std::string& filename )
{
    m_filename = filename;
}

/*===========================================================================*/
/**
 *  @brief  Sets a status of the file reading process.
 *  @param  success [in] status of rendering process
 */
/*===========================================================================*/
void FileFormatBase::setSuccess( const bool success )
{
    m_is_success = success;
}

} // end of namespace kvs
