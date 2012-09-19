/*****************************************************************************/
/**
 *  @file   Stl.h
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
#ifndef KVS__STL_H_INCLUDE
#define KVS__STL_H_INCLUDE

#include <iostream>
#include <fstream>
#include <string>
#include <kvs/ValueArray>
#include <kvs/FileFormatBase>
#include <kvs/Type>
#include <kvs/Indent>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  STL file format class.
 */
/*===========================================================================*/
class Stl : public kvs::FileFormatBase
{
public:

    typedef kvs::FileFormatBase BaseClass;

    enum FileType
    {
        Ascii, // ascii type
        Binary // binary type
    };

protected:

    FileType m_file_type; ///< file type
    kvs::ValueArray<kvs::Real32> m_normals; /// normal vector array
    kvs::ValueArray<kvs::Real32> m_coords; /// coordinate value array

public:

    static bool CheckExtension( const std::string& filename );

public:

    Stl();
    Stl( const std::string& filename );
    virtual ~Stl();

    FileType fileType() const;
    const kvs::ValueArray<kvs::Real32>& normals() const;
    const kvs::ValueArray<kvs::Real32>& coords() const;
    size_t ntriangles() const;

    void setFileType( const FileType file_type );
    void setNormals( const kvs::ValueArray<kvs::Real32>& normals );
    void setCoords( const kvs::ValueArray<kvs::Real32>& coords );

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );

private:

    bool is_ascii_type( FILE* ifs );
    bool read_ascii( FILE* ifs );
    bool read_binary( FILE* ifs );
    bool write_ascii( FILE* ifs );
    bool write_binary( FILE* ifs );
};

} // end of namespace kvs

#endif // KVS__STL_H_INCLUDE
