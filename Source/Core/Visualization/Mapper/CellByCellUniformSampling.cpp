/****************************************************************************/
/**
 *  @file CellByCellUniformSampling.cpp
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
#include "CellByCellUniformSampling.h"
#include <vector>
#include <kvs/GlobalCore>
#include <kvs/ObjectManager>
#include <kvs/Camera>
#include <kvs/TrilinearInterpolator>
#include <kvs/Value>
#include "CellBase.h"
#include "TetrahedralCell.h"
#include "QuadraticTetrahedralCell.h"
#include "HexahedralCell.h"
#include "QuadraticHexahedralCell.h"


namespace Generator = kvs::CellByCellParticleGenerator;


namespace kvs
{

CellByCellUniformSampling::CellByCellUniformSampling( void ):
    kvs::MapperBase(),
    kvs::PointObject(),
    m_camera( 0 )
{
}

CellByCellUniformSampling::CellByCellUniformSampling(
    const kvs::VolumeObjectBase* volume,
    const size_t                 subpixel_level,
    const float                  sampling_step,
    const kvs::TransferFunction& transfer_function,
    const float                  object_depth ):
    kvs::MapperBase( transfer_function ),
    kvs::PointObject(),
    m_camera( 0 )
{
    this->setSubpixelLevel( subpixel_level );
    this->setSamplingStep( sampling_step );
    this->setObjectDepth( object_depth );
    this->exec( volume );
}

CellByCellUniformSampling::CellByCellUniformSampling(
    const kvs::Camera*           camera,
    const kvs::VolumeObjectBase* volume,
    const size_t                 subpixel_level,
    const float                  sampling_step,
    const kvs::TransferFunction& transfer_function,
    const float                  object_depth ):
    kvs::MapperBase( transfer_function ),
    kvs::PointObject()
{
    this->attachCamera( camera ),
    this->setSubpixelLevel( subpixel_level );
    this->setSamplingStep( sampling_step );
    this->setObjectDepth( object_depth );
    this->exec( volume );
}

CellByCellUniformSampling::~CellByCellUniformSampling( void )
{
    m_density_map.deallocate();
}

const size_t CellByCellUniformSampling::subpixelLevel( void ) const
{
    return( m_subpixel_level );
}

const float CellByCellUniformSampling::samplingStep( void ) const
{
    return( m_sampling_step );
}

const float CellByCellUniformSampling::objectDepth( void ) const
{
    return( m_object_depth );
}

void CellByCellUniformSampling::attachCamera( const kvs::Camera* camera )
{
    m_camera = camera;
}

void CellByCellUniformSampling::setSubpixelLevel( const size_t subpixel_level )
{
    m_subpixel_level = subpixel_level;
}

void CellByCellUniformSampling::setSamplingStep( const float sampling_step )
{
    m_sampling_step = sampling_step;
}

void CellByCellUniformSampling::setObjectDepth( const float object_depth )
{
    m_object_depth = object_depth;
}

kvs::ObjectBase* CellByCellUniformSampling::exec( const kvs::ObjectBase* object )
{
    const kvs::ObjectBase::ObjectType object_type = object->objectType();
    if ( object_type == kvs::ObjectBase::Geometry )
    {
        kvsMessageError("Geometry object is not supported.");
        return( NULL );
    }

    const kvs::VolumeObjectBase* volume = reinterpret_cast<const kvs::VolumeObjectBase*>( object );
    const kvs::VolumeObjectBase::VolumeType volume_type = volume->volumeType();
    if ( volume_type == kvs::VolumeObjectBase::Structured )
    {
        const kvs::Camera* camera = ( !m_camera ) ? kvs::GlobalCore::camera : m_camera;
        this->mapping( camera, reinterpret_cast<const kvs::StructuredVolumeObject*>( object ) );
    }
    else // volume_type == kvs::VolumeObjectBase::Unstructured
    {
        const kvs::Camera* camera = ( !m_camera ) ? kvs::GlobalCore::camera : m_camera;
        this->mapping( camera, reinterpret_cast<const kvs::UnstructuredVolumeObject*>( object ) );
    }

    return( this );
}

void CellByCellUniformSampling::mapping( const kvs::Camera* camera, const kvs::StructuredVolumeObject* volume )
{
    // Attach the pointer to the volume object and set the min/max coordinates.
    BaseClass::attach_volume( volume );
    BaseClass::set_min_max_coords( volume, this );

    // Calculate the density map.
    m_density_map = Generator::CalculateDensityMap(
        camera,
        BaseClass::volume(),
        static_cast<float>( m_subpixel_level ),
        m_sampling_step,
        BaseClass::transferFunction().opacityMap() );

    // Generate the particles.
    const std::type_info& type = volume->values().typeInfo()->type();
    if (      type == typeid( kvs::UInt8  ) ) this->generate_particles<kvs::UInt8>( volume );
    else if ( type == typeid( kvs::UInt16 ) ) this->generate_particles<kvs::UInt16>( volume );
    else if ( type == typeid( kvs::Real32 ) ) this->generate_particles<kvs::Real32>( volume );
    else if ( type == typeid( kvs::Real64 ) ) this->generate_particles<kvs::Real64>( volume );
    else
    {
        kvsMessageError("Unsupported data type '%s' of the structured volume.",
                        volume->values().typeInfo()->typeName() );
    }
}

void CellByCellUniformSampling::mapping( const kvs::Camera* camera, const kvs::UnstructuredVolumeObject* volume )
{
    // Attach the pointer to the volume object and set the min/max coordinates.
    BaseClass::attach_volume( volume );
    BaseClass::set_min_max_coords( volume, this );

    // Calculate the density map.
    m_density_map = Generator::CalculateDensityMap(
        camera,
        BaseClass::volume(),
        static_cast<float>( m_subpixel_level ),
        m_sampling_step,
        BaseClass::transferFunction().opacityMap() );

    // Generate the particles.
    const std::type_info& type = volume->values().typeInfo()->type();
    if (      type == typeid( kvs::Int8   ) ) this->generate_particles<kvs::Int8>( volume );
    else if ( type == typeid( kvs::Int16  ) ) this->generate_particles<kvs::Int16>( volume );
    else if ( type == typeid( kvs::Int32  ) ) this->generate_particles<kvs::Int32>( volume );
    else if ( type == typeid( kvs::Int64  ) ) this->generate_particles<kvs::Int64>( volume );
    else if ( type == typeid( kvs::UInt8  ) ) this->generate_particles<kvs::UInt8>( volume );
    else if ( type == typeid( kvs::UInt16 ) ) this->generate_particles<kvs::UInt16>( volume );
    else if ( type == typeid( kvs::UInt32 ) ) this->generate_particles<kvs::UInt32>( volume );
    else if ( type == typeid( kvs::UInt64 ) ) this->generate_particles<kvs::UInt64>( volume );
    else if ( type == typeid( kvs::Real32 ) ) this->generate_particles<kvs::Real32>( volume );
    else if ( type == typeid( kvs::Real64 ) ) this->generate_particles<kvs::Real64>( volume );
    else
    {
        kvsMessageError("Unsupported data type '%s' of the structured volume.",
                        volume->values().typeInfo()->typeName() );
    }
}

template <typename T>
void CellByCellUniformSampling::generate_particles( const kvs::StructuredVolumeObject* volume )
{
    // Vertex data arrays. (output)
    std::vector<kvs::Real32> vertex_coords;
    std::vector<kvs::UInt8>  vertex_colors;
    std::vector<kvs::Real32> vertex_normals;

    // Set a trilinear interpolator.
    kvs::TrilinearInterpolator interpolator( volume );

    // Set parameters for normalization of the node values.
    const float min_value = ( typeid(T) == typeid( kvs::UInt8 ) ) ? 0.0f : static_cast<float>( volume->minValue() );
    const float max_value = ( typeid(T) == typeid( kvs::UInt8 ) ) ? 255.0f : static_cast<float>( volume->maxValue() );
    const float normalize_factor = BaseClass::transferFunction().resolution() / ( max_value - min_value );

    const float* const  density_map = m_density_map.pointer();
    const kvs::ColorMap color_map( BaseClass::transferFunction().colorMap() );

    // Generate particles for each cell.
    const kvs::Vector3ui ncells( volume->resolution() - kvs::Vector3ui(1) );
    for ( kvs::UInt32 z = 0; z < ncells.z(); ++z )
    {
        for ( kvs::UInt32 y = 0; y < ncells.y(); ++y )
        {
            for ( kvs::UInt32 x = 0; x < ncells.x(); ++x )
            {
                // Calculate a volume of cell.
                const float volume_of_cell = 1.0f;

                // Interpolate at the center of gravity of this cell.
                const kvs::Vector3f cog( x + 0.5f, y + 0.5f, z + 0.5f );
                interpolator.attachPoint( cog );

                // Calculate a density.
                const float  average_scalar = interpolator.scalar<T>();
                const size_t average_degree = static_cast<size_t>( ( average_scalar - min_value ) * normalize_factor );
                const float  density = density_map[ average_degree ];

                // Calculate a number of particles in this cell.
                const float p = density * volume_of_cell;
                size_t nparticles_in_cell = static_cast<size_t>( p );
                if ( p - nparticles_in_cell > Generator::GetRandomNumber() ) { ++nparticles_in_cell; }

                const kvs::Vector3f v( static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) );
                for ( size_t particle = 0; particle < nparticles_in_cell; ++particle )
                {
                    // Calculate a coord.
                    const kvs::Vector3f coord( Generator::RandomSamplingInCube( v ) );

                    // Calculate a color.
                    interpolator.attachPoint( coord );
                    const size_t degree = static_cast<size_t>( ( interpolator.scalar<T>() - min_value ) * normalize_factor );
                    const kvs::RGBColor color( color_map[ degree ] );

                    // Calculate a normal.
                    const Vector3f normal( interpolator.gradient<T>() );

                    // set coord, color, and normal to point object( this ).
                    vertex_coords.push_back( coord.x() );
                    vertex_coords.push_back( coord.y() );
                    vertex_coords.push_back( coord.z() );

                    vertex_colors.push_back( color.r() );
                    vertex_colors.push_back( color.g() );
                    vertex_colors.push_back( color.b() );

                    vertex_normals.push_back( normal.x() );
                    vertex_normals.push_back( normal.y() );
                    vertex_normals.push_back( normal.z() );
                } // end of 'paricle' for-loop
            } // end of 'x' loop
        } // end of 'y' loop
    } // end of 'z' loop

    SuperClass::m_coords  = kvs::ValueArray<kvs::Real32>( vertex_coords );
    SuperClass::m_colors  = kvs::ValueArray<kvs::UInt8>( vertex_colors );
    SuperClass::m_normals = kvs::ValueArray<kvs::Real32>( vertex_normals );
    SuperClass::setSize( 1.0f );
}

template <typename T>
void CellByCellUniformSampling::generate_particles( const kvs::UnstructuredVolumeObject* volume )
{
    // Vertex data arrays. (output)
    std::vector<kvs::Real32> vertex_coords;
    std::vector<kvs::UInt8>  vertex_colors;
    std::vector<kvs::Real32> vertex_normals;

    // Set a tetrahedral cell interpolator.
    kvs::CellBase<T>* cell = NULL;
    switch ( volume->cellType() )
    {
    case kvs::VolumeObjectBase::Tetrahedra:
    {
        cell = new kvs::TetrahedralCell<T>( volume );
        break;
    }
    case kvs::VolumeObjectBase::QuadraticTetrahedra:
    {
        cell = new kvs::QuadraticTetrahedralCell<T>( volume );
        break;
    }
    case kvs::VolumeObjectBase::Hexahedra:
    {
        cell = new kvs::HexahedralCell<T>( volume );
        break;
    }
    case kvs::VolumeObjectBase::QuadraticHexahedra:
    {
        cell = new kvs::QuadraticHexahedralCell<T>( volume );
        break;
    }
    default:
        kvsMessageError("Unsupported cell type.");
        return;
    }

    const float min_value = ( typeid(T) == typeid( kvs::UInt8 ) ) ? 0.0f : static_cast<float>( volume->minValue() );
    const float max_value = ( typeid(T) == typeid( kvs::UInt8 ) ) ? 255.0f : static_cast<float>( volume->maxValue() );
    const float max_range = static_cast<float>( BaseClass::transferFunction().resolution() - 1 );
    const float normalize_factor = max_range / ( max_value - min_value );

    const float* const  density_map = m_density_map.pointer();
    const kvs::ColorMap color_map( BaseClass::transferFunction().colorMap() );

    // Generate particles for each cell.
    const size_t ncells = volume->ncells();
    for ( size_t index = 0; index < ncells; ++index )
    {
        // Attach the cell which is specified by 'index'.
        cell->attachCell( index );

        // Calculate a density.
        const float  average_scalar = cell->averagedScalar();
        const size_t average_degree = static_cast<size_t>( ( average_scalar - min_value ) * normalize_factor );
        const float  density = density_map[ average_degree ];

        // Calculate a number of particles in this cell.
        const float volume_of_cell = cell->volume();
        const float p = density * volume_of_cell;
        size_t nparticles_in_cell = static_cast<size_t>( p );

        if ( p - nparticles_in_cell > Generator::GetRandomNumber() ) { ++nparticles_in_cell; }

        // Generate a set of particles in this cell represented by v0,...,v3 and s0,...,s3.
        for ( size_t particle = 0; particle < nparticles_in_cell; ++particle )
        {
            // Calculate a coord.
            const kvs::Vector3f coord = cell->randomSampling();

            // Calculate a color.
            const float degree = ( cell->scalar() - min_value ) * normalize_factor;
            const kvs::RGBColor color ( color_map[ size_t( kvs::Math::Clamp( degree, 0.0f, max_range ) ) ] );

            // Calculate a normal.
            const Vector3f normal( cell->gradient() );

            // set coord, color, and normal to point object( this ).
            vertex_coords.push_back( coord.x() );
            vertex_coords.push_back( coord.y() );
            vertex_coords.push_back( coord.z() );

            vertex_colors.push_back( color.r() );
            vertex_colors.push_back( color.g() );
            vertex_colors.push_back( color.b() );

            vertex_normals.push_back( normal.x() );
            vertex_normals.push_back( normal.y() );
            vertex_normals.push_back( normal.z() );
            
        } // end of 'paricle' for-loop
    } // end of 'cell' for-loop

    SuperClass::m_coords  = kvs::ValueArray<kvs::Real32>( vertex_coords );
    SuperClass::m_colors  = kvs::ValueArray<kvs::UInt8>( vertex_colors );
    SuperClass::m_normals = kvs::ValueArray<kvs::Real32>( vertex_normals );
    SuperClass::setSize( 1.0f );

    delete cell;
}

} // end of namespace kvs
