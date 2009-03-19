/****************************************************************************/
/**
 *  @file AnyValue.h
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
#ifndef KVS_CORE_ANY_VALUE_H_INCLUDE
#define KVS_CORE_ANY_VALUE_H_INCLUDE

#include <iostream>
#include <typeinfo>
#include <cstring>
#include "ClassName.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Any type value class.
 */
/*==========================================================================*/
class AnyValue
{
    kvsClassName_without_virtual( AnyValue );

public:

    class TypeInfo
    {
    public:

        virtual ~TypeInfo( void );

    public:

        virtual const std::type_info& type( void ) const = 0;

        virtual const char* typeName( void ) const = 0;

        virtual TypeInfo* clone( void ) const = 0;
    };

    template<typename T>
    class SetTypeInfo
        : public TypeInfo
    {
    public:

        const std::type_info& type( void ) const;

        const char* typeName( void ) const;

        TypeInfo* clone( void ) const;
    };

private:

    union value_type
    {
        char           c;  ///< char type value
        unsigned char  uc; ///< unsigned char type value
        short          s;  ///< short type value
        unsigned short us; ///< unsigned short type value
        int            i;  ///< int type value
        unsigned int   ui; ///< unsigned int type value
        long           l;  ///< long type value
        unsigned long  ul; ///< unsigned long type value
        float          f;  ///< float type value
        double         d;  ///< double type value
    };

    value_type m_value;     ///< value
    TypeInfo*  m_type_info; ///< value type information

public:

    AnyValue( void );

    template<typename T>
    AnyValue( const T value );

    AnyValue( const AnyValue& other );

    ~AnyValue( void );

public:

    template<typename T>
    AnyValue& operator =( const T& value );

    AnyValue& operator =( const AnyValue& rhs );

    template<typename T>
    operator T () const;

    friend std::ostream& operator << ( std::ostream& os, const AnyValue& rhs );

public:

    const TypeInfo* typeInfo( void ) const;

private:

    template<typename T>
    void set_value( const T& value );

    template<typename T>
    const T get_value( void ) const;
};

template<typename T>
inline const std::type_info& AnyValue::SetTypeInfo<T>::type( void ) const
{
    return( typeid( T ) );
}

template<typename T>
inline AnyValue::TypeInfo* AnyValue::SetTypeInfo<T>::clone( void ) const
{
    return( new SetTypeInfo<T>() );
}

template<typename T>
AnyValue::AnyValue( const T value )
    : m_type_info( new SetTypeInfo<T> )
{
    this->set_value<T>( value );
}

template<typename T>
AnyValue& AnyValue::operator =( const T& value )
{
    if ( m_type_info ) { delete m_type_info; }
    m_type_info = new SetTypeInfo<T>();

    this->set_value<T>( value );

    return( *this );
}

template<typename T>
AnyValue::operator T () const
{
    return( this->get_value<T>() );
}

template<typename T>
void AnyValue::set_value( const T& value )
{
    const std::type_info& type = typeid(T);
    if (      type == typeid( char ) )           { m_value.c  = value; }
    else if ( type == typeid( unsigned char ) )  { m_value.uc = value; }
    else if ( type == typeid( short ) )          { m_value.s  = value; }
    else if ( type == typeid( unsigned short ) ) { m_value.us = value; }
    else if ( type == typeid( int ) )            { m_value.i  = value; }
    else if ( type == typeid( unsigned int ) )   { m_value.ui = value; }
    else if ( type == typeid( long ) )           { m_value.l  = value; }
    else if ( type == typeid( unsigned long ) )  { m_value.ul = value; }
    else if ( type == typeid( float ) )          { m_value.f  = value; }
    else if ( type == typeid( double ) )         { m_value.d  = value; }
}

template<typename T>
const T AnyValue::get_value( void ) const
{
    const std::type_info& type = m_type_info->type();
    if (      type == typeid( char ) )           { return( static_cast<T>(m_value.c) );  }
    else if ( type == typeid( unsigned char ) )  { return( static_cast<T>(m_value.uc) ); }
    else if ( type == typeid( short ) )          { return( static_cast<T>(m_value.s) );  }
    else if ( type == typeid( unsigned short ) ) { return( static_cast<T>(m_value.us) ); }
    else if ( type == typeid( int ) )            { return( static_cast<T>(m_value.i) );  }
    else if ( type == typeid( unsigned int ) )   { return( static_cast<T>(m_value.ui) ); }
    else if ( type == typeid( long ) )           { return( static_cast<T>(m_value.l) );  }
    else if ( type == typeid( unsigned long ) )  { return( static_cast<T>(m_value.ul) ); }
    else if ( type == typeid( float ) )          { return( static_cast<T>(m_value.f) );  }
    else if ( type == typeid( double ) )         { return( static_cast<T>(m_value.d) );  }

    return( T( 0 ) );
}

} // end of namespace kvs

#endif // KVS_CORE_ANY_VALUE_H_INCLUDE
