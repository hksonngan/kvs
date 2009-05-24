/*****************************************************************************/
/**
 *  @file   Command.cpp
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
#include "Command.h"
#include "Parameter.h"
#include "Global.h"
#include <string>
#include <kvs/MouseEvent>
#include <kvs/Dicom>
#include <kvs/ImageObject>
#include <kvs/ImageImporter>
#include <kvs/Date>
#include <kvs/Time>
#include <kvs/Vector2>


namespace
{

/*===========================================================================*/
/**
 *  @brief  Returns an output filename.
 *  @param  extension [in] file extension
 *  @return output filename
 */
/*===========================================================================*/
const std::string GetOutputFilename( const std::string& extension )
{
    const kvs::Date today;
    const kvs::Time now;
    const std::string basename = "test";
    const std::string today_str = today.toString();
    const std::string now_str = now.toString("-");

    return( basename + "_" + today_str + "_" + now_str + "." + extension );
}

} // end of namespace

/*===========================================================================*/
/**
 *  @brief  Toggle for the DICOM information.
 */
/*===========================================================================*/
void Command::toggleInformationFlag( void )
{
    Parameter& p = Global::parameter;

    p.enable_show_information = !p.enable_show_information;
}

/*===========================================================================*/
/**
 *  @brief  Increment the index of the DICOM list.
 *  @param  value [in] incremental value
 */
/*===========================================================================*/
void Command::incrementIndex( const unsigned int value )
{
    Parameter& p = Global::parameter;

    const int nslices = p.dicom_list.size();

    p.index += value;
    p.index = kvs::Math::Min( p.index, nslices - 1 );

    Command::updateDicomWindow();
    Command::updateDicomImage();
}

/*===========================================================================*/
/**
 *  @brief  Decrement the index of the DICOM list.
 *  @param  value [in] decremental value
 */
/*===========================================================================*/
void Command::decrementIndex( const unsigned int value )
{
    Parameter& p = Global::parameter;

    p.index -= value;
    p.index = kvs::Math::Max( p.index, 0 );

    Command::updateDicomWindow();
    Command::updateDicomImage();
}

/*===========================================================================*/
/**
 *  @brief  Update DICOM image.
 */
/*===========================================================================*/
void Command::updateDicomImage( void )
{
    Parameter& p = Global::parameter;

    Global::object_manager->erase();

    const kvs::Dicom* dicom  = p.dicom_list[ p.index ];
    kvs::ImageObject* object = new kvs::ImageImporter( dicom );

    int object_id = Global::object_manager->insert( object );
    Global::id_manager->changeObject( object_id );
}

/*===========================================================================*/
/**
 *  @brief  Update DICOM window.
 */
/*===========================================================================*/
void Command::updateDicomWindow( void )
{
    Parameter& p = Global::parameter;

    kvs::Dicom* dicom = p.dicom_list[ p.index ];
    dicom->changeWindow( p.window_level, p.window_width );
}

/*===========================================================================*/
/**
 *  @brief  Reset DICOM image.
 */
/*===========================================================================*/
void Command::resetDicomWindow( void )
{
    Parameter& p = Global::parameter;

    const kvs::Dicom* dicom = p.dicom_list[ p.index ];

    p.window_width = dicom->windowWidth();
    p.window_level = dicom->windowLevel();

    Command::updateDicomWindow();
    Command::updateDicomImage();
};

/*===========================================================================*/
/**
 *  @brief  Function for the mouse press event.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void Command::pressMouse( kvs::MouseEvent* event )
{
    Parameter& p = Global::parameter;

    p.mouse.set( event->x(), event->y() );
};

/*===========================================================================*/
/**
 *  @brief  Function for the mouse move event.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void Command::moveMouse( kvs::MouseEvent* event )
{
    Parameter& p = Global::parameter;

    kvs::Vector2i diff( kvs::Vector2i( event->x(), event->y() ) - p.mouse );

    p.mouse.set( event->x(), event->y() );

    p.window_width += diff.x();
    p.window_level += diff.y();

    const kvs::Dicom* dicom = p.dicom_list[ p.index ];
    int min_window_value = dicom->minWindowValue();
    int max_window_value = dicom->maxWindowValue();
    int min_window_width = 0;
    int max_window_width = max_window_value - min_window_value + 1;
    p.window_width =
        kvs::Math::Clamp( p.window_width, min_window_width, max_window_width );
    p.window_level =
        kvs::Math::Clamp( p.window_level, min_window_value, max_window_value );

    Command::updateDicomWindow();
    Command::updateDicomImage();
}

/*===========================================================================*/
/**
 *  @brief  Writes a screen image.
 */
/*===========================================================================*/
void Command::writeScreenImage( void )
{
    const std::string filename = ::GetOutputFilename("bmp");
    Global::camera->snapshot().write( filename.c_str() );
}

/*===========================================================================*/
/**
 *  @brief  Writes a DICOM header data as ascii data.
 */
/*===========================================================================*/
void Command::writeHeader( void )
{
    Parameter& p = Global::parameter;

    const std::string filename = ::GetOutputFilename("csv");
    p.dicom_list[ p.index ]->write( filename.c_str() );
}

/*===========================================================================*/
/**
 *  @brief  Writes a DICOM data as raw data.
 */
/*===========================================================================*/
void Command::writeData( void )
{
    Parameter& p = Global::parameter;

    const std::string filename = ::GetOutputFilename("raw");
    p.dicom_list[ p.index ]->write( filename.c_str() );
}
