/****************************************************************************/
/**
 *  @file PlatformChecker.cpp
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
#include "PlatformChecker.h"
#include <kvs/Platform>
#include <kvs/SystemInformation>
#include <kvs/Endian>
#include <kvs/Value>


namespace kvscheck
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
PlatformChecker::PlatformChecker( void )
{
    m_name = kvs::Platform::Name();
    m_cpu  = kvs::Platform::CPUName();
}

/*==========================================================================*/
/**
 *  Returns platform name.
 */
/*==========================================================================*/
const std::string& PlatformChecker::name( void ) const
{
    return( m_name );
}

/*==========================================================================*/
/**
 *  Returns CPU name.
 */
/*==========================================================================*/
const std::string& PlatformChecker::cpu( void ) const
{
    return( m_cpu );
}

/*==========================================================================*/
/**
 *  Output platform information.
 *  @param os [in] output stream
 *  @param checker [in] platform checker
 */
/*==========================================================================*/
std::ostream& operator << ( std::ostream& os, const PlatformChecker& checker )
{
    const std::string byte_order( kvs::Endian::IsBig() ? "Big endian" : "Little endian" );

    const size_t ncores = kvs::SystemInformation::nprocessors();

#if defined( KVS_PLATFORM_CPU_64 )
    const size_t nbits = 64;
#elif defined( KVS_PLATFORM_CPU_32 )
    const size_t nbits = 32;
#else
    const size_t nbits = 0;
#endif

    os << "Platform:   " << checker.name() << std::endl;
    os << "CPU:        " << checker.cpu() << " (" << nbits << " bits)" << std::endl;
    os << "Cores:      " << ncores << " core(s)" << std::endl;
    os << "Byte-order: " << byte_order << std::endl;
    os << "Sizeof:" << std::endl;
    os << "  sizeof( char ) = " << sizeof(char) << std::endl;
    os << "  sizeof( short ) = " << sizeof(short) << std::endl;
    os << "  sizeof( int ) = " << sizeof(int) << std::endl;
    os << "  sizeof( long ) = " << sizeof(long) << std::endl;
    os << "  sizeof( float ) = " << sizeof(float) << std::endl;
    os << "  sizeof( double ) = " << sizeof(double) << std::endl;
    os << "  sizeof( size_t ) = " << sizeof(size_t) << std::endl;
    os << "Min/Max:" << std::endl;
    os << "  char [ "
       << static_cast<int>( kvs::Value<char>::Min() ) << ", "
       << static_cast<int>( kvs::Value<char>::Max() ) << " ]" << std::endl;
    os << "  uchar [ "
       << static_cast<unsigned int>( kvs::Value<unsigned char>::Min() ) << ", "
       << static_cast<unsigned int>( kvs::Value<unsigned char>::Max() ) << " ]" << std::endl;
    os << "  short [ "
       << kvs::Value<short>::Min() << ", "
       << kvs::Value<short>::Max() << " ]" << std::endl;
    os << "  ushort [ "
       << kvs::Value<unsigned short>::Min() << ", "
       << kvs::Value<unsigned short>::Max() << " ]" << std::endl;
    os << "  int [ "
       << kvs::Value<int>::Min() << ", "
       << kvs::Value<int>::Max() << " ]" << std::endl;
    os << "  uint [ "
       << kvs::Value<unsigned int>::Min() << ", "
       << kvs::Value<unsigned int>::Max() << " ]" << std::endl;
    os << "  long [ "
       << kvs::Value<long>::Min() << ", "
       << kvs::Value<long>::Max() << " ]" << std::endl;
    os << "  ulong [ "
       << kvs::Value<unsigned long>::Min() << ", "
       << kvs::Value<unsigned long>::Max() << " ]" << std::endl;
    os << "  float [ "
       << kvs::Value<float>::Min() << ", "
       << kvs::Value<float>::Max() << " ]" << std::endl;
    os << "  double [ "
       << kvs::Value<double>::Min() << ", "
       << kvs::Value<double>::Max() << " ]" << std::endl;
    os << "  size_t [ "
       << kvs::Value<size_t>::Min() << ", "
       << kvs::Value<size_t>::Max() << " ]" << std::endl;

    return( os );
}

} // end of namespace kvscheck
