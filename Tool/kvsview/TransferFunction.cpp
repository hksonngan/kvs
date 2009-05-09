/*****************************************************************************/
/**
 *  @file   TransferFunction.cpp
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
#include "TransferFunction.h"
#include "CommandName.h"
#include <kvs/XMLDocument>
#include <kvs/XMLNode>
#include <kvs/KVSMLTransferFunction>
#include <kvs/TransferFunction>
#include <kvs/glut/ScreenBase>
#include <kvs/glut/GlobalBase>
#include <kvs/Texture1D>
#include <kvs/Texture2D>


namespace kvsview
{

namespace TransferFunction
{

/*===========================================================================*/
/**
 *  @brief  Checks whether the given file is KVSML transfer function format or not.
 *  @param  filename [in] filename
 *  @return true, if the given file is KVSML transfer function format
 */
/*===========================================================================*/
const bool Check( const std::string& filename )
{
    if ( kvs::KVSMLTransferFunction::CheckFileExtension( filename ) )
    {
        // Find a TransferFunction tag without error messages.
        kvs::XMLDocument document;
        if ( !document.read( filename ) ) return( false );

        // <KVSML>
        const std::string kvsml_tag("KVSML");
        const kvs::XMLNode::SuperClass* kvsml_node = kvs::XMLDocument::FindNode( &document, kvsml_tag );
        if ( !kvsml_node ) return( false );

        // <TransferFunction>
        const std::string tfunc_tag("TransferFunction");
        const kvs::XMLNode::SuperClass* tfunc_node = kvs::XMLNode::FindChildNode( kvsml_node, tfunc_tag );
        if ( !tfunc_node ) return( false );

        return( true );
    }

    return( false );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a transfer function renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, kvsview::TransferFunction::CommandName )
{
    // Parameters for the transfer function renderer class.
    add_option( kvsview::TransferFunction::CommandName, kvsview::TransferFunction::Description, 0 );
    add_option("c", "Display color map. (optional)", 0, false );
    add_option("a", "Display opacity (alpha) map. (optional)", 0, false );
}

/*===========================================================================*/
/**
 *  @brief  Checks whether the color map option is specified or not.
 *  @return true, if the color map option is specified
 */
/*===========================================================================*/
const bool Argument::hasColorMapOption( void )
{
    return( this->hasOption("c") );
}

/*===========================================================================*/
/**
 *  @brief  Checks whether the opacity map option is specified or not.
 *  @return true, if the opacity map option is specified
 */
/*===========================================================================*/
const bool Argument::hasOpacityMapOption( void )
{
    return( this->hasOption("a") );
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

// Instantiation of global parameters.
kvs::TransferFunction Global::transfer_function;
kvs::Texture1D Global::color_map;
kvs::Texture2D Global::checkerboard;

/*===========================================================================*/
/**
 *  @brief  Constructs a new Screen class or displaying a transfer function.
 *  @param  color_map_option [in] flag for the color map option
 *  @param  opacity_map_option [in] flag for the opacity map option
 */
/*===========================================================================*/
Screen::Screen( const bool color_map_option, const bool opacity_map_option )
{
    has_color_map_option = color_map_option;
    has_opacity_map_option = opacity_map_option;

    addInitializeFunc( initialize_function );
    addPaintEvent( paint_event );
}

/*===========================================================================*/
/**
 *  @brief  Inititalize function.
 */
/*===========================================================================*/
void Screen::initialize_function( void )
{
    // Setup textures.
    initialize_color_map_texture();
    initialize_checkerboard_texture();
}

/*===========================================================================*/
/**
 *  @brief  Initialize function for the color map with opacity.
 */
/*===========================================================================*/
void Screen::initialize_color_map_texture( void )
{
    const size_t nchannels  = 4; // rgba
    const size_t width = Global::transfer_function.colorMap().resolution();
    const kvs::UInt8* color_map = Global::transfer_function.colorMap().table().pointer();
    const kvs::Real32* opacity_map = Global::transfer_function.opacityMap().table().pointer();

    GLubyte data[width][nchannels];
    for ( size_t i = 0, i3 = 0; i < width; i++, i3 += 3 )
    {
        data[i][0] = static_cast<GLubyte>(color_map[i3]);
        data[i][1] = static_cast<GLubyte>(color_map[i3+1]);
        data[i][2] = static_cast<GLubyte>(color_map[i3+2]);
        data[i][3] = static_cast<GLubyte>(int(opacity_map[i] * 255.0f + 0.5));
    }

    Global::color_map.setPixelFormat( nchannels, sizeof( kvs::UInt8 ) );
    Global::color_map.setMinFilter( GL_LINEAR );
    Global::color_map.setMagFilter( GL_LINEAR );
    Global::color_map.create( width );
    Global::color_map.download( width, data );
}

/*===========================================================================*/
/**
 *  @brief  Initialize function for the checkerboard.
 */
/*===========================================================================*/
void Screen::initialize_checkerboard_texture( void )
{
    const size_t nchannels = 3;
    const int width = 32;
    const int height = 32;

    const int c1 = 255; // checkerboard color (gray value) 1
    const int c2 = 230; // checkerboard color (gray value) 2
    GLubyte data[width][height][nchannels];
    for ( int i = 0; i < height; i++ )
    {
        for ( int j = 0; j < width; j++ )
        {
            int c = ((((i&0x8)==0)^((j&0x8)==0))) * c1;
            c = ( c == 0 ) ? c2 : c;
            data[i][j][0] = static_cast<GLubyte>(c);
            data[i][j][1] = static_cast<GLubyte>(c);
            data[i][j][2] = static_cast<GLubyte>(c);
        }
    }

    Global::checkerboard.setPixelFormat( nchannels, sizeof( kvs::UInt8 ) );
    Global::checkerboard.setMinFilter( GL_NEAREST );
    Global::checkerboard.setMagFilter( GL_NEAREST );
    Global::checkerboard.setWrapS( GL_REPEAT );
    Global::checkerboard.setWrapT( GL_REPEAT );
    Global::checkerboard.create( width, height );
    Global::checkerboard.download( width, height, data );
}

/*===========================================================================*/
/**
 *  @brief  Paint event function.
 */
/*===========================================================================*/
void Screen::paint_event( void )
{
    const kvs::RGBColor white( 255, 255, 255 );
    Global::background->setColor( white );

    int vp[4]; glGetIntegerv( GL_VIEWPORT, (GLint*)vp );
    const int left = vp[0];
    const int bottom = vp[1];
    const int right = vp[2];
    const int top = vp[3];

    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );

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

            if ( has_color_map_option && !has_opacity_map_option )
            {
                // Draw the color map witout opacity.
                draw_color_map_texture( GL_ONE, GL_ZERO );
            }
            else if ( !has_color_map_option && has_opacity_map_option )
            {
                // Draw the opacity map on the checkerboard.
                draw_checkerboard_texture( GL_ONE, GL_ZERO );
                draw_color_map_texture( GL_ZERO, GL_ONE_MINUS_SRC_ALPHA );
            }
            else
            {
                // Draw the color map with the opacity on the checkerboard.
                draw_checkerboard_texture( GL_ONE, GL_ZERO );
                draw_color_map_texture( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
            }
        }
        glPopMatrix();
        glMatrixMode( GL_MODELVIEW );
    }
    glPopMatrix();

    glPopAttrib();
}

/*===========================================================================*/
/**
 *  @brief  Draws a checkerboard.
 *  @param  src_factor [in] blending factor for source color
 *  @param  dst_factor [in] blending factor for destination color
 */
/*===========================================================================*/
void Screen::draw_checkerboard_texture( const GLenum src_factor, const GLenum dst_factor )
{
    // Since the checkerboard is background, GL_ONE and GL_ZERO are always specified
    // for src_factor and dst_factor, rescpectively.

    glDisable( GL_TEXTURE_1D );
    glEnable( GL_TEXTURE_2D );
    glBlendFunc( src_factor, dst_factor );
    Global::checkerboard.bind();
    {
        const float scale = 0.6f;
        const float texture_width = ( Screen::m_width / 32.0f ) * scale;
        const float texture_height = ( Screen::m_height / 32.0f ) * scale;
        draw_texture( texture_width, texture_height );
    }
    Global::checkerboard.unbind();
}

/*===========================================================================*/
/**
 *  @brief  Draw a color map.
 *  @param  src_factor [in] blending factor for source color
 *  @param  dst_factor [in] blending factor for destination color
 */
/*===========================================================================*/
void Screen::draw_color_map_texture( const GLenum src_factor, const GLenum dst_factor )
{
    glEnable( GL_TEXTURE_1D );
    glDisable( GL_TEXTURE_2D );
    glBlendFunc( src_factor, dst_factor );
    Global::color_map.bind();
    {
        const float texture_width = 1.0f;
        const float texture_height = 1.0f;
        draw_texture( texture_width, texture_height );
    }
    Global::color_map.unbind();
}

/*===========================================================================*/
/**
 *  @brief  Draw a texture.
 *  @param  texture_width [in] texture width
 *  @param  texture_height [in] texture height
 */
/*===========================================================================*/
void Screen::draw_texture( const float texture_width, const float texture_height )
{
    const GLfloat x = 0;
    const GLfloat y = 0;
    const GLfloat width = Screen::m_width;
    const GLfloat height = Screen::m_height;

    glBegin( GL_QUADS );
    {
        glTexCoord2f( 0.0f,          0.0f );           glVertex2f( x,         y );
        glTexCoord2f( texture_width, 0.0f );           glVertex2f( x + width, y );
        glTexCoord2f( texture_width, texture_height ); glVertex2f( x + width, y + height );
        glTexCoord2f( 0.0f,          texture_height ); glVertex2f( x,         y + height );
    }
    glEnd();
}

bool Screen::has_color_map_option;
bool Screen::has_opacity_map_option;

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
    if ( !Global::transfer_function.read( m_input_name ) ) exit( EXIT_FAILURE );

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "IMPORTED OBJECT" << std::endl;
        std::cout << "resolution: " << Global::transfer_function.resolution() << std::endl;
    }

    // Create and show the rendering screen.
    Screen* screen = new Screen( arg.hasColorMapOption(), arg.hasOpacityMapOption() );
    if( !screen )
    {
        kvsMessageError("Cannot allocate memory for 'screen'.");
        return( false );
    }
    screen->setGeometry( 0, 0, 512, 150 );
    screen->setTitle( kvsview::CommandName + " - " + kvsview::TransferFunction::CommandName );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}

} // end of namespace TransferFunction

} // end of namespace kvsview
