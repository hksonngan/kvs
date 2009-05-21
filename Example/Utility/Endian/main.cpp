/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::Endian functions.
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include <iostream>
#include <kvs/Endian>


/*===========================================================================*/
/**
 *  @brief  Main function.
 */
/*===========================================================================*/
int main( void )
{
    kvs::Endian::ByteOrder order = kvs::Endian::Check();
    switch( order )
    {
    case kvs::Endian::Big:
        std::cout << "Byte-order is big-endian." << std::endl;
        break;
    case kvs::Endian::Little:
        std::cout << "Byte-order is little-endian." << std::endl;
        break;
    case kvs::Endian::Unknown:
        std::cout << "Byte-order is unknown." << std::endl;
        break;
    default:
        break;
    }

    unsigned char a = 0x12;
    std::cout << "sizeof( unsigned char ): " << sizeof( unsigned char ) << std::endl;
    std::cout << "a: 0x" << std::hex << static_cast<unsigned>(a) << std::dec << std::endl;
    kvs::Endian::Swap( a );
    std::cout << "a: 0x" << std::hex << static_cast<unsigned>(a) << std::dec << std::endl;

    unsigned short b = 0x1234;
    std::cout << "sizeof( unsigned short ): " << sizeof( unsigned short ) << std::endl;
    std::cout << "b: 0x" << std::hex << b << std::dec << std::endl;
    kvs::Endian::Swap( b );
    std::cout << "b: 0x" << std::hex << b << std::dec << std::endl;

    unsigned int c = 0x12345678;
    std::cout << "sizeof( unsigned int ): " << sizeof( unsigned int ) << std::endl;
    std::cout << "c: 0x" << std::hex << c << std::dec << std::endl;
    kvs::Endian::Swap( c );
    std::cout << "c: 0x" << std::hex << c << std::dec << std::endl;

    unsigned long d = 0x12345678;
    std::cout << "sizeof( unsigned long ): " << sizeof( unsigned long ) << std::endl;
    std::cout << "d: 0x" << std::hex << d << std::dec << std::endl;
    kvs::Endian::Swap( d );
    std::cout << "d: 0x" << std::hex << d << std::dec << std::endl;

    return 0;
}
