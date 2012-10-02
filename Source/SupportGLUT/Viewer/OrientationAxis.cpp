/****************************************************************************/
/**
 *  @file OrientationAxis.cpp
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
#include "OrientationAxis.h"
#include <kvs/ObjectManager>
#include <kvs/EventBase>
#include <kvs/ScreenBase>
#include <kvs/glut/Screen>
#include <kvs/glut/GLUT>


// Default parameters.
namespace { namespace Default
{
const size_t AxisWindowSize = 80;
} }


namespace kvs
{

namespace glut
{

OrientationAxis::OrientationAxis( kvs::glut::Screen* screen ):
    kvs::glut::WidgetBase( screen ),
    m_object( screen->objectManager() ),
    m_x_tag( "x" ),
    m_y_tag( "y" ),
    m_z_tag( "z" ),
    m_x_axis_color( kvs::RGBColor( 200, 10, 10 ) ),
    m_y_axis_color( kvs::RGBColor( 10, 200, 10 ) ),
    m_z_axis_color( kvs::RGBColor( 10, 10, 200 ) ),
    m_axis_line_width( 1.0f ),
    m_box_color( kvs::RGBColor( 200, 200, 200 ) ),
    m_box_line_color( kvs::RGBColor( 10, 10, 10 ) ),
    m_box_line_width( 1.0f ),
    m_enable_anti_aliasing( false ),
    m_axis_type( OrientationAxis::CorneredAxis ),
    m_box_type( OrientationAxis::NoneBox ),
    m_projection_type( kvs::Camera::Perspective )
{
    BaseClass::setEventType(
        kvs::EventBase::PaintEvent |
        kvs::EventBase::ResizeEvent );

    BaseClass::setMargin( 0 );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new orientation axis class.
 *  @param  screen [in] pointer to the screen
 */
/*===========================================================================*/
OrientationAxis::OrientationAxis( kvs::ScreenBase* screen, const kvs::ObjectBase* object ):
    kvs::glut::WidgetBase( screen ),
    m_object( object ),
    m_x_tag( "x" ),
    m_y_tag( "y" ),
    m_z_tag( "z" ),
    m_x_axis_color( kvs::RGBColor( 200, 10, 10 ) ),
    m_y_axis_color( kvs::RGBColor( 10, 200, 10 ) ),
    m_z_axis_color( kvs::RGBColor( 10, 10, 200 ) ),
    m_axis_line_width( 1.0f ),
    m_box_color( kvs::RGBColor( 200, 200, 200 ) ),
    m_box_line_color( kvs::RGBColor( 10, 10, 10 ) ),
    m_box_line_width( 1.0f ),
    m_enable_anti_aliasing( false ),
    m_axis_type( OrientationAxis::CorneredAxis ),
    m_box_type( OrientationAxis::NoneBox ),
    m_projection_type( kvs::Camera::Perspective )
{
    BaseClass::setEventType(
        kvs::EventBase::PaintEvent |
        kvs::EventBase::ResizeEvent );

    BaseClass::setMargin( 0 );
}

/*===========================================================================*/
/**
 *  @brief  Destroys the orientation axis class.
 */
/*===========================================================================*/
OrientationAxis::~OrientationAxis( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the X axis tag.
 *  @return X axis tag
 */
/*===========================================================================*/
const std::string& OrientationAxis::xTag( void ) const
{
    return( m_x_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns the Y axis tag.
 *  @return Y axis tag
 */
/*===========================================================================*/
const std::string& OrientationAxis::yTag( void ) const
{
    return( m_y_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns the Z axis tag.
 *  @return Z axis tag
 */
/*===========================================================================*/
const std::string& OrientationAxis::zTag( void ) const
{
    return( m_z_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns the X axis color.
 *  @return X axis color
 */
/*===========================================================================*/
const kvs::RGBColor& OrientationAxis::xAxisColor( void ) const
{
    return( m_x_axis_color );
}

/*===========================================================================*/
/**
 *  @brief  Returns the Y axis color.
 *  @return Y axis color
 */
/*===========================================================================*/
const kvs::RGBColor& OrientationAxis::yAxisColor( void ) const
{
    return( m_y_axis_color );
}

/*===========================================================================*/
/**
 *  @brief  Returns the Z axis color.
 *  @return Z axis color
 */
/*===========================================================================*/
const kvs::RGBColor& OrientationAxis::zAxisColor( void ) const
{
    return( m_z_axis_color );
}

/*===========================================================================*/
/**
 *  @brief  Returns the line width of the axis.
 *  @return line width
 */
/*===========================================================================*/
const float OrientationAxis::axisLineWidth( void ) const
{
    return( m_axis_line_width );
}

/*===========================================================================*/
/**
 *  @brief  Returns the box color.
 *  @return box color
 */
/*===========================================================================*/
const kvs::RGBColor& OrientationAxis::boxColor( void ) const
{
    return( m_box_color );
}

/*===========================================================================*/
/**
 *  @brief  Returns the box line color.
 *  @return box line color
 */
/*===========================================================================*/
const kvs::RGBColor& OrientationAxis::boxLineColor( void ) const
{
    return( m_box_line_color );
}

/*===========================================================================*/
/**
 *  @brief  Returns the line width of the box.
 *  @return line width
 */
/*===========================================================================*/
const float OrientationAxis::boxLineWidth( void ) const
{
    return( m_box_line_width );
}

/*===========================================================================*/
/**
 *  @brief  Returns the axis type.
 *  @return Axis type
 */
/*===========================================================================*/
const OrientationAxis::AxisType OrientationAxis::axisType( void ) const
{
    return( m_axis_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns the box type.
 *  @return box type
 */
/*===========================================================================*/
const OrientationAxis::BoxType OrientationAxis::boxType( void ) const
{
    return( m_box_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns the projection type.
 *  @return projection type
 */
/*===========================================================================*/
const OrientationAxis::ProjectionType OrientationAxis::projectionType( void ) const
{
    return( m_projection_type );
}

/*===========================================================================*/
/**
 *  @brief  Sets a object for obtaining the rotation matrix.
 *  @param  object [in] pointer to the object
 */
/*===========================================================================*/
void OrientationAxis::setObject( const kvs::ObjectBase* object )
{
    m_object = object;
}

/*===========================================================================*/
/**
 *  @brief  Sets the window size.
 *  @param  size [in] window size
 */
/*===========================================================================*/
void OrientationAxis::setSize( const size_t size )
{
    m_width = size;
    m_height = size;
}

/*===========================================================================*/
/**
 *  @brief  Sets the X axis tag.
 *  @param  tag [in] X axis tag
 */
/*===========================================================================*/
void OrientationAxis::setXTag( const std::string& tag )
{
    m_x_tag = tag;
}

/*===========================================================================*/
/**
 *  @brief  Sets the Y axis tag.
 *  @param  tag [in] Y axis tag
 */
/*===========================================================================*/
void OrientationAxis::setYTag( const std::string& tag )
{
    m_y_tag = tag;
}

/*===========================================================================*/
/**
 *  @brief  Sets the Z axis tag.
 *  @param  tag [in] Z axis tag
 */
/*===========================================================================*/
void OrientationAxis::setZTag( const std::string& tag )
{
    m_z_tag = tag;
}

/*===========================================================================*/
/**
 *  @brief  Sets the X axis color.
 *  @param  color [in] X axis color
 */
/*===========================================================================*/
void OrientationAxis::setXAxisColor( const kvs::RGBColor& color )
{
    m_x_axis_color = color;
}

/*===========================================================================*/
/**
 *  @brief  Sets the Y axis color.
 *  @param  color [in] Y axis color
 */
/*===========================================================================*/
void OrientationAxis::setYAxisColor( const kvs::RGBColor& color )
{
    m_y_axis_color = color;
}

/*===========================================================================*/
/**
 *  @brief  Sets the Z axis color.
 *  @param  color [in] Z axis color
 */
/*===========================================================================*/
void OrientationAxis::setZAxisColor( const kvs::RGBColor& color )
{
    m_z_axis_color = color;
}

/*===========================================================================*/
/**
 *  @brief  Sets the line width of the axis.
 *  @param  width [in] line width
 */
/*===========================================================================*/
void OrientationAxis::setAxisLineWidth( const float width )
{
    m_axis_line_width = width;
}

/*===========================================================================*/
/**
 *  @brief  Sets the box color.
 *  @param  color [in] box color
 */
/*===========================================================================*/
void OrientationAxis::setBoxColor( const kvs::RGBColor& color )
{
    m_box_color = color;
}

/*===========================================================================*/
/**
 *  @brief  Sets the box line color.
 *  @param  color [in] box line color
 */
/*===========================================================================*/
void OrientationAxis::setBoxLineColor( const kvs::RGBColor& color )
{
    m_box_line_color = color;
}

/*===========================================================================*/
/**
 *  @brief  Sets the line width of the box.
 *  @param  width [in] line width
 */
/*===========================================================================*/
void OrientationAxis::setBoxLineWidth( const float width )
{
    m_box_line_width = width;
}

/*===========================================================================*/
/**
 *  @brief  Sets the axis type.
 *  @param  axis_type [in] axis type
 */
/*===========================================================================*/
void OrientationAxis::setAxisType( const OrientationAxis::AxisType axis_type )
{
    m_axis_type = axis_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets the box type.
 *  @param  box_type [in] box type
 */
/*===========================================================================*/
void OrientationAxis::setBoxType( const OrientationAxis::BoxType box_type )
{
    m_box_type = box_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets the projection type.
 *  @param  projection_type [in] projection type
 */
/*===========================================================================*/
void OrientationAxis::setProjectionType( const OrientationAxis::ProjectionType projection_type )
{
    m_projection_type = projection_type;
}

/*===========================================================================*/
/**
 *  @brief  Enables anti-aliasing.
 */
/*===========================================================================*/
void OrientationAxis::enableAntiAliasing( void )
{
    m_enable_anti_aliasing = true;
}

/*===========================================================================*/
/**
 *  @brief  Disables anti-aliasing.
 */
/*===========================================================================*/
void OrientationAxis::disableAntiAliasing( void )
{
    m_enable_anti_aliasing = false;
}

/*===========================================================================*/
/**
 *  @brief  Paint event.
 */
/*===========================================================================*/
void OrientationAxis::paintEvent( void )
{
    this->screenUpdated();

    if ( !BaseClass::isShown() ) return;

    GLint vp[4]; glGetIntegerv( GL_VIEWPORT, vp );

    glPushAttrib( GL_ALL_ATTRIB_BITS );

    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    glEnable( GL_DEPTH_TEST );

    glClearDepth( 1.0 );
    glClear( GL_DEPTH_BUFFER_BIT );

    // Anti-aliasing.
    if ( m_enable_anti_aliasing )
    {
        glEnable( GL_LINE_SMOOTH );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }

    // Set the projection parameters.
    glMatrixMode( GL_PROJECTION ); glLoadIdentity();
    {
        const float front = 1.0f;
        const float back = 2000.0f;
        if ( m_projection_type == kvs::Camera::Perspective )
        {
            // Perspective projection.
            const float field_of_view = 45.0f;
            const float aspect = 1.0f;
           gluPerspective( field_of_view, aspect, front, back );
        }
        else
        {
            // Orthogonal projection.
            const float left = -5.0f;
            const float bottom = -5.0f;
            const float right = 5.0f;
            const float top = 5.0f;
            glOrtho( left, right, bottom, top, front, back );
        }
    }

    // The origin is set to the top-left on the screen.
    const int x = m_x + m_margin;
    const int y = screen()->height() - m_y - m_height + m_margin;
    const int width = m_width - m_margin;
    const int height = m_height - m_margin;
    glViewport( x, y, width, height);
    glMatrixMode( GL_MODELVIEW ); glLoadIdentity();
    {
        // Viewing transformation.
        const kvs::Vector3f eye( 0.0f, 0.0f, 12.0f );
        const kvs::Vector3f center( 0.0f, 0.0f, 0.0f );
        const kvs::Vector3f up( 0.0f, 1.0f, 0.0f );
        gluLookAt( eye.x(), eye.y(), eye.z(),
                   center.x(), center.y(), center.z(),
                   up.x(), up.y(), up.z() );

        // Rotate the axis and the box using the object's rotation matrix.
        kvs::Xform xform = m_object->xform();
        const kvs::Vector3f trans = xform.translation();
        const kvs::Vector3f scale = xform.scaling();
        const float max_scale = kvs::Math::Max( scale.x(), scale.y(), scale.z() );
        xform = kvs::Xform::Translation( -trans ) * xform; // Remove translation.
        xform = kvs::Xform::Scaling( 1.0f / max_scale ) * xform; // Normalize by maximum scale.

        float mat[16];
        xform.toArray( mat );
        glMultMatrixf( mat );

        // Fixed length of the axis
        const float length = 4.0f;

        // Draw the box.
        switch ( m_box_type )
        {
        case OrientationAxis::WiredBox:
            this->draw_wired_box( length );
            break;
        case OrientationAxis::SolidBox:
            this->draw_solid_box( length );
            break;
        default:
            break;
        }

        // Draw the axis.
        switch ( m_axis_type )
        {
        case OrientationAxis::CorneredAxis:
            this->draw_cornered_axis( length );
            break;
        case OrientationAxis::CenteredAxis:
            this->draw_centered_axis( length );
            break;
        default:
            break;
        }
    }

    glViewport( vp[0], vp[1], vp[2], vp[3]);
    glPopAttrib();
}

/*===========================================================================*/
/**
 *  @brief  Resize event.
 *  @param  width [in] screen width
 *  @param  height [in] screen height
 */
/*===========================================================================*/
void OrientationAxis::resizeEvent( int width, int height )
{
    kvs::IgnoreUnusedVariable( width );
    kvs::IgnoreUnusedVariable( height );

    this->screenResized();
}

/*===========================================================================*/
/**
 *  @brief  Returns the initial screen width.
 *  @return screen width
 */
/*===========================================================================*/
int OrientationAxis::get_fitted_width( void )
{
    return( ::Default::AxisWindowSize );
}

/*===========================================================================*/
/**
 *  @brief  Returns the initial screen height.
 *  @return screen height
 */
/*===========================================================================*/
int OrientationAxis::get_fitted_height( void )
{
    return( ::Default::AxisWindowSize );
}

/*===========================================================================*/
/**
 *  @brief  Draw the centered axis.
 */
/*===========================================================================*/
void OrientationAxis::draw_centered_axis( const float length )
{
    const float x = 0.0f;
    const float y = 0.0f;
    const float z = 0.0f;
    const kvs::Vector3f v0( x, y, z );
    const kvs::Vector3f v1( x + length, y, z );
    //const kvs::Vector3f v2( x + length, y, z + length );
    const kvs::Vector3f v3( x, y, z + length );
    const kvs::Vector3f v4( x, y + length, z );
    //const kvs::Vector3f v5( x + length, y + length, z );
    //const kvs::Vector3f v6( x + length, y + length, z + length );
    //const kvs::Vector3f v7( x, y + length, z + length );

    glLineWidth( m_axis_line_width );

    const float padding = static_cast<float>( length ) / 4.0f;

    // X-axis.
    glColor3ub( m_x_axis_color.r(), m_x_axis_color.g(), m_x_axis_color.b() );
    glBegin( GL_LINES );
    glVertex3f( v0.x(), v0.y(), v0.z() );
    glVertex3f( v1.x(), v1.y(), v1.z() );
    glEnd();

    glRasterPos3d( v1.x(), v1.y() - padding, v1.z() - padding );
    char* x_char = const_cast<char*>( m_x_tag.c_str() );
    for( char* p = x_char; *p; p++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *p );
    }

    // Y-axis.
    glColor3ub( m_y_axis_color.r(), m_y_axis_color.g(), m_y_axis_color.b() );
    glBegin( GL_LINES );
    glVertex3f( v0.x(), v0.y(), v0.z() );
    glVertex3f( v4.x(), v4.y(), v4.z() );
    glEnd();

    glRasterPos3d( v4.x() - padding, v4.y(), v4.z() - padding );
    char* y_char = const_cast<char*>( m_y_tag.c_str() );
    for( char* p = y_char; *p; p++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *p );
    }

    // Z-axis.
    glColor3ub( m_z_axis_color.r(), m_z_axis_color.g(), m_z_axis_color.b() );
    glBegin( GL_LINES );
    glVertex3f( v0.x(), v0.y(), v0.z() );
    glVertex3f( v3.x(), v3.y(), v3.z() );
    glEnd();

    glRasterPos3d( v3.x() - padding, v3.y() - padding, v3.z() );
    char* z_char = const_cast<char*>( m_z_tag.c_str() );
    for( char* p = z_char; *p; p++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *p );
    }
}

/*===========================================================================*/
/**
 *  @brief  Draw the boundary axis.
 */
/*===========================================================================*/
void OrientationAxis::draw_cornered_axis( const float length )
{
    const float x = -length/2.0f;
    const float y = -length/2.0f;
    const float z = -length/2.0f;
    const kvs::Vector3f v0( x, y, z );
    const kvs::Vector3f v1( x + length, y, z );
    //const kvs::Vector3f v2( x + length, y, z + length );
    const kvs::Vector3f v3( x, y, z + length );
    const kvs::Vector3f v4( x, y + length, z );
    //const kvs::Vector3f v5( x + length, y + length, z );
    //const kvs::Vector3f v6( x + length, y + length, z + length );
    //const kvs::Vector3f v7( x, y + length, z + length );

    glLineWidth( m_axis_line_width );

    const float padding = static_cast<float>( length ) / 6.0f;

    // X-axis.
    glColor3ub( m_x_axis_color.r(), m_x_axis_color.g(), m_x_axis_color.b() );
    glBegin( GL_LINES );
    glVertex3f( v0.x(), v0.y(), v0.z() );
    glVertex3f( v1.x(), v1.y(), v1.z() );
    glEnd();

    glRasterPos3d( v1.x(), v1.y() - padding, v1.z() - padding );
    char* x_char = const_cast<char*>( m_x_tag.c_str() );
    for( char* p = x_char; *p; p++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *p );
    }

    // Y-axis.
    glColor3ub( m_y_axis_color.r(), m_y_axis_color.g(), m_y_axis_color.b() );
    glBegin( GL_LINES );
    glVertex3f( v0.x(), v0.y(), v0.z() );
    glVertex3f( v4.x(), v4.y(), v4.z() );
    glEnd();

    glRasterPos3d( v4.x() - padding, v4.y(), v4.z() - padding );
    char* y_char = const_cast<char*>( m_y_tag.c_str() );
    for( char* p = y_char; *p; p++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *p );
    }

    // Z-axis.
    glColor3ub( m_z_axis_color.r(), m_z_axis_color.g(), m_z_axis_color.b() );
    glBegin( GL_LINES );
    glVertex3f( v0.x(), v0.y(), v0.z() );
    glVertex3f( v3.x(), v3.y(), v3.z() );
    glEnd();

    glRasterPos3d( v3.x() - padding, v3.y() - padding, v3.z() );
    char* z_char = const_cast<char*>( m_z_tag.c_str() );
    for( char* p = z_char; *p; p++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *p );
    }
}

/*===========================================================================*/
/**
 *  @brief  Draws the wired box.
 *  @param  length [in] length of the box's edge
 */
/*===========================================================================*/
void OrientationAxis::draw_wired_box( const float length )
{
    const float x = -length/2.0f;
    const float y = -length/2.0f;
    const float z = -length/2.0f;
    const kvs::Vector3f v0( x, y, z );
    const kvs::Vector3f v1( x + length, y, z );
    const kvs::Vector3f v2( x + length, y, z + length );
    const kvs::Vector3f v3( x, y, z + length );
    const kvs::Vector3f v4( x, y + length, z );
    const kvs::Vector3f v5( x + length, y + length, z );
    const kvs::Vector3f v6( x + length, y + length, z + length );
    const kvs::Vector3f v7( x, y + length, z + length );

    glLineWidth( m_box_line_width );
    glColor3ub( m_box_line_color.r(), m_box_line_color.g(), m_box_line_color.b() );
    glBegin( GL_LINES );
    {
        if ( m_axis_type != OrientationAxis::CorneredAxis )
        {
            // X axis.
            glVertex3f( v0.x(), v0.y(), v0.z() );
            glVertex3f( v1.x(), v1.y(), v1.z() );
        }
        glVertex3f( v1.x(), v1.y(), v1.z() );
        glVertex3f( v2.x(), v2.y(), v2.z() );
        glVertex3f( v2.x(), v2.y(), v2.z() );
        glVertex3f( v3.x(), v3.y(), v3.z() );
        if ( m_axis_type != OrientationAxis::CorneredAxis )
        {
            // Z axis.
            glVertex3f( v3.x(), v3.y(), v3.z() );
            glVertex3f( v0.x(), v0.y(), v0.z() );
        }

        glVertex3f( v4.x(), v4.y(), v4.z() );
        glVertex3f( v5.x(), v5.y(), v5.z() );
        glVertex3f( v5.x(), v5.y(), v5.z() );
        glVertex3f( v6.x(), v6.y(), v6.z() );
        glVertex3f( v6.x(), v6.y(), v6.z() );
        glVertex3f( v7.x(), v7.y(), v7.z() );
        glVertex3f( v7.x(), v7.y(), v7.z() );
        glVertex3f( v4.x(), v4.y(), v4.z() );

        if ( m_axis_type != OrientationAxis::CorneredAxis )
        {
            // Y axis.
            glVertex3f( v0.x(), v0.y(), v0.z() );
            glVertex3f( v4.x(), v4.y(), v4.z() );
        }
        glVertex3f( v1.x(), v1.y(), v1.z() );
        glVertex3f( v5.x(), v5.y(), v5.z() );

        glVertex3f( v2.x(), v2.y(), v2.z() );
        glVertex3f( v6.x(), v6.y(), v6.z() );

        glVertex3f( v3.x(), v3.y(), v3.z() );
        glVertex3f( v7.x(), v7.y(), v7.z() );
    }
    glEnd();
}

/*===========================================================================*/
/**
 *  @brief  Draws the solid box.
 *  @param  length [in] length of the box's edge
 */
/*===========================================================================*/
void OrientationAxis::draw_solid_box( const float length )
{
    const float x = -length/2.0f;
    const float y = -length/2.0f;
    const float z = -length/2.0f;
    const kvs::Vector3f v0( x, y, z );
    const kvs::Vector3f v1( x + length, y, z );
    const kvs::Vector3f v2( x + length, y, z + length );
    const kvs::Vector3f v3( x, y, z + length );
    const kvs::Vector3f v4( x, y + length, z );
    const kvs::Vector3f v5( x + length, y + length, z );
    const kvs::Vector3f v6( x + length, y + length, z + length );
    const kvs::Vector3f v7( x, y + length, z + length );

    glPolygonOffset( 1, 1 );
    glEnable( GL_POLYGON_OFFSET_FILL );

    glColor3ub( m_box_color.r(), m_box_color.g(), m_box_color.b() );
    glBegin( GL_QUADS );
    {
        // bottom
        glVertex3f( v0.x(), v0.y(), v0.z() );
        glVertex3f( v1.x(), v1.y(), v1.z() );
        glVertex3f( v2.x(), v2.y(), v2.z() );
        glVertex3f( v3.x(), v3.y(), v3.z() );
        // top
        glVertex3f( v7.x(), v7.y(), v7.z() );
        glVertex3f( v6.x(), v6.y(), v6.z() );
        glVertex3f( v5.x(), v5.y(), v5.z() );
        glVertex3f( v4.x(), v4.y(), v4.z() );
        // back
        glVertex3f( v0.x(), v0.y(), v0.z() );
        glVertex3f( v4.x(), v4.y(), v4.z() );
        glVertex3f( v5.x(), v5.y(), v5.z() );
        glVertex3f( v1.x(), v1.y(), v1.z() );
        // right
        glVertex3f( v1.x(), v1.y(), v1.z() );
        glVertex3f( v5.x(), v5.y(), v5.z() );
        glVertex3f( v6.x(), v6.y(), v6.z() );
        glVertex3f( v2.x(), v2.y(), v2.z() );
        // front
        glVertex3f( v2.x(), v2.y(), v2.z() );
        glVertex3f( v6.x(), v6.y(), v6.z() );
        glVertex3f( v7.x(), v7.y(), v7.z() );
        glVertex3f( v3.x(), v3.y(), v3.z() );
        // left
        glVertex3f( v0.x(), v0.y(), v0.z() );
        glVertex3f( v3.x(), v3.y(), v3.z() );
        glVertex3f( v7.x(), v7.y(), v7.z() );
        glVertex3f( v4.x(), v4.y(), v4.z() );
    }
    glEnd();

    glLineWidth( m_box_line_width );
    glColor3ub( m_box_line_color.r(), m_box_line_color.g(), m_box_line_color.b() );
    glBegin( GL_LINES );
    {
        if ( m_axis_type != OrientationAxis::CorneredAxis )
        {
            // X axis.
            glVertex3f( v0.x(), v0.y(), v0.z() );
            glVertex3f( v1.x(), v1.y(), v1.z() );
        }
        glVertex3f( v1.x(), v1.y(), v1.z() );
        glVertex3f( v2.x(), v2.y(), v2.z() );
        glVertex3f( v2.x(), v2.y(), v2.z() );
        glVertex3f( v3.x(), v3.y(), v3.z() );
        if ( m_axis_type != OrientationAxis::CorneredAxis )
        {
            // Z axis.
            glVertex3f( v3.x(), v3.y(), v3.z() );
            glVertex3f( v0.x(), v0.y(), v0.z() );
        }

        glVertex3f( v4.x(), v4.y(), v4.z() );
        glVertex3f( v5.x(), v5.y(), v5.z() );
        glVertex3f( v5.x(), v5.y(), v5.z() );
        glVertex3f( v6.x(), v6.y(), v6.z() );
        glVertex3f( v6.x(), v6.y(), v6.z() );
        glVertex3f( v7.x(), v7.y(), v7.z() );
        glVertex3f( v7.x(), v7.y(), v7.z() );
        glVertex3f( v4.x(), v4.y(), v4.z() );

        if ( m_axis_type != OrientationAxis::CorneredAxis )
        {
            // Y axis.
            glVertex3f( v0.x(), v0.y(), v0.z() );
            glVertex3f( v4.x(), v4.y(), v4.z() );
        }
        glVertex3f( v1.x(), v1.y(), v1.z() );
        glVertex3f( v5.x(), v5.y(), v5.z() );

        glVertex3f( v2.x(), v2.y(), v2.z() );
        glVertex3f( v6.x(), v6.y(), v6.z() );

        glVertex3f( v3.x(), v3.y(), v3.z() );
        glVertex3f( v7.x(), v7.y(), v7.z() );
    }
    glEnd();

    glDisable( GL_POLYGON_OFFSET_FILL );
}

} // end of namesapce glut

} // end of namespace kvs
