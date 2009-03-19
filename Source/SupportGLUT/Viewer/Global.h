/****************************************************************************/
/**
 *  @file Global.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_SUPPORT_GLUT_GLOBAL_H_INCLUDE
#define KVS_SUPPORT_GLUT_GLOBAL_H_INCLUDE

#include <kvs/glut/GlobalBase>
#include <kvs/ObjectManager>
#include <kvs/RendererManager>
#include <kvs/IDManager>
#include <kvs/VisualizationPipeline>


namespace kvs
{

namespace glut
{

/*==========================================================================*/
/**
 *  Global class.
 */
/*==========================================================================*/
class Global : public kvs::glut::GlobalBase
{
public:

    Global( int count, char** values );

    virtual ~Global( void );

public:

    void insert( const kvs::VisualizationPipeline& pipeline );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS_SUPPORT_GLUT_GLOBAL_H_INCLUDE
