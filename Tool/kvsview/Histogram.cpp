/*****************************************************************************/
/**
 *  @file   Histogram.cpp
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
#include "Histogram.h"
#include "CommandName.h"
#include <kvs/AVSField>
#include <kvs/AVSUcd>
#include <kvs/KVSMLObjectStructuredVolume>
#include <kvs/KVSMLObjectUnstructuredVolume>
#include <kvs/StructuredVolumeObject>
#include <kvs/UnstructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/UnstructuredVolumeImporter>
#include <kvs/FrequencyTable>
#include <kvs/MouseButton>
#include <kvs/Key>
#include <kvs/glut/ScreenBase>
#include <kvs/glut/GlobalBase>
#include <string>


namespace
{

inline const bool CheckStructuredVolumeData( const std::string& filename )
{
    if ( kvs::KVSMLObjectStructuredVolume::CheckFileExtension( filename ) )
    {
        if ( kvs::KVSMLObjectStructuredVolume::CheckFileFormat( filename ) )
        {
            return( true );
        }
    }

    if ( kvs::AVSField::CheckFileExtension( filename ) )
    {
        return( true );
    }

    return( false );
}

inline const bool CheckUnstructuredVolumeData( const std::string& filename )
{
    if ( kvs::KVSMLObjectUnstructuredVolume::CheckFileExtension( filename ) )
    {
        if ( kvs::KVSMLObjectUnstructuredVolume::CheckFileFormat( filename ) )
        {
            return( true );
        }
    }

    if ( kvs::AVSUcd::CheckFileExtension( filename ) )
    {
        return( true );
    }

    return( false );
}

} // end of namespace


namespace kvsview
{

namespace Histogram
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a transfer function renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, kvsview::Histogram::CommandName )
{
    // Parameters for the transfer function renderer class.
    add_option( kvsview::Histogram::CommandName, kvsview::Histogram::Description, 0 );
    add_option( "b", "Bias parameter in [0,1]. (defalt: 0.5)", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns the bias parameter.
 *  @return bias parameter
 */
/*===========================================================================*/
const float Argument::biasParameter( void )
{
    const float default_value = 0.5f;

    if ( this->hasOption("b") ) return( kvs::Math::Clamp( this->optionValue<float>("b"), 0.0f, 1.0f ) );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Global class.
 *  @param  argc [in] argmunet count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Global::Global( int argc, char** argv ):
    kvs::glut::GlobalBase( argc, argv )
{
}

/*===========================================================================*/
/**
 *  @brief  Creates a frequency table.
 *  @param  filename [in] input data file name
 *  @return true, if the frequency table is created successfully
 */
/*===========================================================================*/
bool Global::createFrequencyTable( const std::string& filename )
{
    if ( ::CheckStructuredVolumeData( filename ) )
    {
        kvs::StructuredVolumeObject* object = new kvs::StructuredVolumeImporter( filename );
        if ( !object )
        {
            kvsMessageError("Cannot import a structured volume object.");
            return( false );
        }

        object->updateMinMaxValues();

        frequency_table.create( object );
    }
    else if ( ::CheckUnstructuredVolumeData( filename ) )
    {
        kvs::UnstructuredVolumeObject* object = new kvs::UnstructuredVolumeImporter( filename );
        if ( !object )
        {
            kvsMessageError("Cannot import a structured volume object.");
            return( false );
        }

        object->updateMinMaxValues();

        frequency_table.create( object );
    }

    return( true );
}

// Instantiation of global parameters.
kvs::Vector2i Global::mouse;
kvs::FrequencyTable Global::frequency_table;
float Global::bias_parameter;
kvs::Texture2D Global::histogram;

/*===========================================================================*/
/**
 *  @brief  Constructs a new Screen class or displaying a transfer function.
 */
/*===========================================================================*/
Screen::Screen( void )
{
    setMousePressEvent( mouse_press_event );
    setMouseMoveEvent( mouse_move_event );

    addInitializeFunc( initialize_function );
    addPaintEvent( paint_event );
    addKeyPressEvent( key_press_event );
}

/*===========================================================================*/
/**
 *  @brief  Inititalize function.
 */
/*===========================================================================*/
void Screen::initialize_function( void )
{
    create_histogram_texture();
}

/*===========================================================================*/
/**
 *  @brief  Paint event function.
 */
/*===========================================================================*/
void Screen::paint_event( void )
{
    const kvs::RGBColor color( 212, 221, 229 );
    Global::background->setColor( color );

    int vp[4]; glGetIntegerv( GL_VIEWPORT, static_cast<GLint*>( vp ) );
    const int left = vp[0];
    const int bottom = vp[1];
    const int right = vp[2];
    const int top = vp[3];

    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    {
        glLoadIdentity();

        glMatrixMode( GL_PROJECTION );
        glPushMatrix();
        {
            glLoadIdentity();

            const float front = 0.0f;
            const float back = 2000.0f;
            glOrtho( left, right, bottom, top, front, back );

            draw_histogram();
        }
        glPopMatrix();
        glMatrixMode( GL_MODELVIEW );
    }
    glPopMatrix();

    glPopAttrib();
}

/*===========================================================================*/
/**
 *  @brief  Mouse press event function.
 *  @param  event [in] mouse event
 */
/*===========================================================================*/
void Screen::mouse_press_event( kvs::MouseEvent* event )
{
    switch( event->button() )
    {
    case kvs::MouseButton::Left:
    {
        Global::mouse.set( event->x(), event->y() );
        break;
    }
    default: break;
    }
}

/*===========================================================================*/
/**
 *  @brief  Mouse move event function.
 *  @param  event [in] mouse event
 */
/*===========================================================================*/
void Screen::mouse_move_event( kvs::MouseEvent* event )
{
    kvs::Vector2i diff( kvs::Vector2i( event->x(), event->y() ) - Global::mouse );

    Global::mouse.set( event->x(), event->y() );
    Global::bias_parameter -= diff.y() * 0.005f;
    Global::bias_parameter = kvs::Math::Clamp( Global::bias_parameter, 0.0f, 0.99999f );

    update_histogram_texture();
    redraw();
}

/*===========================================================================*/
/**
 *  @brief  Key press event function.
 *  @param  event [in] key event
 */
/*===========================================================================*/
void Screen::key_press_event( kvs::KeyEvent* event )
{
    switch( event->key() )
    {
    case kvs::Key::Home:
    {
        Global::bias_parameter = 0.5f;
        update_histogram_texture();
        redraw();
        break;
    }
    default: break;
    }
}

/*===========================================================================*/
/**
 *  @brief  Draws the histogram texture.
 */
/*===========================================================================*/
void Screen::draw_histogram( void )
{
    const GLfloat x = 0;
    const GLfloat y = 0;
    const GLfloat width = static_cast<GLfloat>( Screen::m_width );
    const GLfloat height = static_cast<GLfloat>( Screen::m_height );

    glEnable( GL_TEXTURE_2D );
    Global::histogram.bind();
    {
        glBegin( GL_QUADS );
        {
            glTexCoord2f( 0.0f, 0.0f ); glVertex2f( x,         y );
            glTexCoord2f( 1.0f, 0.0f ); glVertex2f( x + width, y );
            glTexCoord2f( 1.0f, 1.0f ); glVertex2f( x + width, y + height );
            glTexCoord2f( 0.0f, 1.0f ); glVertex2f( x,         y + height );
        }
        glEnd();
    }
    Global::histogram.unbind();
}

/*===========================================================================*/
/**
 *  @brief  Returns pixel data of the histogram image.
 *  @return pixel data of the histogram image
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8> Screen::get_histogram_image( void )
{
    const size_t nchannels = 4;
    const size_t width = Global::frequency_table.nbins();
    const size_t height = width;
    const size_t npixels = width * height;

    kvs::ValueArray<kvs::UInt8> data( npixels * nchannels );
    data.fill( 0x00 );

    const kvs::RGBColor histogram_color( 100, 100, 100 );

    const float g = Global::bias_parameter; // bias parameter
    const kvs::Real32 normalized_factor = 1.0f / ( Global::frequency_table.maxCount() );
    for ( size_t i = 0; i < width; i++ )
    {
        const size_t n = Global::frequency_table.bin().at(i);
        const float f = n * normalized_factor; // frequency count (normalized in [0,1])
        const float b = std::pow( f, static_cast<float>( std::log(g) / std::log(0.5) ) );

        const size_t h = static_cast<size_t>( b * height + 0.5f );
        for ( size_t j = 0; j < h; j++ )
        {
            const size_t index = i + j * width;
            data[ 4 * index + 0 ] = histogram_color.r();
            data[ 4 * index + 1 ] = histogram_color.g();
            data[ 4 * index + 2 ] = histogram_color.b();
            data[ 4 * index + 3 ] = kvs::UInt8( 255 );
        }
    }

    return( data );
}

/*===========================================================================*/
/**
 *  @brief  Creates a histogram texture.
 */
/*===========================================================================*/
void Screen::create_histogram_texture( void )
{
    const size_t nchannels = 4;
    const size_t width = Global::frequency_table.nbins();
    const size_t height = width;

    Global::histogram.setPixelFormat( nchannels, sizeof( kvs::UInt8 ) );
    Global::histogram.create( width, height );
    Global::histogram.download( width, height, get_histogram_image().pointer() );
}

/*===========================================================================*/
/**
 *  @brief  Update the histogram texture.
 */
/*===========================================================================*/
void Screen::update_histogram_texture( void )
{
    Global::histogram.release();
    create_histogram_texture();
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Main::Main( int argc, char** argv )
{
    m_argc = argc;
    m_argv = argv;
}

/*===========================================================================*/
/**
 *  @brief  Executes main process.
 */
/*===========================================================================*/
const bool Main::exec( void )
{
    // Create the global parameters.
    Global* global = new Global( m_argc, m_argv );
    if( !global )
    {
        kvsMessageError("Cannot allocate memory for 'global'.");
        return( false );
    }

    Argument arg( m_argc, m_argv );
    if ( !arg.parse() ) exit( EXIT_FAILURE );

    m_input_name = arg.value<std::string>();

    if ( !Global::createFrequencyTable( m_input_name ) ) exit( EXIT_FAILURE );

    Global::bias_parameter = arg.biasParameter();

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "HISTOGRAM INFORMATION" << std::endl;
        std::cout << "min range: " << Global::frequency_table.minRange() << std::endl;
        std::cout << "max range: " << Global::frequency_table.maxRange() << std::endl;
        std::cout << "number of bins: " << Global::frequency_table.nbins() << std::endl;
        std::cout << "max count: " << Global::frequency_table.maxCount() << std::endl;
    }

    // Create and show the rendering screen.
    Screen* screen = new Screen();
    if( !screen )
    {
        kvsMessageError("Cannot allocate memory for 'screen'.");
        return( false );
    }

    screen->setGeometry( 0, 0, 512, 150 );
    screen->setTitle( kvsview::CommandName + " - " + kvsview::Histogram::CommandName );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}

} // end of namespace Histogram

} // end of namespace kvsview
