/*****************************************************************************/
/**
 *  @file   HAVSVolumeRenderer.h
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
/*----------------------------------------------------------------------------
 *
 * References:
 * [1] S.Callahan, M.Ikits, J.Comba, and C.Silva, "Hardware-Assisted Visibility
 *     Sorting for Unstructured Volume Rendering," IEEE Trans. on Visualization
 *     and Computer Graphics, Vol.11, No.3, pp.285-295, 2005.
 * [2] S.Callahan, L.Bavoil, V.Pascucci and C.Silva, "Progressive Volume Rendering
 *     of Large Unstructured Grids," IEEE Trans. on Visualization and Computer
 *     Graphics, Vol.12, No.5, pp.1307-1314, 2006.
 *
 * Acknowledgements:
 * Original source code was developped by University of Utah and can be
 * downloaded at http://havs.sourceforge.net/
 */
/*****************************************************************************/
#ifndef KVS__GLEW__HAVS_VOLUME_RENDERER_H_INCLUDE
#define KVS__GLEW__HAVS_VOLUME_RENDERER_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/Module>
#include <kvs/VolumeRendererBase>
#include <kvs/UnstructuredVolumeObject>
#include <kvs/Texture2D>
#include <kvs/glew/FragmentShader>
#include <kvs/glew/VertexShader>
#include <kvs/glew/ProgramObject>
#include <kvs/glew/VertexBufferObject>
#include <kvs/glew/IndexBufferObject>
#include <kvs/glew/ProgramObject>
#include <kvs/glew/FrameBufferObject>
#include <kvs/glew/PreIntegrationTable>


namespace kvs
{

namespace glew
{

#define KVS_GLEW_HAVS_VOLUME_RENDERER__EMBEDDED_SHADER

/*===========================================================================*/
/**
 *  @brief  HAVS volume renderer.
 */
/*===========================================================================*/
class HAVSVolumeRenderer : public kvs::VolumeRendererBase
{
    // Class name.
    kvsClassName( ParticleVolumeRenderer );

    // Module information.
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::VolumeRendererBase );

public:

    class Interval;
    class Histogram;
    class Vertex;
    class Face;
    class SortedFace;
    class Meshes;

private:

    // Reference data (NOTE: not allocated in thie class).
    const kvs::UnstructuredVolumeObject* m_ref_volume; ///< pointer to the volume data

    kvs::glew::PreIntegrationTable m_table; ///< pre-integration table
    size_t                         m_k_size; ///< k-buffer size (2 or 6)
    Meshes*                        m_meshes; ///< tetrahedral meshes for HAVS
    bool                           m_enable_vbo; ///< flag for checking if VBO is enabled
    kvs::glew::VertexBufferObject  m_vertex_coords; ///< VBO (coordinate array)
    kvs::glew::VertexBufferObject  m_vertex_values; ///< VBO (value array)
    kvs::glew::IndexBufferObject   m_vertex_indices; ///< VBO (index array)
    GLuint*                        m_pindices; ///< pointer to the index array
    kvs::glew::ProgramObject       m_shader_begin; ///< shader (begin)
    kvs::glew::ProgramObject       m_shader_kbuffer; ///< shader (kbuffer)
    kvs::glew::ProgramObject       m_shader_end; ///< shader (end)
    size_t                         m_ntargets; ///< number of targets (MRTs)
    kvs::glew::FrameBufferObject   m_mrt_framebuffer; ///< MRT frame buffer object
    kvs::Texture2D                 m_mrt_texture[4]; ///< MRT textures
    float                          m_modelview_matrix[16]; ///< modelview matrix

public:

    HAVSVolumeRenderer( void );

    HAVSVolumeRenderer( kvs::UnstructuredVolumeObject* volume, const size_t k_size = 2 );

    virtual ~HAVSVolumeRenderer( void );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void initialize( void );

    void attachVolumeObject( const kvs::UnstructuredVolumeObject* volume );

    void setKBufferSize( const size_t k_size );

    void enableVBO( void );

    void disableVBO( void );

public:

    const size_t kBufferSize( void ) const;

    const bool isEnabledVBO( void ) const;

protected:

    void initialize_geometry( void );

    void initialize_shader( void );

    void initialize_table( void );

    void initialize_framebuffer( void );

    void enable_MRT_rendering( void );

    void disable_MRT_rendering( void );

    void sort_geometry( kvs::Camera* camera );

    void draw_initialization_pass( void );

    void draw_geometry_pass( void );

    void draw_flush_pass( void );

    void draw_texture( void );
};

class HAVSVolumeRenderer::Interval
{
private:

    std::vector<kvs::UInt32> m_faces;

public:

    Interval( void );

    void addFace( const kvs::UInt32 f );

    const size_t size( void ) const;

    const kvs::UInt32 face( const size_t index );
};

inline HAVSVolumeRenderer::Interval::Interval( void )
{
}

inline void HAVSVolumeRenderer::Interval::addFace( const kvs::UInt32 f )
{
    m_faces.push_back(f);
}

inline const size_t HAVSVolumeRenderer::Interval::size( void ) const
{
    return( m_faces.size() );
}

inline const kvs::UInt32 HAVSVolumeRenderer::Interval::face( const size_t index )
{
    return( m_faces[index] );
}

class HAVSVolumeRenderer::Histogram
{
private:

    HAVSVolumeRenderer::Interval* m_scalar_table;
    size_t m_nbuckets;
    size_t m_nfaces;

public:

    Histogram( void );

    ~Histogram( void );

    void defineBuckets( const size_t nbuckets );

    void addFace( const float scalar, const size_t f );

    const kvs::UInt32 face( const size_t index, const size_t f ) const;

    const size_t bucketSize( const size_t index ) const;

    const size_t nbuckets( void ) const;

    const size_t nfaces( void ) const;

    const size_t maxBucketSize( void ) const;

    void cleanup( void );
};

inline HAVSVolumeRenderer::Histogram::Histogram( void )
{
    m_nbuckets = 128;
    m_scalar_table = new HAVSVolumeRenderer::Interval [ m_nbuckets ];
    m_nfaces = 0;
}

inline HAVSVolumeRenderer::Histogram::~Histogram( void )
{
    this->cleanup();
}

inline void HAVSVolumeRenderer::Histogram::defineBuckets( const size_t nbuckets )
{
    m_nbuckets = nbuckets;
    m_scalar_table = new HAVSVolumeRenderer::Interval[ nbuckets ];
    m_nfaces = 0;
}

inline void HAVSVolumeRenderer::Histogram::addFace( const float scalar, const size_t f )
{
    size_t i = static_cast<size_t>( scalar * m_nbuckets );
    if ( i > m_nbuckets - 1 ) { i = m_nbuckets - 1; }
    m_scalar_table[i].addFace(f);
    m_nfaces++;
}

inline const kvs::UInt32 HAVSVolumeRenderer::Histogram::face( const size_t index, const size_t f ) const
{
    return( m_scalar_table[index].face(f) );
}

inline const size_t HAVSVolumeRenderer::Histogram::bucketSize( const size_t index ) const
{
    return( m_scalar_table[index].size() );
}

inline const size_t HAVSVolumeRenderer::Histogram::nbuckets( void ) const
{
    return( m_nbuckets );
}

inline const size_t HAVSVolumeRenderer::Histogram::nfaces( void ) const
{
    return( m_nfaces );
}

inline const size_t HAVSVolumeRenderer::Histogram::maxBucketSize( void ) const
{
    size_t max = 0;
    for ( size_t i = 0; i < m_nbuckets; i++ )
    {
        max = kvs::Math::Max( max, m_scalar_table[i].size() );
    }

    return( max );
}

inline void HAVSVolumeRenderer::Histogram::cleanup( void )
{
    if ( m_scalar_table ) delete [] m_scalar_table;
    m_scalar_table = NULL;
}


/*===========================================================================*/
/**
 *  @brief  Vertex class for HAVS.
 */
/*===========================================================================*/
class HAVSVolumeRenderer::Vertex
{
private:

    float m_coord[3];
    float m_scalar;

public:

    Vertex( void );

    Vertex( const kvs::Vector3f v );

    Vertex( const float x, const float y, const float z, const float s = 0.0f );

public:

    void setScalar( const float s );

    const float x( void ) const;

    const float y( void ) const;

    const float z( void ) const;

    const float scalar( void ) const;

    const float* coord( void ) const;

    const float norm2( void ) const;

    Vertex operator - ( const Vertex& v ) const;
};

inline HAVSVolumeRenderer::Vertex::Vertex( void )
{
    m_coord[0] = 0.0f;
    m_coord[1] = 0.0f;
    m_coord[2] = 0.0f;
    m_scalar = 0.0f;
}

inline HAVSVolumeRenderer::Vertex::Vertex( const kvs::Vector3f v )
{
    m_coord[0] = v.x();
    m_coord[1] = v.y();
    m_coord[2] = v.z();
    m_scalar = 0.0f;
}

inline HAVSVolumeRenderer::Vertex::Vertex( const float x, const float y, const float z, const float s )
{
    m_coord[0] = x;
    m_coord[1] = y;
    m_coord[2] = z;
    m_scalar = s;
}

inline void HAVSVolumeRenderer::Vertex::setScalar( const float s )
{
    m_scalar = s;
}

inline const float HAVSVolumeRenderer::Vertex::x( void ) const
{
    return( m_coord[0] );
}

inline const float HAVSVolumeRenderer::Vertex::y( void ) const
{
    return( m_coord[1] );
}

inline const float HAVSVolumeRenderer::Vertex::z( void ) const
{
    return( m_coord[2] );
}

inline const float HAVSVolumeRenderer::Vertex::scalar( void ) const
{
    return( m_scalar );
}

inline const float* HAVSVolumeRenderer::Vertex::coord( void ) const
{
    return( &m_coord[0] );
}

inline const float HAVSVolumeRenderer::Vertex::norm2( void ) const
{
    return( m_coord[0] * m_coord[0] + m_coord[1] * m_coord[1] + m_coord[2] * m_coord[2] );
}

inline HAVSVolumeRenderer::Vertex HAVSVolumeRenderer::Vertex::operator - (
    const HAVSVolumeRenderer::Vertex& v ) const
{
    return( HAVSVolumeRenderer::Vertex(
                m_coord[0] - v.m_coord[0],
                m_coord[1] - v.m_coord[1],
                m_coord[2] - v.m_coord[2],
                m_scalar   - v.m_scalar ) );
}

/*===========================================================================*/
/**
 *  @brief  Face class for HAVS.
 */
/*===========================================================================*/
class HAVSVolumeRenderer::Face
{
private:

    kvs::UInt32  m_index[3]; ///< indices of the triangle face
    mutable bool m_boundary; ///< check flag for the boundary face

public:

    Face( void );

    Face( const kvs::UInt32 id0, const kvs::UInt32 id1, const kvs::UInt32 id2 );

public:

    void setBoundary( const bool boundary ) const;

    const kvs::UInt32 index( const size_t i ) const;

    const bool isBoundary( void ) const;
};

inline HAVSVolumeRenderer::Face::Face( void )
{
    m_index[0] = 0;
    m_index[1] = 0;
    m_index[2] = 0;
    m_boundary = true;
}

inline HAVSVolumeRenderer::Face::Face(
    const kvs::UInt32 id0,
    const kvs::UInt32 id1,
    const kvs::UInt32 id2 )
{
    m_index[0] = id0;
    m_index[1] = id1;
    m_index[2] = id2;
    m_boundary = true;
}

inline void HAVSVolumeRenderer::Face::setBoundary( const bool boundary ) const
{
    m_boundary = boundary;
}

inline const kvs::UInt32 HAVSVolumeRenderer::Face::index( const size_t i ) const
{
    return( m_index[i] );
}

inline const bool HAVSVolumeRenderer::Face::isBoundary( void ) const
{
    return( m_boundary );
}

/*===========================================================================*/
/**
 *  @brief  Face class for radix sort.
 */
/*===========================================================================*/
class HAVSVolumeRenderer::SortedFace
{
private:

    kvs::UInt32 m_face; ///< face ID
    kvs::UInt32 m_distance; ///< distance

public:

    SortedFace( void );

    SortedFace( const kvs::UInt32 face, const kvs::UInt32 distance );

    const bool operator < ( const SortedFace& face ) const;

    const bool operator <= ( const SortedFace& face ) const;

    const bool operator >= (const SortedFace& face ) const;

    const kvs::UInt32 face( void ) const;

    const kvs::UInt32 distance( void ) const;
};

inline HAVSVolumeRenderer::SortedFace::SortedFace( void )
{
}

inline HAVSVolumeRenderer::SortedFace::SortedFace(
    const kvs::UInt32 face,
    const kvs::UInt32 distance ):
    m_face( face ),
    m_distance( distance ^ ( ( -( distance >> 31 ) ) | 0x80000000 ) )
{
}

inline const bool HAVSVolumeRenderer::SortedFace::operator < (
    const HAVSVolumeRenderer::SortedFace& face ) const
{
    return( m_distance < face.m_distance );
}

inline const bool HAVSVolumeRenderer::SortedFace::operator <= (
    const HAVSVolumeRenderer::SortedFace& face ) const
{
    return( m_distance <= face.m_distance );
}

inline const bool HAVSVolumeRenderer::SortedFace::operator >= (
    const HAVSVolumeRenderer::SortedFace& face ) const
{
    return( m_distance >= face.m_distance );
}

inline const kvs::UInt32 HAVSVolumeRenderer::SortedFace::face( void ) const
{
    return( m_face );
}

inline const kvs::UInt32 HAVSVolumeRenderer::SortedFace::distance( void ) const
{
    return( m_distance );
}

/*===========================================================================*/
/**
 *  @brief  Mesh class for HAVS.
 */
/*===========================================================================*/
class HAVSVolumeRenderer::Meshes
{
private:

    kvs::ValueArray<kvs::Real32>    m_coords;
    kvs::ValueArray<kvs::UInt32>    m_connections;
    kvs::ValueArray<kvs::Real32>    m_values;
    HAVSVolumeRenderer::Face*       m_faces;
    kvs::ValueArray<kvs::UInt32>    m_boundary_faces;
    kvs::ValueArray<kvs::UInt32>    m_internal_faces;
    HAVSVolumeRenderer::SortedFace* m_sorted_faces;
    HAVSVolumeRenderer::Vertex*     m_centers;
    HAVSVolumeRenderer::SortedFace* m_radix_temp;

    size_t m_nvertices;
    size_t m_ntetrahedra;
    size_t m_nfaces;
    size_t m_nboundaryfaces;
    size_t m_ninternalfaces;
    size_t m_nrenderfaces;

    float m_diagonal;
    kvs::Vector3f m_bb_min;
    kvs::Vector3f m_bb_max;
    float m_depth_scale;
    float m_min_scalar;
    float m_max_scalar;

public:

    Meshes( void );

    ~Meshes( void );

public:

    void setVolume( const kvs::UnstructuredVolumeObject* volume );

public:

    const Face face( const size_t index );

    const kvs::UInt32 sortedFace( const size_t face_id );

    const kvs::ValueArray<kvs::Real32>& coords( void ) const;

    const kvs::ValueArray<kvs::UInt32>& connections( void ) const;

    const kvs::ValueArray<kvs::Real32>& values( void ) const;

    const size_t nvertices( void ) const;

    const size_t ntetrahedra( void ) const;

    const size_t nfaces( void ) const;

    const size_t nrenderfaces( void ) const;

    const float depthScale( void ) const;

    const float diagonal( void ) const;

public:

    void build( void );

    void clean( void );

    void sort( Vertex eye );

private:

    void radix_sort( SortedFace* array, SortedFace* temp, int lo, int up );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__HAVS_VOLUME_RENDERER_H_INCLUDE
