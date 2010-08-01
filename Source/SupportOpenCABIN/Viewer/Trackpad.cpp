/*****************************************************************************/
/**
 *  @file   Trackpad.cpp
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
#include "Trackpad.h"
#include <kvs/Math>
#include <kvs/MouseMoveEventListener>
#include <kvs/opencabin/Application>
#include <kvs/opencabin/Configuration>
#include <kvs/glut/GLUT>


namespace kvs
{

namespace opencabin
{

Trackpad::Trackpad( kvs::opencabin::Application* application )
{
    if ( application ) application->attach_trackpad( this );

    if ( kvs::opencabin::Application::IsMaster() )
    {
        const kvs::Vector2i resolution = kvs::opencabin::Configuration::KVSApplication::DisplayResolution();
        const int min = kvs::Math::Min( resolution.x(), resolution.y() );
        const int base = 256;
        const int width = base * resolution.x() / min;
        const int height = base * resolution.y() / min;
        const std::string title( "Trackpad" );
        const kvs::RGBColor color( 200, 200, 200 );

        BaseClass::setTitle( title );
        BaseClass::setSize( width, height );
        BaseClass::background()->setColor( color );
    }
}

int Trackpad::show( void )
{
    if ( kvs::opencabin::Application::IsMaster() )
    {
        return( BaseClass::show() );
    }

    return( 0 );
}

/*==========================================================================*/
/**
 *  @brief  Updates the xform of the control target.
 */
/*==========================================================================*/
void Trackpad::updateXform( void )
{
    if ( kvs::opencabin::Application::IsMaster() )
    {
        float* scaling = kvs::opencabin::Application::GetTrackpadScaling();
        scaling[0] = m_mouse->scaling()[0];
        scaling[1] = m_mouse->scaling()[1];
        scaling[2] = m_mouse->scaling()[2];

        float* translation = kvs::opencabin::Application::GetTrackpadTranslation();
        translation[0] = m_mouse->translation()[0];
        translation[1] = m_mouse->translation()[1];
        translation[2] = m_mouse->translation()[2];

        float* rotation = kvs::opencabin::Application::GetTrackpadRotation();
        rotation[0] = m_mouse->rotation()[0][0];
        rotation[1] = m_mouse->rotation()[0][1];
        rotation[2] = m_mouse->rotation()[0][2];
        rotation[3] = m_mouse->rotation()[1][0];
        rotation[4] = m_mouse->rotation()[1][1];
        rotation[5] = m_mouse->rotation()[1][2];
        rotation[6] = m_mouse->rotation()[2][0];
        rotation[7] = m_mouse->rotation()[2][1];
        rotation[8] = m_mouse->rotation()[2][2];

        BaseClass::updateXform();
    }
}

} // end of namespace opencabin

} // end of namespace kvs
