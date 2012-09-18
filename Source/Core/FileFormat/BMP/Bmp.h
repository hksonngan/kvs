/****************************************************************************/
/**
 *  @file Bmp.h
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
#ifndef KVS__BMP_H_INCLUDE
#define KVS__BMP_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/ClassName>
#include <kvs/Type>
#include <kvs/ValueArray>
#include <kvs/Indent>
#include <iostream>
#include <fstream>
#include "FileHeader.h"
#include "InfoHeader.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Bitmap image class.
 */
/*==========================================================================*/
class Bmp : public kvs::FileFormatBase
{
public:

    typedef kvs::FileFormatBase BaseClass;
    typedef kvs::bmp::FileHeader FileHeader;
    typedef kvs::bmp::InfoHeader InfoHeader;

private:

    Bmp::FileHeader m_file_header; ///< bitmap file header
    Bmp::InfoHeader m_info_header; ///< bitmap information header
    size_t m_width; ///< width
    size_t m_height; ///< height
    size_t m_bpp; ///< bits per pixel
    kvs::ValueArray<kvs::UInt8> m_data; ///< pixel data

public:

    static bool CheckFileExtension( const std::string& filename );
    static bool CheckFileFormat( const std::string& filename );

public:

    Bmp();
    Bmp( const size_t width, const size_t height, const kvs::ValueArray<kvs::UInt8>& data );
    Bmp( const std::string& filename );

    const Bmp::FileHeader& fileHeader() const;
    const Bmp::InfoHeader& infoHeader() const;
    size_t width() const;
    size_t height() const;
    size_t bitsPerPixel() const;
    kvs::ValueArray<kvs::UInt8> data() const;

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );

protected:

    void set_header();
    void skip_header_and_pallete( std::ifstream& ifs );
};

} // end of namespace kvs

#endif // KVS__BMP_H_INCLUDE
