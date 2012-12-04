/****************************************************************************/
/**
 *  @file VolumeObjectBase.cpp
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
#include "VolumeObjectBase.h"


namespace kvs
{

kvs::VolumeObjectBase* VolumeObjectBase::DownCast( kvs::ObjectBase* object )
{
    const kvs::ObjectBase::ObjectType type = object->objectType();
    if ( type != kvs::ObjectBase::Volume )
    {
        kvsMessageError("Input object is not a volume object.");
        return( NULL );
    }

    kvs::VolumeObjectBase* volume = static_cast<kvs::VolumeObjectBase*>( object );

    return( volume );
}

const kvs::VolumeObjectBase* VolumeObjectBase::DownCast( const kvs::ObjectBase* object )
{
    return( VolumeObjectBase::DownCast( const_cast<kvs::ObjectBase*>( object ) ) );
}

/*==========================================================================*/
/**
 *  Constructs a new empty VolumeObjectBase.
 */
/*==========================================================================*/
VolumeObjectBase::VolumeObjectBase()
    : m_veclen( 0 )
    , m_has_min_max_values( false )
    , m_min_value( 0.0 )
    , m_max_value( 0.0 )
{
}

std::ostream& operator << ( std::ostream& os, const kvs::VolumeObjectBase& object )
{
#ifdef KVS_COMPILER_VC
#if KVS_COMPILER_VERSION_LESS_OR_EQUAL( 8, 0 )
    // @TODO Cannot instance the object that is a abstract class here (error:C2259).
#endif
#else
    os << static_cast<const kvs::ObjectBase&>( object ) << std::endl;
#endif

    const std::ios_base::fmtflags flags( os.flags() );
    os << "Veclen:  " << object.veclen() << std::endl;
    os.setf( std::ios::boolalpha );
    os << "Set of min/max value:  " << object.hasMinMaxValues() << std::endl;
    os.unsetf( std::ios::boolalpha );
    os << "Min value:  " << object.minValue() << std::endl;
    os << "Max value:  " << object.maxValue();
    os.flags( flags );

    return( os );
}

/*==========================================================================*/
/**
 *  Sets data label.
 */
/*==========================================================================*/
void VolumeObjectBase::setLabel( const std::string& label )
{
    m_label = label;
}

/*==========================================================================*/
/**
 *  Sets the vector length.
 */
/*==========================================================================*/
void VolumeObjectBase::setVeclen( const size_t veclen )
{
    m_veclen = veclen;
}

/*==========================================================================*/
/**
 *  Sets the coordinate array.
 *
 *  @param coords [in] Coordinate array.
 */
/*==========================================================================*/
void VolumeObjectBase::setCoords( const Coords& coords )
{
    m_coords = coords;
}

/*==========================================================================*/
/**
 *  Sets the value array.
 *
 *  @param values [in] Value array.
 */
/*==========================================================================*/
void VolumeObjectBase::setValues( const Values& values )
{
    m_values = values;
}

/*==========================================================================*/
/**
 *  Sets the min/max values.
 *  @param min_value [in] Minimum value.
 *  @param max_value [in] Maximum value.
 */
/*==========================================================================*/
void VolumeObjectBase::setMinMaxValues(
    const kvs::Real64 min_value,
    const kvs::Real64 max_value ) const
{
    m_min_value          = min_value;
    m_max_value          = max_value;
    m_has_min_max_values = true;
}

kvs::ObjectBase::ObjectType VolumeObjectBase::objectType() const
{
    return( kvs::ObjectBase::Volume );
}

const std::string& VolumeObjectBase::label() const
{
    return( m_label );
}

/*==========================================================================*/
/**
 *  Returns the vector length.
 */
/*==========================================================================*/
size_t VolumeObjectBase::veclen() const
{
    return( m_veclen );
}

/*==========================================================================*/
/**
 *  Returns the coord array.
 */
/*==========================================================================*/
const VolumeObjectBase::Coords& VolumeObjectBase::coords() const
{
    return( m_coords );
}

/*==========================================================================*/
/**
 *  Returns the value array.
 */
/*==========================================================================*/
const VolumeObjectBase::Values& VolumeObjectBase::values() const
{
    return( m_values );
}

/*==========================================================================*/
/**
 *  Returns true if this class has the min/max values; otherwise returns false.
 *
 *  @return Whether this class has the min/max values or not.
 */
/*==========================================================================*/
bool VolumeObjectBase::hasMinMaxValues() const
{
    return( m_has_min_max_values );
}

/*==========================================================================*/
/**
 *  Returns the minimum value.
 *
 *  @return Minimum value.
 */
/*==========================================================================*/
kvs::Real64 VolumeObjectBase::minValue() const
{
    return( m_min_value );
}

/*==========================================================================*/
/**
 *  Returns the maximum value.
 *
 *  @return Maximum value.
 */
/*==========================================================================*/
kvs::Real64 VolumeObjectBase::maxValue() const
{
    return( m_max_value );
}

/*==========================================================================*/
/**
 *  Update the min/max node value.
 */
/*==========================================================================*/
void VolumeObjectBase::updateMinMaxValues() const
{
    const std::type_info& type = m_values.typeInfo()->type();
    if (      type == typeid( kvs::Int8   ) ) { this->calculate_min_max_values<kvs::Int8  >(); }
    else if ( type == typeid( kvs::Int16  ) ) { this->calculate_min_max_values<kvs::Int16 >(); }
    else if ( type == typeid( kvs::Int32  ) ) { this->calculate_min_max_values<kvs::Int32 >(); }
    else if ( type == typeid( kvs::Int64  ) ) { this->calculate_min_max_values<kvs::Int64 >(); }
    else if ( type == typeid( kvs::UInt8  ) ) { this->calculate_min_max_values<kvs::UInt8 >(); }
    else if ( type == typeid( kvs::UInt16 ) ) { this->calculate_min_max_values<kvs::UInt16>(); }
    else if ( type == typeid( kvs::UInt32 ) ) { this->calculate_min_max_values<kvs::UInt32>(); }
    else if ( type == typeid( kvs::UInt64 ) ) { this->calculate_min_max_values<kvs::UInt64>(); }
    else if ( type == typeid( kvs::Real32 ) ) { this->calculate_min_max_values<kvs::Real32>(); }
    else if ( type == typeid( kvs::Real64 ) ) { this->calculate_min_max_values<kvs::Real64>(); }
}

void VolumeObjectBase::shallowCopy( const VolumeObjectBase& object )
{
    BaseClass::operator=( object );
    m_has_min_max_values = object.hasMinMaxValues();
    m_min_value = object.minValue();
    m_max_value = object.maxValue();
    m_label = object.label();
    m_veclen = object.veclen();
    m_coords = object.coords();
    m_values = object.values();
}

void VolumeObjectBase::deepCopy( const VolumeObjectBase& object )
{
    BaseClass::operator=( object );
    m_has_min_max_values = object.hasMinMaxValues();
    m_min_value = object.minValue();
    m_max_value = object.maxValue();
    m_label = object.label();
    m_veclen = object.veclen();
    m_coords = object.coords().clone();
    m_values = object.values().clone();
}

} // end of namespace kvs
