/*****************************************************************************/
/**
 *  @file   Global.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "Global.h"
#include <kvs/File>
#include <kvs/Directory>
#include <kvs/Dicom>

// Instantiation.
Parameter Global::parameter;

/*===========================================================================*/
/**
 *  @brief  Constructs a new Global class.
 *  @param  count [in] argument count
 *  @param  values [in] argument values
 */
/*===========================================================================*/
Global::Global( int count, char** values ):
    kvs::glut::GlobalBase( count, values )
{
    Argument arg( count, values );
    if( !arg.parse() ) exit( EXIT_FAILURE );

    if( !this->read_arguments( arg ) )
    {
        kvsMessageError("Cannot read the DICOM file(s).");
        exit( EXIT_FAILURE );
    }
}

/*===========================================================================*/
/**
 *  @brief  Reads arguments.
 *  @param  arg [in] given arguments
 *  @return true, if the reading process is done succesfully
 */
/*===========================================================================*/
const bool Global::read_arguments( Argument& arg )
{
    const std::string name  = arg.value<std::string>(0);
    const bool check = !arg.hasOption("f");

    const kvs::File file( name );
    if( file.isFile() )
    {
        return( this->read_from_file( name ) );
    }

    const kvs::Directory dir( name );
    if( dir.isDirectory() )
    {
        return( this->read_from_directory( name, check ) );
    }

    kvsMessageError("Invalid argument.");
    return( false );
};

/*===========================================================================*/
/**
 *  @brief  Reads a DICOM file.
 *  @param  name [in] filename
 *  @return true, if the reading process is done succesfully
 */
/*===========================================================================*/
const bool Global::read_from_file( const std::string& name )
{
    // Check file existence.
    kvs::File file( name );
    if( !file.isExisted() )
    {
        kvsMessageError( "%s is not existed.", name.c_str() );
        return( false );
    }

    // Read a DICOM file.
    kvs::Dicom dicom( name );

    parameter.dicom_list.push_back( dicom );
    parameter.width = dicom.width();
    parameter.height = dicom.height();
    parameter.window_level = dicom.windowLevel();
    parameter.window_width = dicom.windowWidth();

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Reads DICOM files in the specified directory.
 *  @param  name [in] directory name
 *  @param  extension_check [in] check flag for the file extension
 *  @return true, if the reading process is done succesfully
 */
/*===========================================================================*/
const bool Global::read_from_directory( const std::string& name, const bool extension_check )
{
    // Check directory existence.
    kvs::Directory dir( name );
    if( !dir.isExisted() )
    {
        kvsMessageError( "%s is not existed.", name.c_str() );
        return( false );
    }

    // Read DICOM files in the specified directory.
    parameter.dicom_list.read( dir.directoryPath().c_str(), extension_check );
    parameter.dicom_list.sort();
    parameter.width = parameter.dicom_list[0]->width();
    parameter.height = parameter.dicom_list[0]->height();
    parameter.window_level = parameter.dicom_list[0]->windowLevel();
    parameter.window_width = parameter.dicom_list[0]->windowWidth();

    return( true );
}
