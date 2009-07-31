/****************************************************************************/
/**
 *  @file StructuredVolumeImporter.cpp
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
#include "StructuredVolumeImporter.h"
#include <kvs/AVSField>
#include <kvs/Message>
#include <kvs/Vector3>


namespace
{

/*==========================================================================*/
/**
 *  Converts to the grid type from the given string.
 *  @param grid_type [in] grid type string
 *  @return grid type
 */
/*==========================================================================*/
const kvs::StructuredVolumeObject::GridType StringToGridType( const std::string& grid_type )
{
    if (      grid_type == "uniform"     ) { return( kvs::StructuredVolumeObject::Uniform );     }
    else if ( grid_type == "rectilinear" ) { return( kvs::StructuredVolumeObject::Rectilinear ); }
    else if ( grid_type == "curvilinear" ) { return( kvs::StructuredVolumeObject::Curvilinear ); }
    else
    {
        kvsMessageError( "Unknown grid type '%s'.", grid_type.c_str() );
        return( kvs::StructuredVolumeObject::UnknownGridType );
    }
}

} // end of namespace


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructs a new kvs::StructuredVolumeImporter.
 */
/*==========================================================================*/
StructuredVolumeImporter::StructuredVolumeImporter( void )
{
}

StructuredVolumeImporter::StructuredVolumeImporter( const std::string& filename )
{
    if ( kvs::KVSMLObjectStructuredVolume::CheckFileExtension( filename ) )
    {
        kvs::KVSMLObjectStructuredVolume* file_format = new kvs::KVSMLObjectStructuredVolume( filename );
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

//    BaseClass::m_is_success = true;
}

/*==========================================================================*/
/**
 *  Constructs a new kvs::StructuredVolumeImporter and import an object.
 *  @param file_format [in] pointer to the file format data
 */
/*==========================================================================*/
StructuredVolumeImporter::StructuredVolumeImporter( const kvs::FileFormatBase* file_format )
{
    if ( !this->exec( file_format ) ) BaseClass::m_is_success = true;
}

/*==========================================================================*/
/**
 *  Destroys the kvs::StructuredVolumeImporter.
 */
/*==========================================================================*/
StructuredVolumeImporter::~StructuredVolumeImporter( void )
{
}

/*===========================================================================*/
/**
 *  Imports a kvs::StructuredVolumeObject from the file format data.
 *  @param  file_format [in] pointer to the file format data
 *  @return Pointer to the imported object as kvs::ObjectBase
 */
/*===========================================================================*/
kvs::ObjectBase* StructuredVolumeImporter::exec( const kvs::FileFormatBase* file_format )
{
    const std::string class_name( file_format->className() );
    if ( class_name == "KVSMLObjectStructuredVolume" )
    {
        this->import( reinterpret_cast<const kvs::KVSMLObjectStructuredVolume*>( file_format ) );
    }
    else if ( class_name == "AVSField" )
    {
        this->import( reinterpret_cast<const kvs::AVSField*>( file_format ) );
    }
    else
    {
        kvsMessageError( "Unsupported class '%s'.", class_name.c_str() );
        return( NULL );
    }

    return( this );
}

/*==========================================================================*/
/**
 *  Import from the KVSML format data.
 *  @param kvsml [in] pointer to the KVSML format data
 */
/*==========================================================================*/
void StructuredVolumeImporter::import(
    const kvs::KVSMLObjectStructuredVolume* kvsml )
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

    SuperClass::setGridType( ::StringToGridType( kvsml->gridType() ) );
    SuperClass::setResolution( kvsml->resolution() );
    SuperClass::setVeclen( kvsml->veclen() );
    SuperClass::setValues( kvsml->values() );
    SuperClass::updateMinMaxCoords();

    BaseClass::m_is_success = true;
}

/*==========================================================================*/
/**
 *  Import from the AVS field format data.
 *  @param field [in] pointer to the AVS field format data
 */
/*==========================================================================*/
void StructuredVolumeImporter::import( const kvs::AVSField* field )
{
    if ( field->fieldType() != kvs::AVSField::Uniform )
    {
        kvsMessageWarning( field->fieldType() == kvs::AVSField::Uniform,
                           "'Uniform' type in kvs::AVSField format is only supported." );

        BaseClass::m_is_success = false;
    }

    if ( field->hasMinMaxExt() )
    {
        const kvs::Vector3f min_coord( field->minExt() );
        const kvs::Vector3f max_coord( field->maxExt() );

        SuperClass::setMinMaxObjectCoords( min_coord, max_coord );
        SuperClass::setMinMaxExternalCoords( min_coord, max_coord );
    }
    else
    {
        const float dim_x = static_cast<float>( field->dim().x() );
        const float dim_y = static_cast<float>( field->dim().y() );
        const float dim_z = static_cast<float>( field->dim().z() );
        const kvs::Vector3f  min_coord( 0.0f );
        const kvs::Vector3f  max_coord( dim_x - 1.0f, dim_y - 1.0f, dim_z - 1.0f );

        SuperClass::setMinMaxObjectCoords( min_coord, max_coord );
        SuperClass::setMinMaxExternalCoords( min_coord, max_coord );
    }

    SuperClass::setGridType( kvs::StructuredVolumeObject::Uniform );
    SuperClass::setVeclen( field->veclen() );
    SuperClass::setResolution( field->dim() );
    SuperClass::setValues( field->values() );

    BaseClass::m_is_success = true;
}

} // end of namespace kvs
