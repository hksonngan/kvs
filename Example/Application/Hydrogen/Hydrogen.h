/*****************************************************************************/
/**
 *  @file   Hydrogen.h
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
/*****************************************************************************/
#ifndef __HYDROGEN_H__
#define __HYDROGEN_H__

#include <kvs/StructuredVolumeObject>
#include <kvs/Vector3>


/*===========================================================================*/
/**
 *  @brief  Hydrogen volume generator class.
 */
/*===========================================================================*/
class Hydrogen : public kvs::StructuredVolumeObject
{
    typedef kvs::StructuredVolumeObject SuperClass;

public:

    Hydrogen( const kvs::Vector3ui& resolution );

    virtual ~Hydrogen( void );

private:

    Hydrogen( void );
};

#endif // __HYDROGEN_H__
