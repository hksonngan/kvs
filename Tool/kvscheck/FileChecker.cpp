/****************************************************************************/
/**
 *  @file FileChecker.cpp
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
#include "FileChecker.h"
#include <kvs/AVSField>
#include <kvs/AVSUcd>
#include <kvs/Stl>
#include <kvs/Bmp>
#include <kvs/Ppm>
#include <kvs/Pgm>
#include <kvs/Pbm>
#include <kvs/Tiff>
#include <kvs/Dicom>
#include <kvs/KVSMLObjectImage>
#include <kvs/KVSMLObjectPoint>
#include <kvs/KVSMLObjectLine>
#include <kvs/KVSMLObjectPolygon>
#include <kvs/KVSMLObjectStructuredVolume>
#include <kvs/KVSMLObjectUnstructuredVolume>
#include <kvs/KVSMLTransferFunction>
#include <kvs/File>
#include <kvs/Timer>
#include <iostream>


#define PRINT_INFO( class_name, os, checker ) \
    PrintInformation<class_name>( #class_name, os, checker )

namespace
{

/*===========================================================================*/
/**
 *  @brief  Outputs information of the file cheacker.
 *  @param  os [out] output stream
 *  @param  checker [in] file cheacker
 */
/*===========================================================================*/
template <typename FileFormatClass>
inline void PrintInformation( const char* class_name, std::ostream& os, const kvscheck::FileChecker& checker )
{
    kvs::Timer timer( kvs::Timer::Start );
    FileFormatClass file( checker.filename() );
    timer.stop();
    os << "File format class: " << class_name << std::endl;
    os << "Reading time: " << timer.sec() << " [sec]" << std::endl;
    os << "Information: " << std::endl;
    const size_t indent = 2;
    file.print( os, indent );
}

/*===========================================================================*/
/**
 *  @brief  Outputs information of the file cheacker for KVSML.
 *  @param  os [out] output stream
 *  @param  checker [in] file cheacker
 */
/*===========================================================================*/
inline void PrintKVSMLInformation( std::ostream& os, const kvscheck::FileChecker& checker )
{
    if ( kvs::KVSMLObjectImage::CheckFileFormat( checker.filename() ) )
    {
        PRINT_INFO( kvs::KVSMLObjectImage, os, checker ); return;
    }

    if ( kvs::KVSMLObjectPoint::CheckFileFormat( checker.filename() ) )
    {
        PRINT_INFO( kvs::KVSMLObjectPoint, os, checker ); return;
    }

    if ( kvs::KVSMLObjectLine::CheckFileFormat( checker.filename() ) )
    {
        PRINT_INFO( kvs::KVSMLObjectLine, os, checker ); return;
    }

    if ( kvs::KVSMLObjectPolygon::CheckFileFormat( checker.filename() ) )
    {
        PRINT_INFO( kvs::KVSMLObjectPolygon, os, checker ); return;
    }

    if ( kvs::KVSMLObjectStructuredVolume::CheckFileFormat( checker.filename() ) )
    {
        PRINT_INFO( kvs::KVSMLObjectStructuredVolume, os, checker ); return;
    }

    if ( kvs::KVSMLObjectUnstructuredVolume::CheckFileFormat( checker.filename() ) )
    {
        PRINT_INFO( kvs::KVSMLObjectUnstructuredVolume, os, checker ); return;
    }
}

} // end of namespace


namespace kvscheck
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new FileCheacker class.
 *  @param  filename [in] filename
 */
/*===========================================================================*/
FileChecker::FileChecker( const std::string& filename )
{
    m_filename = filename;
}

/*===========================================================================*/
/**
 *  @brief  Returns a filename.
 *  @return filename
 */
/*===========================================================================*/
const std::string& FileChecker::filename( void ) const
{
    return( m_filename );
}

/*===========================================================================*/
/**
 *  @brief  Returns a file format type.
 *  @return file format type
 */
/*===========================================================================*/
const FileChecker::FormatType FileChecker::fileFormat( void ) const
{
    if ( kvs::KVSMLObjectPoint::CheckFileExtension( m_filename ) )
    {
        /* NOTE: The KVSML object file have a same extension. Therefore,
         * kvs::KVSMLObjectPoint is used in order to check the file extension
         * for the KVSML format here.
         */
        return( FileChecker::KVSMLFormat );
    }

    if ( kvs::AVSField::CheckFileExtension( m_filename ) )
    {
        return( FileChecker::AVSFieldFormat );
    }

    if ( kvs::AVSUcd::CheckFileExtension( m_filename ) )
    {
        return( FileChecker::AVSUcdFormat );
    }

    if ( kvs::Stl::CheckFileExtension( m_filename ) )
    {
        return( FileChecker::STLFormat );
    }

    if ( kvs::Bmp::CheckFileExtension( m_filename ) )
    {
        return( FileChecker::BitmapFormat );
    }

    if ( kvs::Ppm::CheckFileExtension( m_filename ) )
    {
        return( FileChecker::PPMFormat );
    }

    if ( kvs::Pgm::CheckFileExtension( m_filename ) )
    {
        return( FileChecker::PGMFormat );
    }

    if ( kvs::Pbm::CheckFileExtension( m_filename ) )
    {
        return( FileChecker::PBMFormat );
    }

    if ( kvs::Tiff::CheckFileExtension( m_filename ) )
    {
        return( FileChecker::TIFFFormat );
    }

    if ( kvs::Dicom::CheckFileExtension( m_filename ) )
    {
        return( FileChecker::DICOMFormat );
    }

    return( FileChecker::UnknownFormat );
}

/*==========================================================================*/
/**
 *  @brief  Output file information.
 *  @param  os [in] output stream
 *  @param  checker [in] file checker
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
        PRINT_INFO( kvs::AVSField, os, checker );
        break;

    case FileChecker::AVSUcdFormat:
        PRINT_INFO( kvs::AVSUcd, os, checker );
        break;

    case FileChecker::STLFormat:
        PRINT_INFO( kvs::Stl, os, checker );
        break;

    case FileChecker::BitmapFormat:
        PRINT_INFO( kvs::Bmp, os, checker );
        break;

    case FileChecker::PPMFormat:
        PRINT_INFO( kvs::Ppm, os, checker );
        break;

    case FileChecker::PGMFormat:
        PRINT_INFO( kvs::Pgm, os, checker );
        break;

    case FileChecker::PBMFormat:
        PRINT_INFO( kvs::Pbm, os, checker );
        break;

    case FileChecker::TIFFFormat:
        PRINT_INFO( kvs::Tiff, os, checker );
        break;

    case FileChecker::DICOMFormat:
        PRINT_INFO( kvs::Dicom, os, checker );
        break;

    default:
        kvsMessageError("Unknown file format.");
        break;
    }

    return( os );
}

} // end of namespace kvscheck
