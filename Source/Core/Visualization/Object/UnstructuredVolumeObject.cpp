/****************************************************************************/
/**
 *  @file   UnstructuredVolumeObject.cpp
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
/****************************************************************************/
#include "UnstructuredVolumeObject.h"


namespace
{

/*===========================================================================*/
/**
 *  @brief  Returns the name of the cell type as string.
 *  @param  type [in] cell type
 *  @return name of the cell type
 */
/*===========================================================================*/
const std::string GetCellTypeName( const kvs::UnstructuredVolumeObject::CellType type )
{
    switch( type )
    {
    case kvs::UnstructuredVolumeObject::Tetrahedra: return "tetrahedra";
    case kvs::UnstructuredVolumeObject::Hexahedra: return "hexahedra";
    case kvs::UnstructuredVolumeObject::QuadraticTetrahedra: return "quadratic tetrahedra";
    case kvs::UnstructuredVolumeObject::QuadraticHexahedra: return "quadratic hexahedra";
    case kvs::UnstructuredVolumeObject::Pyramid: return "pyramid";
    default: return "unknown cell type";
    }
}

} // end of namespace


namespace kvs
{

/*==========================================================================*/
/**
 *  @brief  Constructs a new UnstructuredVolumeObject class.
 */
/*==========================================================================*/
UnstructuredVolumeObject::UnstructuredVolumeObject():
    kvs::VolumeObjectBase(),
    m_cell_type( UnknownCellType ),
    m_nnodes( 0 ),
    m_ncells( 0 ),
    m_connections()
{
    BaseClass::setVolumeType( Unstructured );
}

/*===========================================================================*/
/**
 *  @brief  Shallow copys.
 *  @param  object [in] unstructured volume object
 */
/*===========================================================================*/
void UnstructuredVolumeObject::shallowCopy( const UnstructuredVolumeObject& object )
{
    BaseClass::shallowCopy( object );
    m_cell_type = object.cellType();
    m_nnodes = object.numberOfNodes();
    m_ncells = object.numberOfCells();
    m_connections = object.connections();
}

/*===========================================================================*/
/**
 *  @brief  Deep copys.
 *  @param  object [in] unstructured volume object
 */
/*===========================================================================*/
void UnstructuredVolumeObject::deepCopy( const UnstructuredVolumeObject& object )
{
    BaseClass::deepCopy( object );
    m_cell_type = object.cellType();
    m_nnodes = object.numberOfNodes();
    m_ncells = object.numberOfCells();
    m_connections = object.connections().clone();
}

/*===========================================================================*/
/**
 *  @brief  Prints information of the unstructured volume object.
 *  @param  os [in] output stream
 *  @param  indent [in] indent
 */
/*===========================================================================*/
void UnstructuredVolumeObject::print( std::ostream& os, const kvs::Indent& indent ) const
{
    if ( !this->hasMinMaxValues() ) this->updateMinMaxValues();
    os << indent << "Object type : " << "unstructured volume object" << std::endl;
    BaseClass::print( os, indent );
    os << indent << "Cell type : " << ::GetCellTypeName( this->cellType() ) << std::endl;
    os << indent << "Number of nodes : " << this->numberOfNodes() << std::endl;
    os << indent << "Number of cells : " << this->numberOfCells() << std::endl;
    os << indent << "Min. value : " << this->minValue() << std::endl;
    os << indent << "Max. value : " << this->maxValue() << std::endl;
}

/*==========================================================================*/
/**
 *  @brief  Updates the min/max node coordinates.
 */
/*==========================================================================*/
void UnstructuredVolumeObject::updateMinMaxCoords()
{
    this->calculate_min_max_coords();
}

/*==========================================================================*/
/**
 *  @brief  Calculates the min/max coordinate values.
 */
/*==========================================================================*/
void UnstructuredVolumeObject::calculate_min_max_coords()
{
    kvs::Vector3f min_coord( 0.0f, 0.0f, 0.0f );
    kvs::Vector3f max_coord( 0.0f, 0.0f, 0.0f );

    const float*       coord = this->coords().data();
    const float* const end   = coord + this->coords().size();

    float x = *( coord++ );
    float y = *( coord++ );
    float z = *( coord++ );

    min_coord.set( x, y, z );
    max_coord.set( x, y, z );

    while ( coord < end )
    {
        x = *( coord++ );
        y = *( coord++ );
        z = *( coord++ );

        min_coord.x() = kvs::Math::Min( min_coord.x(), x );
        min_coord.y() = kvs::Math::Min( min_coord.y(), y );
        min_coord.z() = kvs::Math::Min( min_coord.z(), z );

        max_coord.x() = kvs::Math::Max( max_coord.x(), x );
        max_coord.y() = kvs::Math::Max( max_coord.y(), y );
        max_coord.z() = kvs::Math::Max( max_coord.z(), z );
    }

    this->setMinMaxObjectCoords( min_coord, max_coord );

    if ( !( this->hasMinMaxExternalCoords() ) )
    {
        this->setMinMaxExternalCoords(
            this->minObjectCoord(),
            this->maxObjectCoord() );
    }
}

std::ostream& operator << ( std::ostream& os, const UnstructuredVolumeObject& object )
{
    if ( !object.hasMinMaxValues() ) object.updateMinMaxValues();

    os << "Object type:  " << "unstructured volume object" << std::endl;
#ifdef KVS_COMPILER_VC
#if KVS_COMPILER_VERSION_LESS_OR_EQUAL( 8, 0 )
    // @TODO Cannot instance the object that is a abstract class here (error:C2259).
#endif
#else
    os << static_cast<const kvs::VolumeObjectBase&>( object ) << std::endl;
#endif
    os << "Cell type:  " << ::GetCellTypeName( object.cellType() ) << std::endl;
    os << "Number of nodes:  " << object.numberOfNodes() << std::endl;
    os << "Number of cells:  " << object.numberOfCells() << std::endl;
    os << "Min. value:  " << object.minValue() << std::endl;
    os << "Max. value:  " << object.maxValue();

    return os;
}

} // end of namespace kvs
