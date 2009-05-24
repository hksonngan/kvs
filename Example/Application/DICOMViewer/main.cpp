/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  DICOM viewer
 *  @author Naohisa Sakamoto
 *
 *  Compile:\
 *  \code
 *  % kvsmake -G
 *  % kvsmake
 *  \endcode
 *
 *  Usage:\n
 *  \code
 *  % ./DICOMViewer [-h|--help] <DICOM file or directory>
 *  \endcode
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
#include "Screen.h"
#include <kvs/Message>


/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    // Create the global parameters.
    Global* global = new Global( argc, argv );
    if( !global )
    {
        kvsMessageError("Cannot allocate memory for the global parameters.");
        return( false );
    }

    // Create and show the rendering screen.
    Screen* screen = new Screen();
    if( !screen )
    {
        kvsMessageError("Cannot allocate memory for the screen.");
        return( false );
    }
    screen->setGeometry( 0, 0, Global::parameter.width, Global::parameter.height );
    screen->setTitle( "DICOM viewer" );
    screen->show( true );

    // Delete the global and the rendering screen.
    delete global;
    delete screen;

    return( true );
}
