/*****************************************************************************/
/**
 *  @file   Isosurface.cpp
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
#include "Isosurface.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/Isosurface>
#include <kvs/Value>
#include <kvs/KeyPressEventListener>
#include <kvs/Key>
#include <kvs/glut/Screen>
#include <kvs/glut/Application>
#include <kvs/glut/LegendBar>
#include <kvs/glut/OrientationAxis>


namespace Widget
{

/*===========================================================================*/
/**
 *  @brief  Isolevel slider class.
 */
/*===========================================================================*/
class IsolevelSlider : public kvs::glut::Slider
{
    const kvs::VolumeObjectBase*   m_volume; ///< pointer to the volume object
    kvs::TransferFunction          m_tfunc;  ///< transfer function
    kvs::PolygonObject::NormalType m_normal; ///< normal vector type

public:

    IsolevelSlider( kvs::glut::Screen* screen ):
        kvs::glut::Slider( screen ),
        m_volume( NULL ),
        m_tfunc( NULL ),
        m_normal( kvs::PolygonObject::PolygonNormal ) {}

    void setVolumeObject( const kvs::VolumeObjectBase* volume )
    {
        m_volume = volume;
    }

    void setTransferFunction( const kvs::TransferFunction& tfunc )
    {
        m_tfunc = tfunc;
    }

    void setNormal( const kvs::PolygonObject::NormalType normal )
    {
        m_normal = normal;
    }

    void valueChanged( void )
    {
        const double level = this->value();
        const bool d = true;
        kvs::PolygonObject* object = new kvs::Isosurface( m_volume, level, m_normal, d, m_tfunc );
        if ( object ) screen()->objectManager()->change( 1, object );
    }
};

} // end of namespace Widget


namespace kvsview
{

namespace Isosurface
{

class KeyPressEvent : public kvs::KeyPressEventListener
{
    void update( kvs::KeyEvent* ev )
    {
        switch ( ev->key() )
        {
        case kvs::Key::o: screen()->controlTarget() = kvs::ScreenBase::TargetObject; break;
        case kvs::Key::l: screen()->controlTarget() = kvs::ScreenBase::TargetLight; break;
        case kvs::Key::c: screen()->controlTarget() = kvs::ScreenBase::TargetCamera; break;
        default: break;
        }
    }
};

class LegendBar : public kvs::glut::LegendBar
{
public:

    LegendBar( kvs::ScreenBase* screen ):
        kvs::glut::LegendBar( screen )
    {
        setWidth( 200 );
        setHeight( 50 );
    }

    void screenResized( void )
    {
        setX( screen()->width() - width() );
        setY( screen()->height() - height() );
    }
};

class OrientationAxis : public kvs::glut::OrientationAxis
{
public:

    OrientationAxis( kvs::ScreenBase* screen ):
        kvs::glut::OrientationAxis( screen )
    {
        setMargin( 10 );
        setSize( 90 );
        setBoxType( kvs::glut::OrientationAxis::SolidBox );
        enableAntiAliasing();
    }

    void screenResized( void )
    {
        setY( screen()->height() - height() );
    }
};

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a point renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, "Isosurface")
{
    // Parameters for the isosurface class.
    add_option( kvsview::Isosurface::CommandName, kvsview::Isosurface::Description, 0 );
    add_option( "l", "Isosurface level. (default: mean value)", 1, false );
    add_option( "n", "Normal vector type; 'poly[gon]' 'vert[ex]'. (default: poly)", 1, false );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns a isolevel.
 *  @return subpixel level
 */
/*===========================================================================*/
const kvs::Real64 Argument::isolevel( const kvs::VolumeObjectBase* volume )
{
    if ( !volume->hasMinMaxValues() ) volume->updateMinMaxValues();
    const kvs::Real64 default_value = ( volume->maxValue() - volume->minValue() ) * 0.5;

    if ( this->hasOption("l") ) return( this->optionValue<kvs::Real64>("l") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a polygon normal vector type.
 *  @return normal vector type
 */
/*===========================================================================*/
const kvs::PolygonObject::NormalType Argument::normalType( void )
{
    const kvs::PolygonObject::NormalType default_value = kvs::PolygonObject::PolygonNormal;

    kvs::PolygonObject::NormalType normal_type = default_value;
    if ( this->hasOption("n") )
    {
        const std::string option_value = this->optionValue<std::string>("n");
        if ( option_value == "poly" ||
             option_value == "polygon" )
        {
            normal_type = kvs::PolygonObject::PolygonNormal;
        }
        else if ( option_value == "vert" ||
                  option_value == "vertex" )
        {
            normal_type = kvs::PolygonObject::VertexNormal;
        }
        else
        {
            kvsMessageError("Unknown normal type '%s'.",option_value.c_str());
        }
    }

    return( normal_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns a transfer function.
 *  @return transfer function
 */
/*===========================================================================*/
const kvs::TransferFunction Argument::transferFunction( void )
{
    if ( this->hasOption("t") )
    {
        const std::string filename = this->optionValue<std::string>("t");
        return( kvs::TransferFunction( filename ) );
    }
    else
    {
        const size_t resolution = 256;
        return( kvs::TransferFunction( resolution ) );
    }
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class for a point renderer.
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
    kvs::glut::Application app( m_argc, m_argv );

    // Parse specified arguments.
    Isosurface::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    KeyPressEvent key_press_event;

    // Create a global and screen class.
    kvs::glut::Screen screen( &app );
    screen.addKeyPressEvent( &key_press_event );
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::Isosurface::CommandName );
    arg.applyTo( screen );

    // Create a isolevel slider.
    Widget::IsolevelSlider slider( &screen );
    slider.setMargin( 10 );
    slider.setCaption("Isolevel");

    // Check the input point data.
    m_input_name = arg.value<std::string>();
    if ( !(kvsview::FileChecker::ImportableStructuredVolume( m_input_name ) ||
           kvsview::FileChecker::ImportableUnstructuredVolume( m_input_name ) ) )
    {
        kvsMessageError("%s is not volume data.", m_input_name.c_str());
        return( false );
    }

    // Visualization pipeline.
    kvs::VisualizationPipeline pipe( m_input_name );
    pipe.import();

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "IMPORTED OBJECT" << std::endl;
        std::cout << kvsview::ObjectInformation( pipe.object() ) << std::endl;
        std::cout << std::endl;
    }

    // Legend bar.
    Isosurface::LegendBar legend_bar( &screen );
    const double min_value = kvs::VolumeObjectBase::DownCast( pipe.object() )->minValue();
    const double max_value = kvs::VolumeObjectBase::DownCast( pipe.object() )->maxValue();
    legend_bar.setColorMap( arg.transferFunction().colorMap() );
    legend_bar.setRange( min_value, max_value );
    legend_bar.show();

    // Orientation axis.
    Isosurface::OrientationAxis orientation_axis( &screen );
    orientation_axis.show();

    // Get the imported object.
    const kvs::ObjectBase* object = pipe.object();
    const kvs::VolumeObjectBase* volume = kvs::VolumeObjectBase::DownCast( object );
    slider.setVolumeObject( volume );

    // Set up the isosurface class.
    kvs::PipelineModule mapper( new kvs::Isosurface );
    const kvs::Real64 level = arg.isolevel( volume );
    const kvs::PolygonObject::NormalType normal = arg.normalType();
    const kvs::TransferFunction function = arg.transferFunction();
    mapper.get<kvs::Isosurface>()->setIsolevel( level );
    mapper.get<kvs::Isosurface>()->setNormalType( normal );
    mapper.get<kvs::Isosurface>()->setTransferFunction( function );

    // Construct the visualization pipeline.
    pipe.connect( mapper );
    if ( !pipe.exec() )
    {
        kvsMessageError("Cannot execute the visulization pipeline.");
        return( false );
    }

    screen.registerObject( &pipe );
    slider.setTransferFunction( function );
    slider.setNormal( normal );
    slider.setValue( static_cast<float>( level ) );
    slider.setRange( static_cast<float>( volume->minValue() ), static_cast<float>( volume->maxValue() ) );

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "RENDERERED OBJECT" << std::endl;
        std::cout << kvsview::ObjectInformation( pipe.object() ) << std::endl;
        std::cout << std::endl;
        std::cout << "VISUALIZATION PIPELINE" << std::endl;
        std::cout << pipe << std::endl;
    }

    // Apply the specified parameters to the global and the visualization pipeline.
    arg.applyTo( screen, pipe );

    // Show the screen and the slider widget.
    screen.show();
    slider.show();

    return( app.run() );
}

} // end of namespace Default

} // end of namespace kvsview
