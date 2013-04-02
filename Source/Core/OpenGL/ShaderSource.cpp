/*****************************************************************************/
/**
 *  @file   ShaderSource.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: ShaderSource.cpp 1033 2012-02-17 16:16:41Z naohisa.sakamoto@gmail.com $
 */
/*****************************************************************************/
#include "ShaderSource.h"
#include <kvs/File>
#include <kvs/Directory>
#include <kvs/Message>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>


namespace
{

class SearchPath
{
private:

    std::vector<std::string> m_search_path_list;

public:

    SearchPath()
    {
        // Add "$KVS_DIR/include/Core/Visualization/Shader".
        const std::string sep = kvs::File::Separator();
        const char* kvs_dir = std::getenv("KVS_DIR");
        if ( kvs_dir != NULL )
        {
            std::string path = std::string( kvs_dir ) + sep;
            path += "include" + sep;
            path += "Core" + sep;
            path += "Visualization" + sep;
            path += "Shader" + sep;
            m_search_path_list.push_back( path );
        }

        // Add current directory.
        m_search_path_list.push_back("." + sep);
    }

    void add( const std::string& path )
    {
        m_search_path_list.push_back( path );
    }

    void del()
    {
        m_search_path_list.clear();
    }

    std::string find( const std::string& source )
    {
        // Search the source file from the m_search_path_list.
        std::vector<std::string>::reverse_iterator path = m_search_path_list.rbegin();
        std::vector<std::string>::reverse_iterator last = m_search_path_list.rend();
        while ( path != last )
        {
            const std::string filename = *path + kvs::File::Separator() + source;
            const kvs::File file( filename );
            if ( file.exists() ) { return filename; }
            path++;
        }

        return "";
    }
};

SearchPath search_path;

}

namespace kvs
{


void ShaderSource::AddSearchPath( const std::string& path )
{
    ::search_path.add( path );
}

void ShaderSource::RemoveSearchPath()
{
    ::search_path.del();
}

ShaderSource::ShaderSource( const std::string& source )
{
    const kvs::File file( source );
    const std::string extension = file.extension();
    if ( extension == "vert" || extension == "geom" || extension == "frag" )
    {
        if ( file.exists() )
        {
            const std::string filename( source );
            this->read( filename );
        }
        else
        {
            const std::string filename = ::search_path.find( source );
            if ( filename.empty() ) { kvsMessageError( "Cannot find '%s'.", source.c_str() ); }
            else { this->read( filename ); }
        }
    }
    else
    {
        const std::string code( source );
        this->setCode( code );
    }
}

const std::string& ShaderSource::code() const
{
    return m_code;
}

void ShaderSource::setCode( const std::string& code )
{
    m_code = code;
}

void ShaderSource::clearCode()
{
    m_code.erase();
}

void ShaderSource::define( const std::string& name )
{
    const std::string define = "#define " + name + "\n";

    std::string::size_type version = m_code.find("#version");
    if ( version != std::string::npos )
    {
        m_code.insert( m_code.find( "\n", version ) + 1, define );
    }
    else
    {
        m_code = define + m_code;
    }
}

bool ShaderSource::read( const std::string& filename )
{
    std::ifstream ifs( filename.c_str() );
    if ( ifs.fail() )
    {
        kvsMessageError( "Cannot open '%s'.", filename.c_str() );
        return( false );
    }

    std::ostringstream buffer;
    buffer << ifs.rdbuf();

    std::string code( buffer.str() );
    ifs.close();

    this->setCode( code );

    return( true );
}

} // end of namespace kvs
