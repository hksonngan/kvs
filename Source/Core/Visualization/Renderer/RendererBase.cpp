/****************************************************************************/
/**
 *  @file   RendererBase.cpp
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
    m_enable_shading( true )
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
