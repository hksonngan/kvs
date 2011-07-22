/*****************************************************************************/
/**
 *  @file   File.cpp
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
#include "File.h"
#include <cstdio>
#include <kvs/Message>
#include <kvs/Endian>


namespace kvs
{

namespace gf
{

/*===========================================================================*/
/**
 *  @brief  Construct a new File class.
 */
/*===========================================================================*/
File::File( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Construct a new File class.
 *  @param  filename [in] filename
 */
/*===========================================================================*/
File::File( const std::string filename )
{
    this->read( filename );
}

/*===========================================================================*/
/**
 *  @brief  Output File class information.
 */
/*===========================================================================*/
std::ostream& operator << ( std::ostream& os, const File& f )
{
    os << "file type header: " << f.m_file_type_header << std::endl;
    for ( size_t i = 0; i < f.m_comment_list.size(); i++ )
    {
        os << "comment[" << i << "]: " << f.m_comment_list[i];
    }

    for ( size_t i = 0; i < f.m_data_set_list.size(); i++ )
    {
        os << "data_set[" << i << "]:" << std::endl;
        os << f.m_data_set_list[i];
        if ( i != f.m_data_set_list.size() - 1 ) os << std::endl;
    }

    return( os );
}

/*===========================================================================*/
/**
 *  @brief  Return file type header.
 *  @return file type header
 */
/*===========================================================================*/
const std::string& File::fileTypeHeader( void ) const
{
    return( m_file_type_header );
}

/*===========================================================================*/
/**
 *  @brief  Return comment list.
 *  @return comment list
 */
/*===========================================================================*/
const std::vector<std::string>& File::commentList( void ) const
{
    return( m_comment_list );
}

/*===========================================================================*/
/**
 *  @brief  Return comment specified by the index.
 *  @param  index [in] index of comment list
 *  @return comment
 */
/*===========================================================================*/
const std::string& File::comment( const size_t index ) const
{
    return( m_comment_list.at( index ) );
}

/*===========================================================================*/
/**
 *  @brief  Return data set list.
 *  @return data set list
 */
/*===========================================================================*/
const std::vector<kvs::gf::DataSet>& File::dataSetList( void ) const
{
    return( m_data_set_list );
}

/*===========================================================================*/
/**
 *  @brief  Return data set specified by the index.
 *  @param  index [in] index of data set list
 *  @return data set
 */
/*===========================================================================*/
const kvs::gf::DataSet& File::dataSet( const size_t index ) const
{
    return( m_data_set_list.at( index ) );
}

/*===========================================================================*/
/**
 *  @brief  Deallocate data sets and comments.
 */
/*===========================================================================*/
void File::deallocate( void )
{
    m_file_type_header = "";

    std::vector<std::string>::iterator comment = m_comment_list.begin();
    std::vector<std::string>::const_iterator last_comment = m_comment_list.end();
    while ( comment != last_comment )
    {
        comment->assign("");
        comment++;
    }

    std::vector<kvs::gf::DataSet>::iterator data_set = m_data_set_list.begin();
    std::vector<kvs::gf::DataSet>::const_iterator last_data_set = m_data_set_list.end();
    while ( data_set != last_data_set )
    {
        data_set->deallocate();
        data_set++;
    }
}

/*===========================================================================*/
/**
 *  @brief  Read GF file.
 *  @param  filename [in] filename
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool File::read( const std::string filename )
{
    FILE* fp = fopen( filename.c_str(), "r" );
    if ( !fp )
    {
        kvsMessageError("Cannot open %s.", filename.c_str());
        return( false );
    }

    if ( this->is_ascii( fp ) )
    {
        this->read_ascii( fp );
    }
    else if ( this->is_binary( fp ) )
    {
        this->read_binary( fp );
    }
    else
    {
        kvsMessageError( "%s is not GF format data." );
        fclose( fp );
        return( false );
    }

    fclose( fp );

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Check file type whether the ascii or not
 *  @param  fp [in] file pointer
 *  @return true, if the file type is ascii
 */
/*===========================================================================*/
const bool File::is_ascii( FILE* fp )
{
    char buffer[8];
    fseek( fp, 0, SEEK_SET );
    fread( buffer, 1, 8, fp );
    fseek( fp, 0, SEEK_SET );

    return( strncmp( buffer, "#A_GF_V1", 8 ) == 0 );
}

/*===========================================================================*/
/**
 *  @brief  Check file type whether the binary (Fortran unformated) or not
 *  @param  fp [in] file pointer
 *  @return true, if the file type is binary
 */
/*===========================================================================*/
const bool File::is_binary( FILE* fp )
{
    char buffer[8];
    fseek( fp, 4, SEEK_SET );
    fread( buffer, 1, 8, fp );
    fseek( fp, 0, SEEK_SET );

    return( strncmp( buffer, "#U_GF_V1", 8 ) == 0 );
}

/*===========================================================================*/
/**
 *  @brief  Read ascii type file.
 *  @param  fp [in] file pointer
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool File::read_ascii( FILE* fp )
{
    // Read a file-type-header (#A_GF_V1).
    char file_type_header[8];
    fseek( fp, 0, SEEK_SET );
    fread( file_type_header, 1, 8, fp );
    m_file_type_header = std::string( file_type_header, 8 );

    // Read a number of comments.
    kvs::Int32 ncomments = 0;
    fscanf( fp, "%d\n", &ncomments );

    // Read commnets.
    char comment[256];
    for ( size_t i = 0; i < size_t( ncomments ); i++ )
    {
        memset( comment, 0, 256 );
        fgets( comment, 256, fp );

        comment[strlen(comment)-1] = '\0';
        m_comment_list.push_back( std::string( comment ) );
    }

    // Read data set.
    char buffer[256];
    while ( fgets( buffer, 256, fp ) != 0 )
    {
        if ( strncmp( buffer, "#ENDFILE", 8 ) == 0 ) break;

        if ( strncmp( buffer, "#NEW_SET", 8 ) == 0 )
        {
            kvs::gf::DataSet data_set;
            data_set.readAscii( fp );

            m_data_set_list.push_back( data_set );
        }
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Read binary type file (Fortran unformated).
 *  @param  fp [in] file pointer
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool File::read_binary( FILE* fp, const bool swap )
{
    // Read a file-type-header (#U_GF_V1).
    char file_type_header[8];
    fseek( fp, 4, SEEK_SET );
    fread( file_type_header, 1, 8, fp );
    fseek( fp, 4, SEEK_CUR );
    m_file_type_header = std::string( file_type_header, 8 );

    // Read a number of comments.
    kvs::Int32 ncomments = 0;
    fseek( fp, 4, SEEK_CUR );
    fread( &ncomments, 4, 1, fp );
    fseek( fp, 4, SEEK_CUR );
    if ( swap ) kvs::Endian::Swap( ncomments );

    // Read commnets.
    char comment[60];
    char initialize[60]; for ( size_t i = 0; i < 60; i++ ) initialize[i] = '\0';
    for ( size_t i = 0; i < size_t( ncomments ); i++ )
    {
        memcpy( comment, initialize, 60 );
        fseek( fp, 4, SEEK_CUR );
        fread( &comment, 1, 60, fp );
        fseek( fp, 4, SEEK_CUR );

        m_comment_list.push_back( std::string( comment, 60 ) );
    }

    // Read data set.
    for ( ; ; )
    {
        char buffer[8];
        fseek( fp, 4, SEEK_CUR );
        fread( buffer, 1, 8, fp );
        fseek( fp, 4, SEEK_CUR );

        if ( strncmp( buffer, "#ENDFILE", 8 ) == 0 ) break;

        if ( strncmp( buffer, "#NEW_SET", 8 ) == 0 )
        {
            kvs::gf::DataSet data_set;
            if ( !data_set.readBinary( fp ) ) return( false );

            m_data_set_list.push_back( data_set );
        }
    }

    return( true );
}

} // end of namespace gf

} // end of namespace kvs
