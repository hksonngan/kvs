/****************************************************************************/
/**
 *  @file CellByCellMetropolisSampling.cpp
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
#include "CellByCellMetropolisSampling.h"
#include <vector>
#include <kvs/ObjectManager>
#include <kvs/Camera>
#include <kvs/TrilinearInterpolator>
#include <kvs/Value>
#include "CellBase.h"
#include "TetrahedralCell.h"
#include "QuadraticTetrahedralCell.h"
#include "HexahedralCell.h"
#include "QuadraticHexahedralCell.h"

#include <kvs/GlobalCore>


namespace Generator = kvs::CellByCellParticleGenerator;


namespace kvs
{

CellByCellMetropolisSampling::CellByCellMetropolisSampling( void ):
    kvs::MapperBase(),
    kvs::PointObject(),
    m_camera( 0 )
{
}

CellByCellMetropolisSampling::CellByCellMetropolisSampling(
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

CellByCellMetropolisSampling::CellByCellMetropolisSampling(
    const kvs::Camera*           camera,
    const kvs::VolumeObjectBase* volume,
    const size_t                 subpixel_level,
    const float                  sampling_step,
    const kvs::TransferFunction& transfer_function,
    const float                  object_depth ):
    kvs::MapperBase( transfer_function ),
    kvs::PointObject()
{
    this->attachCamera( camera );
    this->setSubpixelLevel( subpixel_level );
    this->setSamplingStep( sampling_step );
    this->setObjectDepth( object_depth );
    this->exec( volume );
}

CellByCellMetropolisSampling::~CellByCellMetropolisSampling( void )
{
    m_density_map.deallocate();
}

const size_t CellByCellMetropolisSampling::subpixelLevel( void ) const
{
    return( m_subpixel_level );
}

const float CellByCellMetropolisSampling::samplingStep( void ) const
{
    return( m_sampling_step );
}

const float CellByCellMetropolisSampling::objectDepth( void ) const
{
    return( m_object_depth );
}

void CellByCellMetropolisSampling::attachCamera( const kvs::Camera* camera )
{
    m_camera = camera;
}

void CellByCellMetropolisSampling::setSubpixelLevel( const size_t subpixel_level )
{
    m_subpixel_level = subpixel_level;
}

void CellByCellMetropolisSampling::setSamplingStep( const float sampling_step )
{
    m_sampling_step = sampling_step;
}

void CellByCellMetropolisSampling::setObjectDepth( const float object_depth )
{
    m_object_depth = object_depth;
}

kvs::ObjectBase* CellByCellMetropolisSampling::exec( const kvs::ObjectBase* object )
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
//        const kvs::Camera* camera = ( !m_camera ) ? kvs::GlobalCore::camera : m_camera;
//        this->mapping( camera, reinterpret_cast<const kvs::StructuredVolumeObject*>( object ) );
        if ( m_camera )
        {
            this->mapping( m_camera, reinterpret_cast<const kvs::StructuredVolumeObject*>( object ) );
        }
        else
        {
            // Generate particles by using default camera parameters.
            if ( kvs::GlobalCore::camera )
            {
                if ( kvs::GlobalCore::camera->windowWidth() != 0 && kvs::GlobalCore::camera->windowHeight() )
                {
                    const kvs::Camera* camera = kvs::GlobalCore::camera;
                    this->mapping( camera, reinterpret_cast<const kvs::StructuredVolumeObject*>( object ) );
                }
            }
            else
            {
                kvs::Camera* camera = new kvs::Camera();
                this->mapping( camera, reinterpret_cast<const kvs::StructuredVolumeObject*>( object ) );
                delete camera;
            }
        }
    }
    else // volume_type == kvs::VolumeObjectBase::Unstructured
    {
//        const kvs::Camera* camera = ( !m_camera ) ? kvs::GlobalCore::camera : m_camera;
//        this->mapping( camera, reinterpret_cast<const kvs::UnstructuredVolumeObject*>( object ) );
        if ( m_camera )
        {
            this->mapping( m_camera, reinterpret_cast<const kvs::UnstructuredVolumeObject*>( object ) );
        }
        else
        {
            // Generate particles by using default camera parameters.
            if ( kvs::GlobalCore::camera )
            {
                if ( kvs::GlobalCore::camera->windowWidth() != 0 && kvs::GlobalCore::camera->windowHeight() )
                {
                    const kvs::Camera* camera = kvs::GlobalCore::camera;
                    this->mapping( camera, reinterpret_cast<const kvs::UnstructuredVolumeObject*>( object ) );
                }
            }
            else
            {
                kvs::Camera* camera = new kvs::Camera();
                this->mapping( camera, reinterpret_cast<const kvs::UnstructuredVolumeObject*>( object ) );
                delete camera;
            }
        }
    }

    return( this );
}

void CellByCellMetropolisSampling::mapping(const kvs::Camera* camera, const kvs::StructuredVolumeObject* volume )
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

void CellByCellMetropolisSampling::mapping( const kvs::Camera* camera, const kvs::UnstructuredVolumeObject* volume )
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
void CellByCellMetropolisSampling::generate_particles( const kvs::StructuredVolumeObject* volume )
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
    const size_t max_range = BaseClass::transferFunction().resolution() - 1;
    const float normalize_factor = max_range / ( max_value - min_value );

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
                const float  average_density = density_map[ average_degree ];

                // Calculate a number of particles in this cell.
                const float p = average_density * volume_of_cell;
                size_t nparticles_in_cell = static_cast<size_t>( p );
                if ( p - nparticles_in_cell > Generator::GetRandomNumber() ) { ++nparticles_in_cell; }

                if( nparticles_in_cell == 0 ) continue;

//                const kvs::Vector3f v( x, y, z );
                const kvs::Vector3f v( static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) );

                // Calculate itnitial value
                kvs::Vector3f point( Generator::RandomSamplingInCube( v ) );
                interpolator.attachPoint( point );
                float scalar = interpolator.scalar<T>();
                size_t degree = static_cast< size_t >( ( scalar - min_value ) * normalize_factor );
                degree = kvs::Math::Clamp<size_t>( degree, 0, max_range );
                float density = density_map[ degree ];

                kvs::Vector3f point_trial( Generator::RandomSamplingInCube( v ) );
                interpolator.attachPoint( point_trial );
                float scalar_trial = interpolator.scalar<T>();
                size_t degree_trial = static_cast< size_t >( ( scalar_trial - min_value ) * normalize_factor );
                degree_trial = kvs::Math::Clamp<size_t>( degree_trial, 0, max_range );
                float density_trial = density_map[ degree_trial ];

                while( Math::IsZero( density ) )
                {
                    point= Generator::RandomSamplingInCube( v );
                    interpolator.attachPoint( point );
                    scalar = interpolator.scalar<T>();
                    degree = static_cast< size_t >( ( scalar - min_value ) * normalize_factor );
                    degree = kvs::Math::Clamp<size_t>( degree, 0, max_range );
                    density = density_map[ degree ];
                }

                //Generate N particles
                size_t counter = 0;
                while( counter < nparticles_in_cell )
                {
                    //set trial position and density
                    point_trial = Generator::RandomSamplingInCube( v );
                    interpolator.attachPoint( point_trial );
                    scalar_trial = interpolator.scalar<T>();
                    degree_trial = static_cast< size_t >( ( scalar_trial - min_value ) * normalize_factor );
                    degree_trial = kvs::Math::Clamp<size_t>( degree_trial, 0, max_range );
                    density_trial = density_map[ degree_trial ];

                    //calculate ratio
                    double ratio = density_trial / density;

                    if( ratio >= 1.0 ) // accept trial point
                    {
                        // calculate color
                        interpolator.attachPoint( point_trial );
                        scalar_trial = interpolator.scalar<T>();
                        degree_trial = static_cast< size_t >( ( scalar_trial -min_value ) * normalize_factor );
                        degree_trial = kvs::Math::Clamp<size_t>( degree_trial, 0, max_range );
                        const kvs::RGBColor color( color_map[ degree_trial ] );

                        // calculate normal
                        const Vector3f normal( interpolator.gradient<T>() );

                        vertex_coords.push_back( point_trial.x() );
                        vertex_coords.push_back( point_trial.y() );
                        vertex_coords.push_back( point_trial.z() );

                        vertex_colors.push_back( color.r() );
                        vertex_colors.push_back( color.g() );
                        vertex_colors.push_back( color.b() );

                        vertex_normals.push_back( normal.x() );
                        vertex_normals.push_back( normal.y() );
                        vertex_normals.push_back( normal.z() );

                        // update point
                        point = point_trial;
                        density = density_trial;

                        counter++;
                    }
                    else
                    {
                        if( ratio >= Generator::GetRandomNumber() ) // accept point trial
                        {
                            // calculate color
                            interpolator.attachPoint( point_trial );
                            scalar_trial = interpolator.scalar<T>();
                            degree_trial = static_cast< size_t >( ( scalar_trial -min_value ) * normalize_factor );
                            degree_trial = kvs::Math::Clamp<size_t>( degree_trial, 0, max_range );
                            const kvs::RGBColor color( color_map[ degree_trial ] );

                            // calculate normal
                            const Vector3f normal( interpolator.gradient<T>() );

                            vertex_coords.push_back( point_trial.x() );
                            vertex_coords.push_back( point_trial.y() );
                            vertex_coords.push_back( point_trial.z() );

                            vertex_colors.push_back( color.r() );
                            vertex_colors.push_back( color.g() );
                            vertex_colors.push_back( color.b() );

                            vertex_normals.push_back( normal.x() );
                            vertex_normals.push_back( normal.y() );
                            vertex_normals.push_back( normal.z() );

                            // update point
                            point = point_trial;
                            density = density_trial;

                            counter++;
                        }
                        else // accept current point
                        {
#ifdef DUPLICATION
                            // calculate color
                            interpolator.attachPoint( point );
                            scalar = interpolator.scalar<T>();
                            degree = static_cast< size_t >( ( scalar - min_value ) * normalize_factor );
                            degree = kvs::Math::Clamp<size_t>( degree, 0, max_range );
                            const kvs::RGBColor color( color_map[ degree ] );

                            //calculate normal
                            const Vector3f normal( interpolator.gradient<T>() );

                            vertex_coords.push_back( point_trial.x() );
                            vertex_coords.push_back( point_trial.y() );
                            vertex_coords.push_back( point_trial.z() );

                            vertex_colors.push_back( color.r() );
                            vertex_colors.push_back( color.g() );
                            vertex_colors.push_back( color.b() );

                            vertex_normals.push_back( normal.x() );
                            vertex_normals.push_back( normal.y() );
                            vertex_normals.push_back( normal.z() );

                            counter++;
#else
                            continue;
#endif
                        }
                    }
                } // end of 'paricle' while-loop
            } // end of 'x' loop
        } // end of 'y' loop
    } // end of 'z' loop

    SuperClass::m_coords  = kvs::ValueArray<kvs::Real32>( vertex_coords );
    SuperClass::m_colors  = kvs::ValueArray<kvs::UInt8>( vertex_colors );
    SuperClass::m_normals = kvs::ValueArray<kvs::Real32>( vertex_normals );
    SuperClass::setSize( 1.0f );
}

template <typename T>
void CellByCellMetropolisSampling::generate_particles( const kvs::UnstructuredVolumeObject* volume )
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
    const size_t max_range = BaseClass::transferFunction().resolution() - 1;
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
        const float  average_density = density_map[ average_degree ];

        // Calculate a number of particles in this cell.
        const float volume_of_cell = cell->volume();
        const float p = average_density * volume_of_cell;
        size_t nparticles_in_cell = static_cast<size_t>( p );

        if ( p - nparticles_in_cell > Generator::GetRandomNumber() ) { ++nparticles_in_cell; }
        if( nparticles_in_cell == 0 ) continue;

        // Calculate itnitial value
        kvs::Vector3f point = cell->randomSampling();
        size_t        degree = static_cast< size_t >( ( cell->scalar() - min_value ) * normalize_factor );
        degree = kvs::Math::Clamp<size_t>( degree, 0, max_range );
        float         density = density_map[ degree ];
        kvs::Vector3f g = cell->gradient();

        kvs::Vector3f point_trial;
        size_t        degree_trial;
        float         density_trial;
        kvs::Vector3f g_trial;

        while( Math::IsZero( density ) )
        {
            point = cell->randomSampling();
            degree = static_cast< size_t >( ( cell->scalar() - min_value ) * normalize_factor );
            degree = kvs::Math::Clamp<size_t>( degree, 0, max_range );
            density = density_map[ degree ];
            g = cell->gradient();
        }

        //Generate N particles
        size_t counter = 0;
        while( counter < nparticles_in_cell )
        {
            //set trial position and density
            point_trial = cell->randomSampling();
            degree_trial = static_cast< size_t >( ( cell->scalar() - min_value ) * normalize_factor );
            degree_trial = kvs::Math::Clamp<size_t>( degree_trial, 0, max_range );
            density_trial = density_map[ degree_trial ];
            g_trial = cell->gradient();

            //calculate ratio
            double ratio = density_trial / density;

            if( ratio >= 1.0 ) // accept trial point
            {
                // calculate color
                const kvs::RGBColor color( color_map[ degree_trial ] );

                // calculate normal
                const Vector3f normal( g_trial );

                vertex_coords.push_back( point_trial.x() );
                vertex_coords.push_back( point_trial.y() );
                vertex_coords.push_back( point_trial.z() );

                vertex_colors.push_back( color.r() );
                vertex_colors.push_back( color.g() );
                vertex_colors.push_back( color.b() );

                vertex_normals.push_back( normal.x() );
                vertex_normals.push_back( normal.y() );
                vertex_normals.push_back( normal.z() );

                // update point
                point = point_trial;
                degree = degree_trial;
                density = density_trial;
                g = g_trial;

                counter++;
            }
            else
            {
                if( ratio >= Generator::GetRandomNumber() ) // accept point trial
                {
                    // calculate color
                    const kvs::RGBColor color( color_map[ degree_trial ] );

                    // calculate normal
                    const Vector3f normal( g_trial );

                    vertex_coords.push_back( point_trial.x() );
                    vertex_coords.push_back( point_trial.y() );
                    vertex_coords.push_back( point_trial.z() );

                    vertex_colors.push_back( color.r() );
                    vertex_colors.push_back( color.g() );
                    vertex_colors.push_back( color.b() );

                    vertex_normals.push_back( normal.x() );
                    vertex_normals.push_back( normal.y() );
                    vertex_normals.push_back( normal.z() );

                    // update point
                    point = point_trial;
                    degree = degree_trial;
                    density = density_trial;
                    g = g_trial;

                    counter++;
                }
                else // accept current point
                {
#ifdef DUPLICATION
                    // calculate color
                    const kvs::RGBColor color( color_map[ degree ] );

                    //calculate normal
                    const Vector3f normal( g );

                    vertex_coords.push_back( point_trial.x() );
                    vertex_coords.push_back( point_trial.y() );
                    vertex_coords.push_back( point_trial.z() );

                    vertex_colors.push_back( color.r() );
                    vertex_colors.push_back( color.g() );
                    vertex_colors.push_back( color.b() );

                    vertex_normals.push_back( normal.x() );
                    vertex_normals.push_back( normal.y() );
                    vertex_normals.push_back( normal.z() );

                    counter++;
#else
                    continue;
#endif
                }
            }
        } // end of 'paricle' while-loop
    } // end of 'cell' for-loop

    SuperClass::m_coords  = kvs::ValueArray<kvs::Real32>( vertex_coords );
    SuperClass::m_colors  = kvs::ValueArray<kvs::UInt8>( vertex_colors );
    SuperClass::m_normals = kvs::ValueArray<kvs::Real32>( vertex_normals );
    SuperClass::setSize( 1.0f );

    delete cell;
}

} // end of namespace kvs
