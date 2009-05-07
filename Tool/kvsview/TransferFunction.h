/*****************************************************************************/
/**
 *  @file   TransferFunction.h
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
#ifndef KVSVIEW__TRANSFER_FUNCTION_H_INCLUDE
#define KVSVIEW__TRANSFER_FUNCTION_H_INCLUDE

#include <string>
#include <kvs/TransferFunction>
#include <kvs/glut/ScreenBase>
#include <kvs/glut/GlobalBase>
#include <kvs/Texture1D>
#include <kvs/Texture2D>
#include <kvs/CommandLine>
#include "Argument.h"


namespace kvsview
{

namespace TransferFunction
{

const std::string CommandName("TransferFunction");
const std::string Description("Rendering a transfer function. (optional)");

/*===========================================================================*/
/**
 *  @brief  Argument class.
 */
/*===========================================================================*/
class Argument : public kvsview::Argument::Common
{
public:

    Argument( int argc, char** argv );

    const bool hasColorMapOption( void );

    const bool hasOpacityMapOption( void );
};

/*===========================================================================*/
/**
 *  @brief  Global class.
 */
/*===========================================================================*/
class Global : public kvs::glut::GlobalBase
{
public:

    static kvs::TransferFunction transfer_function;
    static kvs::Texture1D color_map;
    static kvs::Texture1D opacity_map;
    static kvs::Texture2D checkerboard;

public:

    Global( int argc, char** argv );
};

/*===========================================================================*/
/**
 *  @brief  Screen class.
 */
/*===========================================================================*/
class Screen : public kvs::glut::ScreenBase
{
public:

    static bool has_color_map_option;
    static bool has_opacity_map_option;

public:

    Screen( const bool color_map_option, const bool opacity_map_option );

    static void initialize_function( void );

    static void initialize_color_map_texture( void );

    static void initialize_opacity_map_texture( void );

    static void initialize_checkerboard_texture( void );

    static void paint_event( void );

    static void draw_checkerboard_texture( const GLenum src_factor, const GLenum dst_factor );

    static void draw_opacity_map_texture( const GLenum src_factor, const GLenum dst_factor );

    static void draw_color_map_texture( const GLenum src_factor, const GLenum dst_factor );

    static void draw_texture( const float texture_width, const float texture_height );
};

/*===========================================================================*/
/**
 *  @brief  Main class.
 */
/*===========================================================================*/
class Main
{
protected:

    int         m_argc;        ///< argument count
    char**      m_argv;        ///< argument values
    std::string m_input_name;  ///< input filename
    std::string m_output_name; ///< output filename

public:

    Main( int argc, char** argv );

public:

    const bool exec( void );
};

} // end of namespace TransferFunction

} // end of namespace kvsview

#endif // KVSVIEW__TRANSFER_FUNCTION_H_INCLUDE
