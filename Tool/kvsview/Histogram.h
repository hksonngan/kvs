/*****************************************************************************/
/**
 *  @file   Histogram.h
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
#ifndef KVSVIEW__HISTOGRAM_H_INCLUDE
#define KVSVIEW__HISTOGRAM_H_INCLUDE

#include <string>
#include <kvs/FrequencyTable>
#include <kvs/glut/ScreenBase>
#include <kvs/glut/GlobalBase>
#include <kvs/Texture2D>
#include <kvs/CommandLine>
#include "Argument.h"


namespace kvsview
{

namespace Histogram
{

const std::string CommandName("Histogram");
const std::string Description("Rendering histogram. (optional)");
const bool Check( const std::string& filename );

/*===========================================================================*/
/**
 *  @brief  Argument class.
 */
/*===========================================================================*/
class Argument : public kvsview::Argument::Common
{
public:

    Argument( int argc, char** argv );

public:

    const float biasParameter( void );
};

/*===========================================================================*/
/**
 *  @brief  Global class.
 */
/*===========================================================================*/
class Global : public kvs::glut::GlobalBase
{
public:

    static kvs::Vector2i mouse; ///< mouse information for controling the bias parameter
    static kvs::FrequencyTable frequency_table; ///< frequency table
    static float bias_parameter; ///< bias parameter
    static kvs::Texture2D histogram; ///< histogram texture

public:

    Global( int argc, char** argv );

    static bool createFrequencyTable( const std::string& filename );
};

/*===========================================================================*/
/**
 *  @brief  Screen class.
 */
/*===========================================================================*/
class Screen : public kvs::glut::ScreenBase
{
public:

    Screen( void );

    static void initialize_function( void );

    static void paint_event( void );

    static void mouse_press_event( kvs::MouseEvent* event );

    static void mouse_move_event( kvs::MouseEvent* event );

    static void key_press_event( kvs::KeyEvent* event );

public:

    static void draw_histogram( void );

    static const kvs::ValueArray<kvs::UInt8> get_histogram_image( void );

    static void create_histogram_texture( void );

    static void update_histogram_texture( void );
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

} // end of namespace Histogram

} // end of namespace kvsview

#endif // KVSVIEW__HISTOGRAM_H_INCLUDE
