/****************************************************************************/
/**
 *  @file Ppm.h
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
#ifndef KVS__PPM_H_INCLUDE
#define KVS__PPM_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/ClassName>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <string>
#include <iostream>
#include "Header.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  PPM image class.
 */
/*==========================================================================*/
class Ppm : public kvs::FileFormatBase
{
    kvsClassName( kvs::Ppm );

public:

    typedef kvs::FileFormatBase BaseClass;
    typedef kvs::pnm::Header    Header;

private:

    Ppm::Header m_header; ///< header information
    size_t m_width; ///< width
    size_t m_height; ///< height
    kvs::ValueArray<kvs::UInt8> m_data; ///< pixel data

public:

    Ppm();
    Ppm( const size_t width, const size_t height, const kvs::ValueArray<kvs::UInt8>& data );
    Ppm( const std::string& filename );

public:

    const Ppm::Header& header() const;

public:

    size_t width() const;
    size_t height() const;
    const kvs::ValueArray<kvs::UInt8>& data() const;

public:

    bool read( const std::string& filename );
    bool write( const std::string& filename );

protected:

    void set_header();

public:

    static bool CheckFileExtension( const std::string& filename );
    static bool CheckFileFormat( const std::string& filename );

    friend std::ostream& operator <<( std::ostream& os, const Ppm& rhs );
};

} // end of namespace kvs

#endif // KVS__PPM_H_INCLUDE
