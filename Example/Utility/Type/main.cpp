/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::Type.
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
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <kvs/Type>


/*===========================================================================*/
/**
 *  @brief  Main function.
 */
/*===========================================================================*/
int main( void )
{
    std::cout << std::setiosflags(std::ios::boolalpha);

    // Re-defined primitive types in KVS.
    std::cout << "char == kvs::Int8 ? ";
    std::cout << ( typeid(char) == typeid(kvs::Int8) ) << std::endl;
    std::cout << "unsigned char == kvs::UInt8 ? ";
    std::cout << ( typeid(unsigned char) == typeid(kvs::UInt8) ) << std::endl;
    std::cout << "short == kvs::Int16 ? ";
    std::cout << ( typeid(short) == typeid(kvs::Int16) ) << std::endl;
    std::cout << "unsigned short == kvs::UInt16 ? ";
    std::cout << ( typeid(unsigned short) == typeid(kvs::UInt16) ) << std::endl;
    std::cout << "int == kvs::Int32 ? ";
    std::cout << ( typeid(int) == typeid(kvs::Int32) ) << std::endl;
    std::cout << "unsigned int == kvs::UInt32 ? ";
    std::cout << ( typeid(unsigned int) == typeid(kvs::UInt32) ) << std::endl;
    std::cout << "long == kvs::Int64 ? ";
    std::cout << ( typeid(int) == typeid(kvs::Int64) ) << std::endl;
    std::cout << "unsigned long == kvs::UInt64 ? ";
    std::cout << ( typeid(unsigned long) == typeid(kvs::UInt64) ) << std::endl;
    std::cout << "float == kvs::Real32 ? ";
    std::cout << ( typeid(float) == typeid(kvs::Real32) ) << std::endl;
    std::cout << "double == kvs::Real64 ? ";
    std::cout << ( typeid(double) == typeid(kvs::Real64) ) << std::endl;

    std::cout << std::endl;

    // char type.
    std::cout << "sizeof(char) == KVS_TYPE_SIZEOF_CHAR ? ";
    std::cout << ( sizeof(char) == KVS_TYPE_SIZEOF_CHAR ) << ", ";
    std::cout << "( sizeof(char) = " << sizeof(char) << ", ";
    std::cout << "KVS_TYPE_SIZEOF_CHAR = " << KVS_TYPE_SIZEOF_CHAR << " )" << std::endl;

    // short type.
    std::cout << "sizeof(short) == KVS_TYPE_SIZEOF_SHORT ? ";
    std::cout << ( sizeof(short) == KVS_TYPE_SIZEOF_SHORT ) << ", ";
    std::cout << "( sizeof(short) = " << sizeof(short) << ", ";
    std::cout << "KVS_TYPE_SIZEOF_SHORT = " << KVS_TYPE_SIZEOF_SHORT << " )" << std::endl;

    // int type.
    std::cout << "sizeof(int) == KVS_TYPE_SIZEOF_INT ? ";
    std::cout << ( sizeof(int) == KVS_TYPE_SIZEOF_INT ) << ", ";
    std::cout << "( sizeof(int) = " << sizeof(int) << ", ";
    std::cout << "KVS_TYPE_SIZEOF_INT = " << KVS_TYPE_SIZEOF_INT << " )" << std::endl;

    // long type.
    std::cout << "sizeof(long) == KVS_TYPE_SIZEOF_LONG ? ";
    std::cout << ( sizeof(long) == KVS_TYPE_SIZEOF_LONG ) << ", ";
    std::cout << "( sizeof(long) = " << sizeof(long) << ", ";
    std::cout << "KVS_TYPE_SIZEOF_LONG = " << KVS_TYPE_SIZEOF_LONG << " )" << std::endl;

    // long long type.
    std::cout << "sizeof(long long) == KVS_TYPE_SIZEOF_LONG_LONG ? ";
    std::cout << ( sizeof(long long) == KVS_TYPE_SIZEOF_LONG_LONG ) << ", ";
    std::cout << "sizeof(long long) = " << sizeof(long long) << ", "
              << "KVS_TYPE_SIZEOF_LONG_LONG = " << KVS_TYPE_SIZEOF_LONG_LONG << " )" << std::endl;

    // float type.
    std::cout << "sizeof(float) == KVS_TYPE_SIZEOF_FLOAT ? ";
    std::cout << ( sizeof(float) == KVS_TYPE_SIZEOF_FLOAT ) << ", ";
    std::cout << "( sizeof(float) = " << sizeof(float) << ", ";
    std::cout << "KVS_TYPE_SIZEOF_FLOAT = " << KVS_TYPE_SIZEOF_FLOAT << " )" << std::endl;

    // double type.
    std::cout << "sizeof(double) == KVS_TYPE_SIZEOF_DOUBLE ? ";
    std::cout << ( sizeof(double) == KVS_TYPE_SIZEOF_DOUBLE ) << ", ";
    std::cout << "( sizeof(double) = " << sizeof(double) << ", ";
    std::cout << "KVS_TYPE_SIZEOF_DOUBLE = " << KVS_TYPE_SIZEOF_DOUBLE << " )" << std::endl;

    // long double type.
    std::cout << "sizeof(long double) == KVS_TYPE_SIZEOF_LONG_DOUBLE ? ";
    std::cout << ( sizeof(long double) == KVS_TYPE_SIZEOF_LONG_DOUBLE ) << ", ";
    std::cout << "( sizeof(long double) = " << sizeof(long double) << ", ";
    std::cout << "KVS_TYPE_SIZEOF_LONG_DOUBLE = " << KVS_TYPE_SIZEOF_LONG_DOUBLE << " )" << std::endl;

    // pointer type.
    std::cout << "sizeof(void*) == KVS_TYPE_SIZEOF_POINTER ? ";
    std::cout << ( sizeof(void*) == KVS_TYPE_SIZEOF_POINTER ) << ", ";
    std::cout << "( sizeof(void*) = " << sizeof(void*) << ", ";
    std::cout << "KVS_TYPE_SIZEOF_POINTER = " << KVS_TYPE_SIZEOF_POINTER << " )" << std::endl;

    return 0;
}
