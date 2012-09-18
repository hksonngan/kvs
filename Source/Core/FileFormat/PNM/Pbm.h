/****************************************************************************/
/**
 *  @file Pbm.h
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
#ifndef KVS__PBM_H_INCLUDE
#define KVS__PBM_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/BitArray>
#include <kvs/Type>
#include <string>
#include "Header.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  PBM image class.
 */
/*==========================================================================*/
class Pbm : public kvs::FileFormatBase
{
public:

    typedef kvs::FileFormatBase BaseClass;
    typedef kvs::pnm::Header Header;

private:

    Pbm::Header m_header; ///< header information
    size_t m_width; ///< width
    size_t m_height; ///< height
    kvs::BitArray m_data; ///< bit pixel data

public:

    static bool CheckFileExtension( const std::string& filename );
    static bool CheckFileFormat( const std::string& filename );

public:

    Pbm();
    Pbm( const size_t width, const size_t height, const kvs::BitArray& data );
    Pbm( const std::string& filename );

    const Pbm::Header& header() const;
    size_t width() const;
    size_t height() const;
    const kvs::BitArray& data() const;

    void print( std::ostream& os, const size_t indent = 0 ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );

private:

    void set_header();
};

} // end of namespace kvs

#endif // KVS__PBM_H_INCLUDE
