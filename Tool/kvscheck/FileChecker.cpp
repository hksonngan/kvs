/****************************************************************************/
/**
 *  @file FileChecker.cpp
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
#include "FileChecker.h"
#include <kvs/KVSMLObjectPoint>
#include <kvs/KVSMLObjectLine>
#include <kvs/KVSMLObjectPolygon>
#include <kvs/KVSMLObjectStructuredVolume>
#include <kvs/KVSMLObjectUnstructuredVolume>
#include <kvs/AVSField>
#include <kvs/AVSUcd>
#include <kvs/Bmp>
#include <kvs/Dicom>
#include <kvs/File>
#include <kvs/Timer>
#include <iostream>


namespace
{

template <typename FileFormatClass>
inline void PrintInformation( std::ostream& os, const kvscheck::FileChecker& checker )
{
    kvs::Timer timer( kvs::Timer::Start );
    FileFormatClass file( checker.filename() );
    timer.stop();
    os << "File format class: " << "kvs::" << file.className() << std::endl;
    os << "Reading time:      " << timer.sec() << " [sec]" << std::endl;
    os << "Information:       " << std::endl << file;
}

inline void PrintKVSMLInformation( std::ostream& os, const kvscheck::FileChecker& checker )
{
    if ( kvs::KVSMLObjectPoint::CheckFileFormat( checker.filename() ) )
    {
        PrintInformation<kvs::KVSMLObjectPoint>( os, checker ); return;
    }

    if ( kvs::KVSMLObjectLine::CheckFileFormat( checker.filename() ) )
    {
        PrintInformation<kvs::KVSMLObjectLine>( os, checker ); return;
    }

    if ( kvs::KVSMLObjectPolygon::CheckFileFormat( checker.filename() ) )
    {
        PrintInformation<kvs::KVSMLObjectPolygon>( os, checker ); return;
    }

    if ( kvs::KVSMLObjectStructuredVolume::CheckFileFormat( checker.filename() ) )
    {
        PrintInformation<kvs::KVSMLObjectStructuredVolume>( os, checker ); return;
    }

    if ( kvs::KVSMLObjectUnstructuredVolume::CheckFileFormat( checker.filename() ) )
    {
        PrintInformation<kvs::KVSMLObjectUnstructuredVolume>( os, checker ); return;
    }
}

}


namespace kvscheck
{

/*==========================================================================*/
/**
 *  Constructor.
 *  @param filename [in] filename
 */
/*==========================================================================*/
FileChecker::FileChecker( const std::string& filename )
{
    m_filename = filename;
}

/*==========================================================================*/
/**
 *  Get the filename.
 *  @retval filename
 */
/*==========================================================================*/
const std::string& FileChecker::filename( void ) const
{
    return( m_filename );
}

/*==========================================================================*/
/**
 *  Get the file format type.
 *  @return file format type
 */
/*==========================================================================*/
const FileChecker::FormatType FileChecker::fileFormat( void ) const
{
    kvs::File file( m_filename );

    if(      file.extension( false ) == "fld" )   return( FileChecker::AVSFieldFormat );
    else if( file.extension( false ) == "inp" )   return( FileChecker::AVSUcdFormat );
    else if( file.extension( false ) == "ucd" )   return( FileChecker::AVSUcdFormat );
    else if( file.extension( false ) == "kvsml" ) return( FileChecker::KVSMLFormat );
    else if( file.extension( false ) == "bmp" )   return( FileChecker::BitmapFormat );
    else if( file.extension( false ) == "dcm" )   return( FileChecker::DICOMFormat );
    else
    {
        return( FileChecker::UnknownFormat );
    }
}

/*==========================================================================*/
/**
 *  Output file information.
 *  @param os [in] output stream
 *  @param checker [in] file checker
 */
/*==========================================================================*/
std::ostream& operator << ( std::ostream& os, const FileChecker& checker )
{
    if ( !kvs::File( checker.filename() ).isExisted() )
    {
        kvsMessageError("%s is not existed.", checker.filename().c_str() );
        return( os );
    }

    // KVSML format.
    if ( checker.fileFormat() == FileChecker::KVSMLFormat )
    {
        ::PrintKVSMLInformation( os, checker );
        return( os );
    }

    // Other supported format.
    switch ( checker.fileFormat() )
    {
    case FileChecker::AVSFieldFormat:
    {
        ::PrintInformation<kvs::AVSField>( os, checker );
        break;
    }
    case FileChecker::AVSUcdFormat:
    {
        ::PrintInformation<kvs::AVSUcd>( os, checker );
        break;
    }
    case FileChecker::BitmapFormat:
    {
        ::PrintInformation<kvs::Bmp>( os, checker );
        break;
    }
    case FileChecker::DICOMFormat:
    {
        ::PrintInformation<kvs::Dicom>( os, checker );
        break;
    }
    default:
        kvsMessageError("Unknown file format.");
        break;
    }

    return( os );
}

} // end of namespace kvscheck
