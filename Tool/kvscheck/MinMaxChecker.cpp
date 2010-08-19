/*****************************************************************************/
/**
 *  @file   MinMaxChecker.cpp
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
/*****************************************************************************/
#include "MinMaxChecker.h"
#include <iostream>


namespace kvscheck
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new MinMaxChecker class.
 */
/*===========================================================================*/
MinMaxChecker::MinMaxChecker( void )
{
}

/*==========================================================================*/
/**
 *  @brief  Output platform information.
 *  @param  os [in] output stream
 *  @param  checker [in] sizeof checker
 */
/*==========================================================================*/
std::ostream& operator << ( std::ostream& os, const MinMaxChecker& checker )
{
    os << "Min/Max value range:" << std::endl;
    os << "  char   = [ "
       << static_cast<int>( checker.minValue<char>() ) << ", "
       << static_cast<int>( checker.maxValue<char>() ) << " ]" << std::endl;
    os << "  uchar  = [ "
       << static_cast<unsigned int>( checker.minValue<unsigned char>() ) << ", "
       << static_cast<unsigned int>( checker.maxValue<unsigned char>() ) << " ]" << std::endl;
    os << "  short  = [ "
       << checker.minValue<short>() << ", "
       << checker.maxValue<short>() << " ]" << std::endl;
    os << "  ushort = [ "
       << checker.minValue<unsigned short>() << ", "
       << checker.maxValue<unsigned short>() << " ]" << std::endl;
    os << "  int    = [ "
       << checker.minValue<int>() << ", "
       << checker.maxValue<int>() << " ]" << std::endl;
    os << "  uint   = [ "
       << checker.minValue<unsigned int>() << ", "
       << checker.maxValue<unsigned int>() << " ]" << std::endl;
    os << "  long   = [ "
       << checker.minValue<long>() << ", "
       << checker.maxValue<long>() << " ]" << std::endl;
    os << "  ulong  = [ "
       << checker.minValue<unsigned long>() << ", "
       << checker.maxValue<unsigned long>() << " ]" << std::endl;
    os << "  float  = [ "
       << checker.minValue<float>() << ", "
       << checker.maxValue<float>() << " ]" << std::endl;
    os << "  double = [ "
       << checker.minValue<double>() << ", "
       << checker.maxValue<double>() << " ]" << std::endl;
    os << "  size_t = [ "
       << checker.minValue<size_t>() << ", "
       << checker.maxValue<size_t>() << " ]";

    return( os );
}

} // end of namespace kvscheck
