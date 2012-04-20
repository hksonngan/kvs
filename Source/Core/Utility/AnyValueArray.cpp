/****************************************************************************/
/**
 *  @file AnyValueArray.cpp
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
#include "AnyValueArray.h"


namespace kvs
{

AnyValueArray::AnyValueArray()
    : m_counter( 0 )
    , m_type_info( 0 )
    , m_size_of_value( 0 )
    , m_size( 0 )
    , m_values( 0 )
{
    this->create_counter();
}

AnyValueArray::AnyValueArray( const AnyValueArray& other )
{
    m_counter       = other.m_counter;
    m_size          = other.m_size;
    m_values        = other.m_values;

    m_type_info     = other.m_type_info->clone();
    m_size_of_value = other.m_size_of_value;

    this->ref();
}

AnyValueArray::~AnyValueArray()
{
    this->deallocate();
}


template<> AnyValueArray::AnyValueArray( const kvs::Int8* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const kvs::UInt8* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const kvs::Int16* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const kvs::UInt16* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const kvs::Int32* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const kvs::UInt32* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const kvs::Int64* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const kvs::UInt64* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const kvs::Real32* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const kvs::Real64* values, const size_t nvalues );
template<> AnyValueArray::AnyValueArray( const std::string* values, const size_t nvalues );

template<> AnyValueArray::AnyValueArray( const std::vector<kvs::Int8>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<kvs::UInt8>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<kvs::Int16>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<kvs::UInt16>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<kvs::Int32>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<kvs::UInt32>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<kvs::Int64>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<kvs::UInt64>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<kvs::Real32>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<kvs::Real64>& values );
template<> AnyValueArray::AnyValueArray( const std::vector<std::string>& values );

template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::Int8>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::UInt8>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::Int16>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::UInt16>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::Int32>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::UInt32>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::Int64>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::UInt64>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::Real32>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<kvs::Real64>& values );
template<> AnyValueArray::AnyValueArray( const kvs::ValueArray<std::string>& values );

template<> kvs::Int8&   AnyValueArray::at<kvs::Int8>( const size_t index );
template<> kvs::UInt8&  AnyValueArray::at<kvs::UInt8>( const size_t index );
template<> kvs::Int16&  AnyValueArray::at<kvs::Int16>( const size_t index );
template<> kvs::UInt16& AnyValueArray::at<kvs::UInt16>( const size_t index );
template<> kvs::Int32&  AnyValueArray::at<kvs::Int32>( const size_t index );
template<> kvs::UInt32& AnyValueArray::at<kvs::UInt32>( const size_t index );
template<> kvs::Int64&  AnyValueArray::at<kvs::Int64>( const size_t index );
template<> kvs::UInt64& AnyValueArray::at<kvs::UInt64>( const size_t index );
template<> kvs::Real32& AnyValueArray::at<kvs::Real32>( const size_t index );
template<> kvs::Real64& AnyValueArray::at<kvs::Real64>( const size_t index );
template<> std::string& AnyValueArray::at<std::string>( const size_t index );

//template<> const kvs::Int8&   AnyValueArray::at<kvs::Int8>( const size_t index ) const;
//template<> const kvs::UInt8&  AnyValueArray::at<kvs::UInt8>( const size_t index ) const;
//template<> const kvs::Int16&  AnyValueArray::at<kvs::Int16>( const size_t index ) const ;
//template<> const kvs::UInt16& AnyValueArray::at<kvs::UInt16>( const size_t index ) const;
//template<> const kvs::Int32&  AnyValueArray::at<kvs::Int32>( const size_t index ) const;
//template<> const kvs::UInt32& AnyValueArray::at<kvs::UInt32>( const size_t index ) const;
//template<> const kvs::Int64&  AnyValueArray::at<kvs::Int64>( const size_t index ) const;
//template<> const kvs::UInt64& AnyValueArray::at<kvs::UInt64>( const size_t index ) const;
//template<> const kvs::Real32& AnyValueArray::at<kvs::Real32>( const size_t index ) const;
//template<> const kvs::Real64& AnyValueArray::at<kvs::Real64>( const size_t index ) const;
//template<> const std::string& AnyValueArray::at<std::string>( const size_t index ) const;

template<> kvs::Int8   AnyValueArray::to<kvs::Int8>( const size_t index ) const;
template<> kvs::UInt8  AnyValueArray::to<kvs::UInt8>( const size_t index ) const;
template<> kvs::Int16  AnyValueArray::to<kvs::Int16>( const size_t index ) const;
template<> kvs::UInt16 AnyValueArray::to<kvs::UInt16>( const size_t index ) const;
template<> kvs::Int32  AnyValueArray::to<kvs::Int32>( const size_t index ) const;
template<> kvs::UInt32 AnyValueArray::to<kvs::UInt32>( const size_t index ) const;
template<> kvs::Int64  AnyValueArray::to<kvs::Int64>( const size_t index ) const;
template<> kvs::UInt64 AnyValueArray::to<kvs::UInt64>( const size_t index ) const;
template<> kvs::Real32 AnyValueArray::to<kvs::Real32>( const size_t index ) const;
template<> kvs::Real64 AnyValueArray::to<kvs::Real64>( const size_t index ) const;
template<> std::string AnyValueArray::to<std::string>( const size_t index ) const;

template<> const kvs::Int8*   AnyValueArray::pointer<kvs::Int8>() const;
template<> const kvs::UInt8*  AnyValueArray::pointer<kvs::UInt8>() const;
template<> const kvs::Int16*  AnyValueArray::pointer<kvs::Int16>() const;
template<> const kvs::UInt16* AnyValueArray::pointer<kvs::UInt16>() const;
template<> const kvs::Int32*  AnyValueArray::pointer<kvs::Int32>() const;
template<> const kvs::UInt32* AnyValueArray::pointer<kvs::UInt32>() const;
template<> const kvs::Int64*  AnyValueArray::pointer<kvs::Int64>() const;
template<> const kvs::UInt64* AnyValueArray::pointer<kvs::UInt64>() const;
template<> const kvs::Real32* AnyValueArray::pointer<kvs::Real32>() const;
template<> const kvs::Real64* AnyValueArray::pointer<kvs::Real64>() const;
template<> const std::string* AnyValueArray::pointer<std::string>() const;

template<> kvs::Int8*   AnyValueArray::pointer<kvs::Int8>();
template<> kvs::UInt8*  AnyValueArray::pointer<kvs::UInt8>();
template<> kvs::Int16*  AnyValueArray::pointer<kvs::Int16>();
template<> kvs::UInt16* AnyValueArray::pointer<kvs::UInt16>();
template<> kvs::Int32*  AnyValueArray::pointer<kvs::Int32>();
template<> kvs::UInt32* AnyValueArray::pointer<kvs::UInt32>();
template<> kvs::Int64*  AnyValueArray::pointer<kvs::Int64>();
template<> kvs::UInt64* AnyValueArray::pointer<kvs::UInt64>();
template<> kvs::Real32* AnyValueArray::pointer<kvs::Real32>();
template<> kvs::Real64* AnyValueArray::pointer<kvs::Real64>();
template<> std::string* AnyValueArray::pointer<std::string>();

#if KVS_ENABLE_DEPRECATED

template<> void* AnyValueArray::allocate<kvs::Int8>( const size_t nvalues );
template<> void* AnyValueArray::allocate<kvs::UInt8>( const size_t nvalues );
template<> void* AnyValueArray::allocate<kvs::Int16>( const size_t nvalues );
template<> void* AnyValueArray::allocate<kvs::UInt16>( const size_t nvalues );
template<> void* AnyValueArray::allocate<kvs::Int32>( const size_t nvalues );
template<> void* AnyValueArray::allocate<kvs::UInt32>( const size_t nvalues );
template<> void* AnyValueArray::allocate<kvs::Int64>( const size_t nvalues );
template<> void* AnyValueArray::allocate<kvs::UInt64>( const size_t nvalues );
template<> void* AnyValueArray::allocate<kvs::Real32>( const size_t nvalues );
template<> void* AnyValueArray::allocate<kvs::Real64>( const size_t nvalues );
template<> void* AnyValueArray::allocate<std::string>( const size_t nvalues );

#else

template<> void AnyValueArray::allocate<kvs::Int8>( const size_t nvalues );
template<> void AnyValueArray::allocate<kvs::UInt8>( const size_t nvalues );
template<> void AnyValueArray::allocate<kvs::Int16>( const size_t nvalues );
template<> void AnyValueArray::allocate<kvs::UInt16>( const size_t nvalues );
template<> void AnyValueArray::allocate<kvs::Int32>( const size_t nvalues );
template<> void AnyValueArray::allocate<kvs::UInt32>( const size_t nvalues );
template<> void AnyValueArray::allocate<kvs::Int64>( const size_t nvalues );
template<> void AnyValueArray::allocate<kvs::UInt64>( const size_t nvalues );
template<> void AnyValueArray::allocate<kvs::Real32>( const size_t nvalues );
template<> void AnyValueArray::allocate<kvs::Real64>( const size_t nvalues );
template<> void AnyValueArray::allocate<std::string>( const size_t nvalues );

#endif

template<> void AnyValueArray::shallowCopy<kvs::Int8>( const kvs::ValueArray<kvs::Int8>& values );
template<> void AnyValueArray::shallowCopy<kvs::UInt8>( const kvs::ValueArray<kvs::UInt8>& values );
template<> void AnyValueArray::shallowCopy<kvs::Int16>( const kvs::ValueArray<kvs::Int16>& values );
template<> void AnyValueArray::shallowCopy<kvs::UInt16>( const kvs::ValueArray<kvs::UInt16>& values );
template<> void AnyValueArray::shallowCopy<kvs::Int32>( const kvs::ValueArray<kvs::Int32>& values );
template<> void AnyValueArray::shallowCopy<kvs::UInt32>( const kvs::ValueArray<kvs::UInt32>& values );
template<> void AnyValueArray::shallowCopy<kvs::Int64>( const kvs::ValueArray<kvs::Int64>& values );
template<> void AnyValueArray::shallowCopy<kvs::UInt64>( const kvs::ValueArray<kvs::UInt64>& values );
template<> void AnyValueArray::shallowCopy<kvs::Real32>( const kvs::ValueArray<kvs::Real32>& values );
template<> void AnyValueArray::shallowCopy<kvs::Real64>( const kvs::ValueArray<kvs::Real64>& values );
template<> void AnyValueArray::shallowCopy<std::string>( const kvs::ValueArray<std::string>& values );

template<> void AnyValueArray::deepCopy<kvs::Int8>( const kvs::Int8* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<kvs::UInt8>( const kvs::UInt8* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<kvs::Int16>( const kvs::Int16* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<kvs::UInt16>( const kvs::UInt16* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<kvs::Int32>( const kvs::Int32* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<kvs::UInt32>( const kvs::UInt32* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<kvs::Int64>( const kvs::Int64* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<kvs::UInt64>( const kvs::UInt64* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<kvs::Real32>( const kvs::Real32* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<kvs::Real64>( const kvs::Real64* values, const size_t nvalues );
template<> void AnyValueArray::deepCopy<std::string>( const std::string* values, const size_t nvalues );

} // end of namespace kvs
