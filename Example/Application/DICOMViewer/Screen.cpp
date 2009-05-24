/*****************************************************************************/
/**
 *  @file   Screen.cpp
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
#include "Screen.h"
#include "Global.h"
#include "Parameter.h"
#include "Command.h"
#include <kvs/RGBColor>
#include <kvs/Dicom>
#include <kvs/ImageObject>
#include <kvs/ImageRenderer>
#include <kvs/Key>
#include <kvs/MouseButton>
#include <kvs/glut/Text>


/*===========================================================================*/
/**
 *  @brief  Constructs a new Screen class.
 */
/*===========================================================================*/
Screen::Screen( void )
{
    setMousePressEvent( mouse_press_event );
    setMouseMoveEvent( mouse_move_event );

    addInitializeFunc( additional_initialize_func );
    addPaintEvent( additional_paint_event );
    addKeyPressEvent( additional_key_press_event );
}

/*===========================================================================*/
/**
 *  @brief  Mouse press event (Override the default mouse press event).
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void Screen::mouse_press_event( kvs::MouseEvent* event )
{
    switch( event->button() )
    {
    case kvs::MouseButton::Left: Command::pressMouse( event ); break;
    default: break;
    }

    switch( event->state() )
    {
    case kvs::MouseButton::Up:   Command::incrementIndex(); break;
    case kvs::MouseButton::Down: Command::decrementIndex(); break;
    default: break;
    }
}

/*===========================================================================*/
/**
 *  @brief  Mouse move event (Override the default mouse move event).
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void Screen::mouse_move_event( kvs::MouseEvent* event )
{
    Command::moveMouse( event );
    redraw();
}

/*===========================================================================*/
/**
 *  @brief  Additional initialize function.
 */
/*===========================================================================*/
void Screen::additional_initialize_func( void )
{
    Global::background->setColor( kvs::RGBColor( 0, 0, 0 ) );

    Parameter& p = Global::parameter;

    const kvs::Dicom* dicom = p.dicom_list[0];

    kvs::ImageObject* object = new kvs::ImageObject(
        dicom->column(), dicom->row(), dicom->pixelData(), kvs::ImageObject::Gray8 );
    kvs::ImageRenderer* renderer = new kvs::ImageRenderer();

    int object_id   = Global::object_manager->insert( object );
    int renderer_id = Global::renderer_manager->insert( renderer );

    Global::id_manager->insert( object_id, renderer_id );
}

/*===========================================================================*/
/**
 *  @brief  Additional paint event.
 */
/*===========================================================================*/
void Screen::additional_paint_event( void )
{
    Parameter& p = Global::parameter;

    if ( p.enable_show_information ) show_information();
}

/*===========================================================================*/
/**
 *  @brief  Additional key press event.
 *  @param  event [in] pointer to the key event
 */
/*===========================================================================*/
void Screen::additional_key_press_event( kvs::KeyEvent* event )
{
    switch( event->key() )
    {
    case kvs::Key::i:     Command::toggleInformationFlag(); break;
    case kvs::Key::s:     Command::writeScreenImage();      break;
    case kvs::Key::h:     Command::writeHeader();           break;
    case kvs::Key::w:     Command::writeData();             break;
    case kvs::Key::Up:    Command::incrementIndex(5);       break;
    case kvs::Key::Down:  Command::decrementIndex(5);       break;
    case kvs::Key::Right: Command::incrementIndex(1);       break;
    case kvs::Key::Left:  Command::decrementIndex(1);       break;
    default: break;
    }
}

/*===========================================================================*/
/**
 *  @brief  Shows the DICOM information.
 */
/*===========================================================================*/
void Screen::show_information( void )
{
    Parameter& p = Global::parameter;

    kvs::RGBColor text_color( 255, 255, 255 );

    int width  = Global::camera->windowWidth();
    int height = Global::camera->windowHeight();

    const kvs::Dicom* dicom = p.dicom_list[ p.index ];

    // Counter on top-right.
    int counter     = p.index + 1;
    int counter_max = p.dicom_list.size();
    kvs::glut::Text text1;
    text1.addText("[%04d/%04d]", counter, counter_max );
    text1.setColor( text_color );
    text1.setPosition( width - 100, height - 20 );
    text1.draw();

    // Manufacturer and modality on top-left.
    const std::string manufacturer = dicom->manufacturer();
    const std::string modality     = dicom->modality();
    kvs::glut::Text text2;
    text2.addText("Manufacturer: %s", manufacturer.c_str() );
    text2.addText("Modality:     %s", modality.c_str() );
    text2.setColor( text_color );
    text2.setPosition( 10, height - 20 );
    text2.draw();

    // Image information on bottom-left.
    kvs::glut::Text text3;
    text3.addText("Slice Thickness:   %.3lf", dicom->sliceThickness() );
    text3.addText("Slice Spacing:     %.3lf", dicom->sliceSpacing() );
    text3.addText("Series Number:     %d",    dicom->seriesNumber() );
    text3.addText("Image Number:      %d",    dicom->imageNumber() );
    text3.addText("Slice Location:    %.3lf", dicom->sliceLocation() );
    text3.addText("Row:               %d",    dicom->row() );
    text3.addText("Column:            %d",    dicom->column() );
    text3.addText("Bits Allocated:    %d",    dicom->bitsAllocated() );
    text3.addText("Bits Stored:       %d",    dicom->bitsStored() );
    text3.addText("High Bit:          %d",    dicom->highBit() );
    text3.addText("Pixel Spacing:     %.3lf %.3lf",
                  dicom->pixelSpacing()[0],
                  dicom->pixelSpacing()[1] );
    text3.addText("Rescale Slope:     %.3lf", dicom->rescaleSlope() );
    text3.addText("Rescale Intersept: %.3lf", dicom->rescaleIntersept() );
    text3.addText("Min. raw value:    %d",    dicom->minRawValue() );
    text3.addText("Max. raw value:    %d",    dicom->maxRawValue() );
    text3.addText("Min. value:        %d",    dicom->minValue() );
    text3.addText("Max. value:        %d",    dicom->maxValue() );
    text3.addText("Window Level:      %d",    p.window_level );
    text3.addText("Window Width:      %d",    p.window_width );
    text3.setColor( text_color );
    text3.setPosition( 10, 225 );
    text3.draw();
}
