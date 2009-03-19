/****************************************************************************/
/**
 *  @file AnyValue.cpp
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
#include "AnyValue.h"


namespace kvs
{

AnyValue::TypeInfo::~TypeInfo( void )
{
}

template<>
const char* AnyValue::SetTypeInfo<char>::typeName( void ) const
{
    return( "char" );
}

template<>
const char* AnyValue::SetTypeInfo<unsigned char>::typeName( void ) const
{
    return( "unsigned char" );
}

template<>
const char* AnyValue::SetTypeInfo<short>::typeName( void ) const
{
    return( "short" );
}

template<>
const char* AnyValue::SetTypeInfo<unsigned short>::typeName( void ) const
{
    return( "unsigned short" );
}

template<>
const char* AnyValue::SetTypeInfo<int>::typeName( void ) const
{
    return( "int" );
}

template<>
const char* AnyValue::SetTypeInfo<unsigned int>::typeName( void ) const
{
    return( "unsigned int" );
}

template<>
const char* AnyValue::SetTypeInfo<long>::typeName( void ) const
{
    return( "long" );
}

template<>
const char* AnyValue::SetTypeInfo<unsigned long>::typeName( void ) const
{
    return( "unsigned long" );
}

template<>
const char* AnyValue::SetTypeInfo<float>::typeName( void ) const
{
    return( "float" );
}

template<>
const char* AnyValue::SetTypeInfo<double>::typeName( void ) const
{
    return( "double" );
}

AnyValue::AnyValue( void )
    : m_type_info( NULL )
{
    memset( &m_value, 0, sizeof( value_type ) );
}

AnyValue::AnyValue( const AnyValue& other )
    : m_value( other.m_value )
    , m_type_info( other.m_type_info ? other.m_type_info->clone() : NULL )
{
}

AnyValue::~AnyValue( void )
{
    if ( m_type_info ) { delete m_type_info; }
}

AnyValue& AnyValue::operator =( const AnyValue& rhs )
{
    m_value = rhs.m_value;

    if ( m_type_info ) { delete m_type_info; }
    m_type_info = rhs.m_type_info ? rhs.m_type_info->clone() : NULL;

    return( *this );
}

std::ostream& operator << ( std::ostream& os, const AnyValue& rhs )
{
    const std::type_info& type = rhs.m_type_info->type();
    if (      type == typeid( char ) )           { os << rhs.m_value.c;  }
    else if ( type == typeid( unsigned char ) )  { os << rhs.m_value.uc; }
    else if ( type == typeid( short ) )          { os << rhs.m_value.s;  }
    else if ( type == typeid( unsigned short ) ) { os << rhs.m_value.us; }
    else if ( type == typeid( int ) )            { os << rhs.m_value.i;  }
    else if ( type == typeid( unsigned int ) )   { os << rhs.m_value.ui; }
    else if ( type == typeid( long ) )           { os << rhs.m_value.l;  }
    else if ( type == typeid( unsigned long ) )  { os << rhs.m_value.ul; }
    else if ( type == typeid( float ) )          { os << rhs.m_value.f;  }
    else if ( type == typeid( double ) )         { os << rhs.m_value.d;  }

    return( os );
}

const AnyValue::TypeInfo* AnyValue::typeInfo( void ) const
{
    return( m_type_info );
}

template<> AnyValue::AnyValue( const char& value );
template<> AnyValue::AnyValue( const unsigned char& value );
template<> AnyValue::AnyValue( const short& value );
template<> AnyValue::AnyValue( const unsigned short& value );
template<> AnyValue::AnyValue( const int& value );
template<> AnyValue::AnyValue( const unsigned int& value );
template<> AnyValue::AnyValue( const long& value );
template<> AnyValue::AnyValue( const unsigned long& value );
template<> AnyValue::AnyValue( const float& value );
template<> AnyValue::AnyValue( const double& value );

template<> AnyValue& AnyValue::operator =( const char& value );
template<> AnyValue& AnyValue::operator =( const unsigned char& value );
template<> AnyValue& AnyValue::operator =( const short& value );
template<> AnyValue& AnyValue::operator =( const unsigned short& value );
template<> AnyValue& AnyValue::operator =( const int& value );
template<> AnyValue& AnyValue::operator =( const unsigned int& value );
template<> AnyValue& AnyValue::operator =( const long& value );
template<> AnyValue& AnyValue::operator =( const unsigned long& value );
template<> AnyValue& AnyValue::operator =( const float& value );
template<> AnyValue& AnyValue::operator =( const double& value );

template<> AnyValue::operator char () const;
template<> AnyValue::operator unsigned char () const;
template<> AnyValue::operator short () const;
template<> AnyValue::operator unsigned short () const;
template<> AnyValue::operator int () const;
template<> AnyValue::operator unsigned int () const;
template<> AnyValue::operator long () const;
template<> AnyValue::operator unsigned long () const;
template<> AnyValue::operator float () const;
template<> AnyValue::operator double () const;

} // end of namespace kvs
