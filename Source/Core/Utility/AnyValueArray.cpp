/****************************************************************************/
/**
 *  @file AnyValueArray.cpp
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
#include "AnyValueArray.h"


namespace kvs
{

AnyValueArray::AnyValueArray( void )
    : m_counter( 0 )
    , m_type_info( 0 )
    , m_size_of_value( 0 )
    , m_nvalues( 0 )
    , m_values( 0 )
{
    this->create_counter();
}

AnyValueArray::AnyValueArray( const AnyValueArray& other )
    : m_counter( 0 )
    , m_type_info( 0 )
    , m_size_of_value( 0 )
    , m_nvalues( 0 )
    , m_values( 0 )
{
    this->shallowCopy( other );
}

AnyValueArray::~AnyValueArray( void )
{
    this->deallocate();
}

template<> AnyValueArray::AnyValueArray( const char* values, size_t nvalues );
template<> AnyValueArray::AnyValueArray( const unsigned char* values, size_t nvalues );
template<> AnyValueArray::AnyValueArray( const short* values, size_t nvalues );
template<> AnyValueArray::AnyValueArray( const unsigned short* values, size_t nvalues );
template<> AnyValueArray::AnyValueArray( const int* values, size_t nvalues );
template<> AnyValueArray::AnyValueArray( const unsigned int* values, size_t nvalues );
template<> AnyValueArray::AnyValueArray( const long* values, size_t nvalues );
template<> AnyValueArray::AnyValueArray( const unsigned long* values, size_t nvalues );
template<> AnyValueArray::AnyValueArray( const float* values, size_t nvalues );
template<> AnyValueArray::AnyValueArray( const double* values, size_t nvalues );

template<> AnyValueArray::AnyValueArray( const std::vector<char>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<unsigned char>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<short>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<unsigned short>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<int>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<unsigned int>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<long>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<unsigned long>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<float>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<double>& values );

template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<char>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<unsigned char>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<short>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<unsigned short>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<int>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<unsigned int>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<long>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<unsigned long>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<float>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<double>& values );

template<> char&           AnyValueArray::at<char>( unsigned int index );
template<> unsigned char&  AnyValueArray::at<unsigned char>( unsigned int index );
template<> short&          AnyValueArray::at<short>( unsigned int index );
template<> unsigned short& AnyValueArray::at<unsigned short>( unsigned int index );
template<> int&            AnyValueArray::at<int>( unsigned int index );
template<> unsigned int&   AnyValueArray::at<unsigned int>( unsigned int index );
template<> long&           AnyValueArray::at<long>( unsigned int index );
template<> unsigned long&  AnyValueArray::at<unsigned long>( unsigned int index );
template<> float&          AnyValueArray::at<float>( unsigned int index );
template<> double&         AnyValueArray::at<double>( unsigned int index );

template<> const char&           AnyValueArray::at<char>( unsigned int index ) const;
template<> const unsigned char&  AnyValueArray::at<unsigned char>( unsigned int index ) const;
template<> const short&          AnyValueArray::at<short>( unsigned int index ) const ;
template<> const unsigned short& AnyValueArray::at<unsigned short>( unsigned int index ) const;
template<> const int&            AnyValueArray::at<int>( unsigned int index ) const;
template<> const unsigned int&   AnyValueArray::at<unsigned int>( unsigned int index ) const;
template<> const long&           AnyValueArray::at<long>( unsigned int index ) const;
template<> const unsigned long&  AnyValueArray::at<unsigned long>( unsigned int index ) const;
template<> const float&          AnyValueArray::at<float>( unsigned int index ) const;
template<> const double&         AnyValueArray::at<double>( unsigned int index ) const;

template<> const char*           AnyValueArray::pointer<char>( void ) const;
template<> const unsigned char*  AnyValueArray::pointer<unsigned char>( void ) const;
template<> const short*          AnyValueArray::pointer<short>( void ) const;
template<> const unsigned short* AnyValueArray::pointer<unsigned short>( void ) const;
template<> const int*            AnyValueArray::pointer<int>( void ) const;
template<> const unsigned int*   AnyValueArray::pointer<unsigned int>( void ) const;
template<> const long*           AnyValueArray::pointer<long>( void ) const;
template<> const unsigned long*  AnyValueArray::pointer<unsigned long>( void ) const;
template<> const float*          AnyValueArray::pointer<float>( void ) const;
template<> const double*         AnyValueArray::pointer<double>( void ) const;

template<> char*           AnyValueArray::pointer<char>( void );
template<> unsigned char*  AnyValueArray::pointer<unsigned char>( void );
template<> short*          AnyValueArray::pointer<short>( void );
template<> unsigned short* AnyValueArray::pointer<unsigned short>( void );
template<> int*            AnyValueArray::pointer<int>( void );
template<> unsigned int*   AnyValueArray::pointer<unsigned int>( void );
template<> long*           AnyValueArray::pointer<long>( void );
template<> unsigned long*  AnyValueArray::pointer<unsigned long>( void );
template<> float*          AnyValueArray::pointer<float>( void );
template<> double*         AnyValueArray::pointer<double>( void );

template<> void* AnyValueArray::allocate<char>( size_t nvalues );
template<> void* AnyValueArray::allocate<unsigned char>( size_t nvalues );
template<> void* AnyValueArray::allocate<short>( size_t nvalues );
template<> void* AnyValueArray::allocate<unsigned short>( size_t nvalues );
template<> void* AnyValueArray::allocate<int>( size_t nvalues );
template<> void* AnyValueArray::allocate<unsigned int>( size_t nvalues );
template<> void* AnyValueArray::allocate<long>( size_t nvalues );
template<> void* AnyValueArray::allocate<unsigned long>( size_t nvalues );
template<> void* AnyValueArray::allocate<float>( size_t nvalues );
template<> void* AnyValueArray::allocate<double>( size_t nvalues );

template<> void AnyValueArray::shallowCopy<char>( const kvs::ValueArray<char>& values );
template<> void AnyValueArray::shallowCopy<unsigned char>( const kvs::ValueArray<unsigned char>& values );
template<> void AnyValueArray::shallowCopy<short>( const kvs::ValueArray<short>& values );
template<> void AnyValueArray::shallowCopy<unsigned short>( const kvs::ValueArray<unsigned short>& values );
template<> void AnyValueArray::shallowCopy<int>( const kvs::ValueArray<int>& values );
template<> void AnyValueArray::shallowCopy<unsigned int>( const kvs::ValueArray<unsigned int>& values );
template<> void AnyValueArray::shallowCopy<long>( const kvs::ValueArray<long>& values );
template<> void AnyValueArray::shallowCopy<unsigned long>( const kvs::ValueArray<unsigned long>& values );
template<> void AnyValueArray::shallowCopy<float>( const kvs::ValueArray<float>& values );
template<> void AnyValueArray::shallowCopy<double>( const kvs::ValueArray<double>& values );

template<> void AnyValueArray::deepCopy<char>( const char* values, size_t nvalues );
template<> void AnyValueArray::deepCopy<unsigned char>( const unsigned char* values, size_t nvalues );
template<> void AnyValueArray::deepCopy<short>( const short* values, size_t nvalues );
template<> void AnyValueArray::deepCopy<unsigned short>( const unsigned short* values, size_t nvalues );
template<> void AnyValueArray::deepCopy<int>( const int* values, size_t nvalues );
template<> void AnyValueArray::deepCopy<unsigned int>( const unsigned int* values, size_t nvalues );
template<> void AnyValueArray::deepCopy<long>( const long* values, size_t nvalues );
template<> void AnyValueArray::deepCopy<unsigned long>( const unsigned long* values, size_t nvalues );
template<> void AnyValueArray::deepCopy<float>( const float* values, size_t nvalues );
template<> void AnyValueArray::deepCopy<double>( const double* values, size_t nvalues );

} // end of namespace kvs
