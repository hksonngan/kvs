/*****************************************************************************/
/**
 *  @file   HydrogenVolumeData.h
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
#ifndef KVS__HYDROGEN_VOLUME_DATA_H_INCLUDE
#define KVS__HYDROGEN_VOLUME_DATA_H_INCLUDE

#include <kvs/StructuredVolumeObject>
#include <kvs/Vector3>
#include <kvs/ClassName>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Hydrogen data generator class.
 */
/*===========================================================================*/
class HydrogenVolumeData : public kvs::StructuredVolumeObject
{
    kvsClassName( HydrogenVolumeData );

public:

    typedef kvs::StructuredVolumeObject SuperClass;

public:

    HydrogenVolumeData( void );

    HydrogenVolumeData( const kvs::Vector3ui resolution );

    virtual ~HydrogenVolumeData( void );

public:

    SuperClass* exec( void );
};

} // end of namespace kvs

#endif // KVS__HYDROGEN_VOLUME_DATA_H_INCLUDE
