/*****************************************************************************/
/**
 *  @file   DiamondGlyph.h
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
#ifndef KVS__DIAMOND_GLYPH_H_INCLUDE
#define KVS__DIAMOND_GLYPH_H_INCLUDE

#include "GlyphBase.h"
#include <kvs/MapperBase>
#include <kvs/ClassName>
#include <kvs/Module>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Diamond glyph class.
 */
/*===========================================================================*/
class DiamondGlyph : public kvs::GlyphBase
{
    // Class name.
    kvsClassName( DiamondGlyph );

    // Module information.
    kvsModuleCategory( Mapper );
    kvsModuleBaseClass( kvs::GlyphBase );

public:

    DiamondGlyph( void );

    DiamondGlyph(
        const kvs::VolumeObjectBase* volume );

    DiamondGlyph(
        const kvs::VolumeObjectBase* volume,
        const kvs::TransferFunction& transfer_function );

    virtual ~DiamondGlyph( void );

/*
public:

    const ObjectType objectType( void ) const
    {
        return( Geometry );
    }
*/
public:

    BaseClass::SuperClass* exec( const kvs::ObjectBase* object );

    void draw( void );

protected:

    void draw_element( const kvs::RGBColor& color, const kvs::UInt8 opacity );

protected:

    void initialize( void );
};

} // end of namespace kvs

#endif // KVS__DIAMOND_GLYPH_H_INCLUDE
