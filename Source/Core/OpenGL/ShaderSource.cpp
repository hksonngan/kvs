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
#include <kvs/Message>
#include <sstream>
#include <fstream>


namespace kvs
{

ShaderSource::ShaderSource( const std::string& source )
{
    const kvs::File file( source );
    if ( file.isExisted() )
    {
        const std::string filename( source );
        this->read( filename );
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
