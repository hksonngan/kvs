/****************************************************************************/
/**
 *  @file RendererBase.cpp
 *  @author Naohisa Sakamoto
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
#include "RendererBase.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  @brief  Constructs a new RendererBase class.
 */
/*==========================================================================*/
RendererBase::RendererBase():
    m_name("unknown"),
    m_shading_flag( true )
{
}

/*==========================================================================*/
/**
 *  @brief  Destruct the RendererBase class.
 */
/*==========================================================================*/
RendererBase::~RendererBase()
{
}

/*===========================================================================*/
/**
 *  @brief  Sets a renderer name.
 *  @param  name [in] renderer name
 */
/*===========================================================================*/
void RendererBase::setName( const std::string& name )
{
    m_name = name;
}

/*===========================================================================*/
/**
 *  @brief  Returns renderer name.
 *  @return renderer name
 */
/*===========================================================================*/
const std::string& RendererBase::name() const
{
    return m_name;
}

/*==========================================================================*/
/**
 *  @brief  Returns the rendering timer.
 *  @return rendering timer
 */
/*==========================================================================*/
const kvs::Timer& RendererBase::timer() const
{
    return m_timer;
}

/*==========================================================================*/
/**
 *  @brief  Tests whether the shading is enable or disable.
 *  @return true, if the shading is enable.
 */
/*==========================================================================*/
bool RendererBase::isShading() const
{
    return m_shading_flag;
}

/*==========================================================================*/
/**
 *  @brief  Enable to shading.
 */
/*==========================================================================*/
void RendererBase::enableShading() const
{
    m_shading_flag = true;
}

/*==========================================================================*/
/**
 *  @brief  Disable to shading.
 */
/*==========================================================================*/
void RendererBase::disableShading() const
{
    m_shading_flag = false;
}

/*===========================================================================*/
/**
 *  @brief  Starts the rendering timer.
 */
/*===========================================================================*/
void RendererBase::startTimer()
{
    m_timer.start();
}

/*===========================================================================*/
/**
 *  @brief  Stops the rendering timer.
 */
/*===========================================================================*/
void RendererBase::stopTimer()
{
    m_timer.stop();
}

} // end of namespace kvs
