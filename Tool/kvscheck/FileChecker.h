/****************************************************************************/
/**
 *  @file FileChecker.h
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
#ifndef KVS_KVSCHECK_FILE_CHECKER_H_INCLUDE
#define KVS_KVSCHECK_FILE_CHECKER_H_INCLUDE

#include <string>
#include <iostream>


namespace kvscheck
{

/*==========================================================================*/
/**
 *  File checker class.
 */
/*==========================================================================*/
class FileChecker
{
public:

    enum FormatType
    {
        UnknownFormat = 0,
        KVSMLFormat,
        AVSFieldFormat,
        AVSUcdFormat,
        BitmapFormat,
        DICOMFormat
    };

private:

    std::string m_filename; ///< filename

public:

    FileChecker( const std::string& filename );

public:

    const std::string& filename( void ) const;

    const FormatType fileFormat( void ) const;

    friend std::ostream& operator << ( std::ostream& os, const FileChecker& checker );
};

} // end of namespace kvscheck

#endif // KVS_KVSCHECK_FILE_CHECKER_H_INCLUDE
