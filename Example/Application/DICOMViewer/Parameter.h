/*****************************************************************************/
/**
 *  @file   Parameter.h
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
#ifndef __PARAPMETER_H__
#define __PARAPMETER_H__

#include <kvs/DicomList>
#include <kvs/Vector2>

/*===========================================================================*/
/**
 *  @brief  Global parameter set.
 */
/*===========================================================================*/
struct Parameter
{
    kvs::DicomList dicom_list; ///< DICOM list
    int width; ///< image width
    int height; ///< image height
    int index; ///< current data index
    int window_level; ///< window level
    int window_width; ///< window width
    int value; ///< pointed value
    bool enable_show_information; ///< enable showing information
    kvs::Vector2i mouse; ///< windowing mouse

    ///< Sets default values.
    Parameter( void ):
        width( 0 ),
        height( 0 ),
        index( 0 ),
        window_level( 0 ),
        window_width( 0 ),
        value( 0 ),
        enable_show_information( true ){}
};

#endif // __PARAPMETER_H__
