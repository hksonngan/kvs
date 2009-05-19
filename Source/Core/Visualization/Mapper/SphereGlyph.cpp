/*****************************************************************************/
/**
 *  @file   SphereGlyph.cpp
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
#include "SphereGlyph.h"
#include <kvs/OpenGL>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new SphereGlyph class.
 */
/*===========================================================================*/
SphereGlyph::SphereGlyph( void ):
    kvs::GlyphBase(),
    m_sphere(NULL),
    m_nslices(10),
    m_nstacks(10)
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new SphereGlyph class.
 *  @param  volume [in] pointer to the volume object
 */
/*===========================================================================*/
SphereGlyph::SphereGlyph( const kvs::VolumeObjectBase* volume ):
    kvs::GlyphBase(),
    m_sphere(NULL),
    m_nslices(10),
    m_nstacks(10)
{
    this->exec( volume );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new SphereGlyph class.
 *  @param  volume [in] pointer to the volume object
 *  @param  transfer_function [in] transfer function
 */
/*===========================================================================*/
SphereGlyph::SphereGlyph(
    const kvs::VolumeObjectBase* volume,
    const kvs::TransferFunction& transfer_function ):
    kvs::GlyphBase(),
    m_sphere(NULL),
    m_nslices(10),
    m_nstacks(10)
{
    BaseClass::setTransferFunction( transfer_function );
    this->exec( volume );
}

/*===========================================================================*/
/**
 *  @brief  Destructs the Sphere glyph class.
 */
/*===========================================================================*/
SphereGlyph::~SphereGlyph( void )
{
    gluDeleteQuadric( m_sphere );
}

/*===========================================================================*/
/**
 *  @brief  Sets a number of slices (subdivisions) of the sphere.
 *  @param  nslices [in] number of slices.
 */
/*===========================================================================*/
void SphereGlyph::setNSlices( const size_t nslices )
{
    m_nslices = nslices;
}

/*===========================================================================*/
/**
 *  @brief  Sets a number of stacks (subdivisions) of the sphere.
 *  @param  nstacks [in] number of stacks.
 */
/*===========================================================================*/
void SphereGlyph::setNStacks( const size_t nstacks )
{
    m_nstacks = nstacks;
}

/*===========================================================================*/
/**
 *  @brief  Creates a sphere glyph.
 *  @param  object [in] pointer to the input object (volume object)
 *  @return pointer to the created glyph object
 */
/*===========================================================================*/
kvs::ObjectBase* SphereGlyph::exec( const kvs::ObjectBase* object )
{
    const kvs::VolumeObjectBase* volume = kvs::VolumeObjectBase::DownCast( object );
    BaseClass::attach_volume( volume );
    BaseClass::set_min_max_coords( volume, this );

    BaseClass::calculate_coords( volume );

    const std::type_info& type = volume->values().typeInfo()->type();
    if ( type == typeid( kvs::Int8 ) )
    {
        BaseClass::calculate_sizes<kvs::Int8>( volume );
        BaseClass::calculate_colors<kvs::Int8>( volume );
        BaseClass::calculate_opacities<kvs::Int8>( volume );
    }
    else if ( type == typeid( kvs::Int16 ) )
    {
        BaseClass::calculate_sizes<kvs::Int16>( volume );
        BaseClass::calculate_colors<kvs::Int16>( volume );
        BaseClass::calculate_opacities<kvs::Int16>( volume );
    }
    else if ( type == typeid( kvs::Int32 ) )
    {
        BaseClass::calculate_sizes<kvs::Int32>( volume );
        BaseClass::calculate_colors<kvs::Int32>( volume );
        BaseClass::calculate_opacities<kvs::Int32>( volume );
    }
    else if ( type == typeid( kvs::Int64 ) )
    {
        BaseClass::calculate_sizes<kvs::Int64>( volume );
        BaseClass::calculate_colors<kvs::Int64>( volume );
        BaseClass::calculate_opacities<kvs::Int64>( volume );
    }
    else if ( type == typeid( kvs::UInt8  ) )
    {
        BaseClass::calculate_sizes<kvs::UInt8>( volume );
        BaseClass::calculate_colors<kvs::UInt8>( volume );
        BaseClass::calculate_opacities<kvs::UInt8>( volume );
    }
    else if ( type == typeid( kvs::UInt16 ) )
    {
        BaseClass::calculate_sizes<kvs::UInt16>( volume );
        BaseClass::calculate_colors<kvs::UInt16>( volume );
        BaseClass::calculate_opacities<kvs::UInt16>( volume );
    }
    else if ( type == typeid( kvs::UInt32 ) )
    {
        BaseClass::calculate_sizes<kvs::UInt32>( volume );
        BaseClass::calculate_colors<kvs::UInt32>( volume );
        BaseClass::calculate_opacities<kvs::UInt32>( volume );
    }
    else if ( type == typeid( kvs::UInt64 ) )
    {
        BaseClass::calculate_sizes<kvs::UInt64>( volume );
        BaseClass::calculate_colors<kvs::UInt64>( volume );
        BaseClass::calculate_opacities<kvs::UInt64>( volume );
    }
    else if ( type == typeid( kvs::Real32 ) )
    {
        BaseClass::calculate_sizes<kvs::Real32>( volume );
        BaseClass::calculate_colors<kvs::Real32>( volume );
        BaseClass::calculate_opacities<kvs::Real32>( volume );
    }
    else if ( type == typeid( kvs::Real64 ) )
    {
        BaseClass::calculate_sizes<kvs::Real64>( volume );
        BaseClass::calculate_colors<kvs::Real64>( volume );
        BaseClass::calculate_opacities<kvs::Real64>( volume );
    }

    return( this );
}

/*===========================================================================*/
/**
 *  @brief  Draw the sphere glyph.
 */
/*===========================================================================*/
void SphereGlyph::draw( void )
{
    if ( !m_sphere )
    {
        m_sphere = gluNewQuadric();
        gluQuadricDrawStyle( m_sphere, GLU_FILL );
        gluQuadricNormals( m_sphere, GLU_SMOOTH );
    }

    this->initialize();
    BaseClass::applyMaterial();

    const size_t npoints = BaseClass::m_coords.size() / 3;

    if ( BaseClass::m_directions.size() == 0 )
    {
        for ( size_t i = 0, index = 0; i < npoints; i++, index += 3 )
        {
            const kvs::Vector3f position( BaseClass::m_coords.pointer() + index );
            const kvs::Real32 size = BaseClass::m_sizes[i];
            const kvs::RGBColor color( BaseClass::m_colors.pointer() + index );
            const kvs::UInt8 opacity = BaseClass::m_opacities[i];
            glPushMatrix();
            {
                BaseClass::transform( position, size );
                this->draw_element( color, opacity );
            }
            glPopMatrix();
        }
    }
    else
    {
        for( size_t i = 0, index = 0; i < npoints; i++, index += 3 )
        {
            const kvs::Vector3f position( BaseClass::m_coords.pointer() + index );
            const kvs::Vector3f direction( BaseClass::m_directions.pointer() + index );
            const kvs::Real32 size = BaseClass::m_sizes[i];
            const kvs::RGBColor color( BaseClass::m_colors.pointer() + index );
            const kvs::UInt8 opacity = BaseClass::m_opacities[i];
            glPushMatrix();
            {
                BaseClass::transform( position, direction, size );
                this->draw_element( color, opacity );
            }
            glPopMatrix();
        }
    }
}

/*===========================================================================*/
/**
 *  @brief  Draw the glyph element.
 *  @param  color [in] color value
 *  @param  opacity [in] opacity value
 */
/*===========================================================================*/
void SphereGlyph::draw_element( const kvs::RGBColor& color, const kvs::UInt8 opacity )
{
    glColor4ub( color.r(), color.g(), color.b(), opacity );

    const GLdouble radius = 0.5;
    gluSphere( m_sphere, radius, static_cast<GLint>(m_nslices), static_cast<GLint>(m_nstacks) );
}

/*===========================================================================*/
/**
 *  @brief  Initialize the modelview matrix.
 */
/*===========================================================================*/
void SphereGlyph::initialize( void )
{
    glDisable( GL_LINE_SMOOTH );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glShadeModel( GL_SMOOTH );

    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glEnable( GL_COLOR_MATERIAL );
}

} // end of namespace kvs
