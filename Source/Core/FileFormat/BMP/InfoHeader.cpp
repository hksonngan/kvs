/****************************************************************************/
/**
 *  @file InfoHeader.cpp
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
#include "InfoHeader.h"
#include <kvs/Endian>


namespace kvs
{

namespace bmp
{

InfoHeader::InfoHeader()
{
}

InfoHeader::InfoHeader( std::ifstream& ifs )
{
    this->read( ifs );
}

kvs::UInt32 InfoHeader::size() const
{
    return m_size;
}

kvs::UInt32 InfoHeader::width() const
{
    return m_width;
}

kvs::UInt32 InfoHeader::height() const
{
    return m_height;
}

kvs::UInt16 InfoHeader::nplanes() const
{
    return m_nplanes;
}

kvs::UInt16 InfoHeader::bpp() const
{
    return m_bpp;
}

kvs::UInt32 InfoHeader::compression() const
{
    return m_compression;
}

kvs::UInt32 InfoHeader::bitmapsize() const
{
    return m_bitmapsize;
}

kvs::UInt32 InfoHeader::hresolution() const
{
    return m_hresolution;
}

kvs::UInt32 InfoHeader::vresolution() const
{
    return m_vresolution;
}

kvs::UInt32 InfoHeader::colsused() const
{
    return m_colsused;
}

kvs::UInt32 InfoHeader::colsimportant() const
{
    return m_colsimportant;
}

void InfoHeader::print( std::ostream& os, const size_t indent ) const
{
    const std::string blanks( indent, ' ' );
    os << blanks << "Structure size : " << m_size << std::endl;
    os << blanks << "Image width : " << m_width << std::endl;
    os << blanks << "Image height : " << m_height << std::endl;
    os << blanks << "Number of planes : " << m_nplanes << std::endl;
    os << blanks << "Bits per pixel : " << m_bpp << std::endl;
    os << blanks << "Compression : " << m_compression << std::endl;
    os << blanks << "Size of bitmap : " << m_bitmapsize << std::endl;
    os << blanks << "Horizontal resolution : " << m_hresolution << std::endl;
    os << blanks << "Vertical resolution : " << m_vresolution << std::endl;
    os << blanks << "Number of colors : " << m_colsused << std::endl;
    os << blanks << "Number of important colors : " << m_colsimportant;
}

void InfoHeader::read( std::ifstream& ifs )
{
    BaseClass::get_value( ifs, &m_size );
    BaseClass::get_value( ifs, &m_width );
    BaseClass::get_value( ifs, &m_height );
    BaseClass::get_value( ifs, &m_nplanes );
    BaseClass::get_value( ifs, &m_bpp );
    BaseClass::get_value( ifs, &m_compression );
    BaseClass::get_value( ifs, &m_bitmapsize );
    BaseClass::get_value( ifs, &m_hresolution );
    BaseClass::get_value( ifs, &m_vresolution );
    BaseClass::get_value( ifs, &m_colsused );
    BaseClass::get_value( ifs, &m_colsimportant );
    BMP_HEADER_SWAP_BYTES;
}

void InfoHeader::write( std::ofstream& ofs )
{
    BMP_HEADER_SWAP_BYTES;
    BaseClass::put_value( ofs, m_size );
    BaseClass::put_value( ofs, m_width );
    BaseClass::put_value( ofs, m_height );
    BaseClass::put_value( ofs, m_nplanes );
    BaseClass::put_value( ofs, m_bpp );
    BaseClass::put_value( ofs, m_compression );
    BaseClass::put_value( ofs, m_bitmapsize );
    BaseClass::put_value( ofs, m_hresolution );
    BaseClass::put_value( ofs, m_vresolution );
    BaseClass::put_value( ofs, m_colsused );
    BaseClass::put_value( ofs, m_colsimportant );
    BMP_HEADER_SWAP_BYTES;
};

void InfoHeader::swap_bytes()
{
    kvs::Endian::Swap( &m_size );
    kvs::Endian::Swap( &m_width );
    kvs::Endian::Swap( &m_height );
    kvs::Endian::Swap( &m_nplanes );
    kvs::Endian::Swap( &m_bpp );
    kvs::Endian::Swap( &m_compression );
    kvs::Endian::Swap( &m_bitmapsize );
    kvs::Endian::Swap( &m_hresolution );
    kvs::Endian::Swap( &m_vresolution );
    kvs::Endian::Swap( &m_colsused );
    kvs::Endian::Swap( &m_colsimportant );
}

} // end of namesapce bmp

} // end of namespace kvs
