/****************************************************************************/
/**
 *  @file UnstructuredVolumeImporter.cpp
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
#include "UnstructuredVolumeImporter.h"

#include <kvs/AVSUcd>
#include <kvs/Message>
#include <kvs/Vector3>


namespace
{

/*==========================================================================*/
/**
 *  Converts to the cell type from the given string.
 *  @param cell_type [in] grid type string
 *  @return cell type
 */
/*==========================================================================*/
const kvs::UnstructuredVolumeObject::CellType StringToCellType( const std::string& cell_type )
{
    if (      cell_type == "tetrahedra" ) { return( kvs::UnstructuredVolumeObject::Tetrahedra ); }
    else if ( cell_type == "hexahedra"  ) { return( kvs::UnstructuredVolumeObject::Hexahedra );  }
    else
    {
        kvsMessageError( "Unknown cell type '%s'.", cell_type.c_str() );
        return( kvs::UnstructuredVolumeObject::UnknownCellType );
    }
}

/*==========================================================================*/
/**
 *  Converts to the cell type from the given element type.
 *  @param element_type [in] element type
 *  @return cell type
 */
/*==========================================================================*/
const kvs::UnstructuredVolumeObject::CellType ElementTypeToCellType(
    const kvs::AVSUcd::ElementType element_type )
{
    if ( element_type == kvs::AVSUcd::Tetrahedra  )
    {
        return( kvs::UnstructuredVolumeObject::Tetrahedra );
    }
    else if ( element_type == kvs::AVSUcd::Tetrahedra2 )
    {
        return( kvs::UnstructuredVolumeObject::QuadraticTetrahedra );
    }
    else if ( element_type == kvs::AVSUcd::Hexahedra )
    {
        return( kvs::UnstructuredVolumeObject::Hexahedra );
    }
    else if ( element_type == kvs::AVSUcd::Hexahedra2 )
    {
        return( kvs::UnstructuredVolumeObject::QuadraticHexahedra );
    }
    else
    {
        kvsMessageError( "Unknown element type." );
        return( kvs::UnstructuredVolumeObject::UnknownCellType );
    }
}

} // end of namespace


namespace kvs
{

/*===========================================================================*/
/**
 *  Constructs a new kvs::UnstructuredVolumeImporter.
 */
/*===========================================================================*/
UnstructuredVolumeImporter::UnstructuredVolumeImporter( void )
{
}

UnstructuredVolumeImporter::UnstructuredVolumeImporter( const std::string& filename )
{
    if ( kvs::KVSMLObjectUnstructuredVolume::CheckFileExtension( filename ) )
    {
        kvs::KVSMLObjectUnstructuredVolume* file_format = new kvs::KVSMLObjectUnstructuredVolume( filename );
        if( !file_format )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            return;
        }

        if( file_format->isFailure() )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            delete file_format;
            return;
        }

        this->import( file_format );
        delete file_format;
    }
    else if ( kvs::AVSUcd::CheckFileExtension( filename ) )
    {
        kvs::AVSUcd* file_format = new kvs::AVSUcd( filename );
        if( !file_format )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            return;
        }

        if( file_format->isFailure() )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            delete file_format;
            return;
        }

        this->import( file_format );
        delete file_format;
    }
    else if ( kvs::AVSField::CheckFileExtension( filename ) )
    {
        kvs::AVSField* file_format = new kvs::AVSField( filename );
        if( !file_format )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            return;
        }

        if( file_format->isFailure() )
        {
            kvsMessageError("Cannot read '%s'.",filename.c_str());
            delete file_format;
            return;
        }

        this->import( file_format );
        delete file_format;
    }
    else
    {
        kvsMessageError("Cannot import '%'.",filename.c_str());
        return;
    }

    BaseClass::m_is_success = true;
}

/*==========================================================================*/
/**
 *  Constructs a new kvs::UnstructuredVolumeImporter and import an object.
 *  @param file_format [in] pointer to the file format data
 */
/*==========================================================================*/
UnstructuredVolumeImporter::UnstructuredVolumeImporter( const kvs::FileFormatBase* file_format )
{
    this->exec( file_format );
}

/*==========================================================================*/
/**
 *  Destroys the kvs::UnstructuredVolumeImporter.
 */
/*==========================================================================*/
UnstructuredVolumeImporter::~UnstructuredVolumeImporter( void )
{
}

/*===========================================================================*/
/**
 *  Imports a kvs::UnstructuredVolumeObject from the file format data.
 *  @param  file_format [in] pointer to the file format data
 *  @return Pointer to the imported object as kvs::ObjectBase
 */
/*===========================================================================*/
kvs::ObjectBase* UnstructuredVolumeImporter::exec( const kvs::FileFormatBase* file_format )
{
    const std::string class_name = file_format->className();
    if ( class_name == "KVSMLObjectUnstructuredVolume" )
    {
        this->import( reinterpret_cast<const kvs::KVSMLObjectUnstructuredVolume*>( file_format ) );
    }
    else if ( class_name == "AVSUcd" )
    {
        this->import( reinterpret_cast<const kvs::AVSUcd*>( file_format ) );
    }
    else if ( class_name == "AVSField" )
    {
        this->import( reinterpret_cast<const kvs::AVSField*>( file_format ) );
    }
    else
    {
        kvsMessageError( "Unsupported class '%s'.", class_name.c_str() );
    }

    return( this );
}

/*==========================================================================*/
/**
 *  Import from the KVSML format data.
 *  @param kvsml [in] pointer to the KVSML format data
 */
/*==========================================================================*/
void UnstructuredVolumeImporter::import( const kvs::KVSMLObjectUnstructuredVolume* kvsml )
{
    if ( kvsml->objectTag().hasExternalCoord() )
    {
        const kvs::Vector3f min_coord( kvsml->objectTag().minExternalCoord() );
        const kvs::Vector3f max_coord( kvsml->objectTag().maxExternalCoord() );
        SuperClass::setMinMaxExternalCoords( min_coord, max_coord );
    }

    if ( kvsml->objectTag().hasObjectCoord() )
    {
        const kvs::Vector3f min_coord( kvsml->objectTag().minObjectCoord() );
        const kvs::Vector3f max_coord( kvsml->objectTag().maxObjectCoord() );
        SuperClass::setMinMaxObjectCoords( min_coord, max_coord );
    }

    SuperClass::setVeclen( kvsml->veclen() );
    SuperClass::setNNodes( kvsml->nnodes() );
    SuperClass::setNCells( kvsml->ncells() );
    SuperClass::setCellType( ::StringToCellType( kvsml->cellType() ) );
    SuperClass::setCoords( kvsml->coords() );
    SuperClass::setConnections( kvsml->connections() );
    SuperClass::setValues( kvsml->values() );
    SuperClass::updateMinMaxCoords();
    SuperClass::updateMinMaxValues();

    m_is_success = true;
}

/*==========================================================================*/
/**
 *  Import from the AVS UCD format data.
 *  @param ucd [in] pointer to the AVS UCD format data
 */
/*==========================================================================*/
void UnstructuredVolumeImporter::import( const kvs::AVSUcd* ucd )
{
    SuperClass::setVeclen( ucd->veclens()[ ucd->componentID() ] );
    SuperClass::setNNodes( ucd->nnodes() );
    SuperClass::setNCells( ucd->nelements() );
    SuperClass::setCellType( ::ElementTypeToCellType( ucd->elementType() ) );
    SuperClass::setCoords( ucd->coords() );
    SuperClass::setConnections( ucd->connections() );
    SuperClass::setValues( kvs::AnyValueArray( ucd->values() ) );
    SuperClass::updateMinMaxCoords();
    SuperClass::updateMinMaxValues();

    m_is_success = true;
}

void UnstructuredVolumeImporter::import( const kvs::AVSField* field )
{
    if( field->fieldType() != kvs::AVSField::Irregular )
    {
        kvsMessageError("Cannot import uniform/rectilinear type AVS field data.");
        return;
    }

    const size_t line_size  = field->dim().x();
    const size_t slice_size = field->dim().y();
    const kvs::Vector3ui ncells( field->dim() - kvs::Vector3ui( 1, 1, 1 ) );
    SuperClass::Connections connections( ncells.x() * ncells.y() * ncells.z() * 8 );

    size_t vertex_index = 0;
    size_t connection_index = 0;

    for ( size_t z = 0; z < ncells.z(); ++z )
    {
        for ( size_t y = 0; y < ncells.y(); ++y )
        {
            for ( size_t x = 0; x < ncells.x(); ++x )
            {
                const size_t local_vertex_index[8] =
                {
                    vertex_index,
                    vertex_index + 1,
                    vertex_index + line_size,
                    vertex_index + line_size + 1,
                    vertex_index + slice_size,
                    vertex_index + slice_size + 1,
                    vertex_index + slice_size + line_size,
                    vertex_index + slice_size + line_size + 1
                };

                // hexahedra-1
                connections[ connection_index++ ] = local_vertex_index[ 0 ];
                connections[ connection_index++ ] = local_vertex_index[ 1 ];
                connections[ connection_index++ ] = local_vertex_index[ 3 ];
                connections[ connection_index++ ] = local_vertex_index[ 2 ];
                connections[ connection_index++ ] = local_vertex_index[ 4 ];
                connections[ connection_index++ ] = local_vertex_index[ 5 ];
                connections[ connection_index++ ] = local_vertex_index[ 7 ];
                connections[ connection_index++ ] = local_vertex_index[ 6 ];

                vertex_index++;
            }
            vertex_index++;
        }
        vertex_index += line_size;
    }

    SuperClass::setVeclen( field->veclen() );
    SuperClass::setNNodes( field->values().size() );

    SuperClass::setNCells( ncells.x() * ncells.y() * ncells.z() );

    SuperClass::setCellType( Hexahedra );
    SuperClass::setCoords( field->coords() );

    SuperClass::setConnections( connections );

    SuperClass::setValues( field->values() );
    SuperClass::updateMinMaxCoords();
    SuperClass::updateMinMaxValues();


    m_is_success = true;
}

} // end of namespace kvs
