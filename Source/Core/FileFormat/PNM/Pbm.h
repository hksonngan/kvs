/****************************************************************************/
/**
 *  @file Pbm.h
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
#ifndef KVS_CORE_PNM_PBM_H_INCLUDE
#define KVS_CORE_PNM_PBM_H_INCLUDE

#include "../FileFormatBase.h"
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
    kvsClassName( Pbm );

public:

    typedef kvs::FileFormatBase BaseClass;
    typedef kvs::pnm::Header    Header;

private:

    Pbm::Header   m_header;  ///< header information
    size_t        m_width;   ///< width
    size_t        m_height;  ///< height
    kvs::BitArray m_data;    ///< bit pixel data

public:

    Pbm( void );

    Pbm( const size_t width, const size_t height, const kvs::BitArray& data );

    Pbm( const std::string& filename );

public:

    const Pbm::Header& header( void ) const;

public:

    const size_t width( void ) const;

    const size_t height( void ) const;

    const kvs::BitArray& data( void ) const;

public:

    const bool read( const std::string& filename );

    const bool write( const std::string& filename );

protected:

    void set_header( void );

public:

    static const bool CheckFileExtension( const std::string& filename );

    static const bool CheckFileFormat( const std::string& filename );

    friend std::ostream& operator <<( std::ostream& os, const Pbm& rhs );
};

} // end of namespace kvs

#endif // KVS_CORE_PNM_PBM_H_INCLUDE
