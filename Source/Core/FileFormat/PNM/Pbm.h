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
#include <kvs/ClassName>
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
    kvsClassName( kvs::Pbm );

public:

    typedef kvs::FileFormatBase BaseClass;
    typedef kvs::pnm::Header Header;

private:

    Pbm::Header m_header; ///< header information
    size_t m_width; ///< width
    size_t m_height; ///< height
    kvs::BitArray m_data; ///< bit pixel data

public:

    Pbm();
    Pbm( const size_t width, const size_t height, const kvs::BitArray& data );
    Pbm( const std::string& filename );

public:

    const Pbm::Header& header() const;

public:

    size_t width() const;
    size_t height() const;
    const kvs::BitArray& data() const;

public:

    bool read( const std::string& filename );
    bool write( const std::string& filename );

protected:

    void set_header();

public:

    static bool CheckFileExtension( const std::string& filename );
    static bool CheckFileFormat( const std::string& filename );

    friend std::ostream& operator <<( std::ostream& os, const Pbm& rhs );
};

} // end of namespace kvs

#endif // KVS__PBM_H_INCLUDE
