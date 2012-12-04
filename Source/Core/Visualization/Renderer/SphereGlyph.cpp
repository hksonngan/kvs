/*****************************************************************************/
/**
 *  @file   SphereGlyph.cpp
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
#include "SphereGlyph.h"
#include <kvs/OpenGL>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new SphereGlyph class.
 */
/*===========================================================================*/
SphereGlyph::SphereGlyph():
    kvs::GlyphBase(),
    m_sphere( NULL ),
    m_nslices( 10 ),
    m_nstacks( 10 )
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new SphereGlyph class.
 *  @param  volume [in] pointer to the volume object
 */
/*===========================================================================*/
SphereGlyph::SphereGlyph( const kvs::PointObject* point ):
    kvs::GlyphBase(),
    m_sphere( NULL ),
    m_nslices( 10 ),
    m_nstacks( 10 )
{
    this->attach_point( point );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new SphereGlyph class.
 *  @param  volume [in] pointer to the volume object
 */
/*===========================================================================*/
SphereGlyph::SphereGlyph( const kvs::VolumeObjectBase* volume ):
    kvs::GlyphBase(),
    m_sphere( NULL ),
    m_nslices( 10 ),
    m_nstacks( 10 )
{
    this->attach_volume( volume );
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
    m_sphere( NULL ),
    m_nslices( 10 ),
    m_nstacks( 10 )
{
    BaseClass::setTransferFunction( transfer_function );
    this->attach_volume( volume );
}

/*===========================================================================*/
/**
 *  @brief  Destructs the Sphere glyph class.
 */
/*===========================================================================*/
SphereGlyph::~SphereGlyph()
{
    gluDeleteQuadric( m_sphere );
}

/*===========================================================================*/
/**
 *  @brief  Sets a number of slices (subdivisions) of the sphere.
 *  @param  nslices [in] number of slices.
 */
/*===========================================================================*/
void SphereGlyph::setNumberOfSlices( const size_t nslices )
{
    m_nslices = nslices;
}

/*===========================================================================*/
/**
 *  @brief  Sets a number of stacks (subdivisions) of the sphere.
 *  @param  nstacks [in] number of stacks.
 */
/*===========================================================================*/
void SphereGlyph::setNumberOfStacks( const size_t nstacks )
{
    m_nstacks = nstacks;
}

/*===========================================================================*/
/**
 *  @brief  Executes rendering process.
 *  @param  object [in] pointer to the volume object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void SphereGlyph::exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
    kvs::IgnoreUnusedVariable( light );
    kvs::IgnoreUnusedVariable( camera );

    if ( object->objectType() == kvs::ObjectBase::Geometry )
    {
        const kvs::GeometryObjectBase* geometry = kvs::GeometryObjectBase::DownCast( object );
        if ( geometry->geometryType() == kvs::GeometryObjectBase::Point )
        {
            const kvs::PointObject* point = kvs::PointObject::DownCast( geometry );
            if ( !point ) { kvsMessageError("Input object is not point dat."); return; }
            if ( m_point != point ) { this->attach_point( point ); }
        }
    }
    else if ( object->objectType() == kvs::ObjectBase::Volume )
    {
        const kvs::VolumeObjectBase* volume = kvs::VolumeObjectBase::DownCast( object );
        if ( !volume ) { kvsMessageError("Input object is not volume dat."); return; }
        if ( m_volume != volume ) { this->attach_volume( volume ); }
    }

    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    BaseClass::initialize();

    glEnable( GL_DEPTH_TEST );
    {
        BaseClass::timer().start();
        this->draw();
        BaseClass::timer().stop();
    }
    glDisable( GL_DEPTH_TEST );

    glPopAttrib();
}

/*===========================================================================*/
/**
 *  @brief  Draw the sphere glyph.
 */
/*===========================================================================*/
void SphereGlyph::draw()
{
    this->initialize();

    if ( !m_sphere )
    {
        m_sphere = gluNewQuadric();
        gluQuadricDrawStyle( m_sphere, GLU_FILL );
        gluQuadricNormals( m_sphere, GLU_SMOOTH );
    }

    const size_t npoints = BaseClass::coords().size() / 3;
    if ( BaseClass::directions().size() == 0 )
    {
        for ( size_t i = 0, index = 0; i < npoints; i++, index += 3 )
        {
            const kvs::Vector3f position( BaseClass::coords().data() + index );
            const kvs::Real32 size = BaseClass::sizes()[i];
            const kvs::RGBColor color( BaseClass::colors().data() + index );
            const kvs::UInt8 opacity = BaseClass::opacities()[i];
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
            const kvs::Vector3f position( BaseClass::coords().data() + index );
            const kvs::Vector3f direction( BaseClass::directions().data() + index );
            const kvs::Real32 size = BaseClass::sizes()[i];
            const kvs::RGBColor color( BaseClass::colors().data() + index );
            const kvs::UInt8 opacity = BaseClass::opacities()[i];
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
 *  @brief  Attaches a point object.
 *  @param  point [in] pointer to the point object
 */
/*===========================================================================*/
void SphereGlyph::attach_point( const kvs::PointObject* point )
{
    m_point = point;

    const size_t nvertices = point->numberOfVertices();

    BaseClass::setCoords( point->coords() );

    if ( BaseClass::directionMode() == BaseClass::DirectionByNormal )
    {
        if ( point->numberOfNormals() != 0 )
        {
            BaseClass::setDirections( point->normals() );
        }
    }

    if ( point->numberOfSizes() == 1 )
    {
        const kvs::Real32 size = point->size();
        kvs::ValueArray<kvs::Real32> sizes( nvertices );
        for ( size_t i = 0; i < nvertices; i++ ) sizes[i] = size;
        BaseClass::setSizes( sizes );
    }
    else
    {
        BaseClass::setSizes( point->sizes() );
    }

    if ( point->numberOfColors() == 1 )
    {
        const kvs::RGBColor color = point->color();
        kvs::ValueArray<kvs::UInt8> colors( nvertices * 3 );
        for ( size_t i = 0, j = 0; i < nvertices; i++, j += 3 )
        {
            colors[j]   = color.r();
            colors[j+1] = color.r();
            colors[j+2] = color.r();
        }
        BaseClass::setColors( colors );
    }
    else
    {
        BaseClass::setColors( point->colors() );
    }

    const kvs::UInt8 opacity = static_cast<kvs::UInt8>( 255 );
    kvs::ValueArray<kvs::UInt8> opacities( nvertices );
    for ( size_t i = 0; i < nvertices; i++ ) opacities[i] = opacity;
    BaseClass::setOpacities( opacities );
}

/*===========================================================================*/
/**
 *  @brief  Attaches a volume object.
 *  @param  volume [in] pointer to the volume object
 *  @return glyph object
 */
/*===========================================================================*/
void SphereGlyph::attach_volume( const kvs::VolumeObjectBase* volume )
{
    m_volume = volume;

    BaseClass::calculateCoords( volume );

    const std::type_info& type = volume->values().typeInfo()->type();
    if ( type == typeid( kvs::Int8 ) )
    {
        BaseClass::calculateSizes<kvs::Int8>( volume );
        BaseClass::calculateColors<kvs::Int8>( volume );
        BaseClass::calculateOpacities<kvs::Int8>( volume );
    }
    else if ( type == typeid( kvs::Int16 ) )
    {
        BaseClass::calculateSizes<kvs::Int16>( volume );
        BaseClass::calculateColors<kvs::Int16>( volume );
        BaseClass::calculateOpacities<kvs::Int16>( volume );
    }
    else if ( type == typeid( kvs::Int32 ) )
    {
        BaseClass::calculateSizes<kvs::Int32>( volume );
        BaseClass::calculateColors<kvs::Int32>( volume );
        BaseClass::calculateOpacities<kvs::Int32>( volume );
    }
    else if ( type == typeid( kvs::Int64 ) )
    {
        BaseClass::calculateSizes<kvs::Int64>( volume );
        BaseClass::calculateColors<kvs::Int64>( volume );
        BaseClass::calculateOpacities<kvs::Int64>( volume );
    }
    else if ( type == typeid( kvs::UInt8  ) )
    {
        BaseClass::calculateSizes<kvs::UInt8>( volume );
        BaseClass::calculateColors<kvs::UInt8>( volume );
        BaseClass::calculateOpacities<kvs::UInt8>( volume );
    }
    else if ( type == typeid( kvs::UInt16 ) )
    {
        BaseClass::calculateSizes<kvs::UInt16>( volume );
        BaseClass::calculateColors<kvs::UInt16>( volume );
        BaseClass::calculateOpacities<kvs::UInt16>( volume );
    }
    else if ( type == typeid( kvs::UInt32 ) )
    {
        BaseClass::calculateSizes<kvs::UInt32>( volume );
        BaseClass::calculateColors<kvs::UInt32>( volume );
        BaseClass::calculateOpacities<kvs::UInt32>( volume );
    }
    else if ( type == typeid( kvs::UInt64 ) )
    {
        BaseClass::calculateSizes<kvs::UInt64>( volume );
        BaseClass::calculateColors<kvs::UInt64>( volume );
        BaseClass::calculateOpacities<kvs::UInt64>( volume );
    }
    else if ( type == typeid( kvs::Real32 ) )
    {
        BaseClass::calculateSizes<kvs::Real32>( volume );
        BaseClass::calculateColors<kvs::Real32>( volume );
        BaseClass::calculateOpacities<kvs::Real32>( volume );
    }
    else if ( type == typeid( kvs::Real64 ) )
    {
        BaseClass::calculateSizes<kvs::Real64>( volume );
        BaseClass::calculateColors<kvs::Real64>( volume );
        BaseClass::calculateOpacities<kvs::Real64>( volume );
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
void SphereGlyph::initialize()
{
    glDisable( GL_LINE_SMOOTH );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glShadeModel( GL_SMOOTH );

    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable( GL_COLOR_MATERIAL );

    if( !this->isShading() )
    {
        glDisable( GL_NORMALIZE );
        glDisable( GL_LIGHTING );
    }
    else
    {
        glEnable( GL_NORMALIZE );
        glEnable( GL_LIGHTING );
    }
}

} // end of namespace kvs
