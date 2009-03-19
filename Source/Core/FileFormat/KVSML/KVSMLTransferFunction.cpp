/****************************************************************************/
/**
 *  @file KVSMLTransferFunction.cpp
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
#include "KVSMLTransferFunction.h"
#include "TransferFunctionParser.h"
#include <kvs/File>
#include <kvs/XMLDocument>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

KVSMLTransferFunction::KVSMLTransferFunction( void )
{
}

KVSMLTransferFunction::KVSMLTransferFunction( const std::string& filename )
{
    if( this->read( filename ) ) { m_is_success = true; }
    else { m_is_success = false; }
}

KVSMLTransferFunction::~KVSMLTransferFunction( void )
{
}

const kvs::ValueArray<kvs::Real32>& KVSMLTransferFunction::opacities( void ) const
{
    return( m_opacities );
}

const kvs::ValueArray<kvs::UInt8>& KVSMLTransferFunction::colors( void ) const
{
    return( m_colors );
}

void KVSMLTransferFunction::setOpacities( const kvs::ValueArray<kvs::Real32>& opacities )
{
    m_opacities = opacities;
}

void KVSMLTransferFunction::setColors( const kvs::ValueArray<kvs::UInt8>& colors )
{
    m_colors = colors;
}

const bool KVSMLTransferFunction::read( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument document;
    if ( !document.read( filename ) )
    {
        kvsMessageError( "%s", document.ErrorDesc().c_str() );
        return( false );
    }

    kvs::TransferFunctionParser parser;
    if ( !parser.parse( document ) )
    {
        kvsMessageError("'%s' is invalid.", filename.c_str());
        return( false );
    }

    parser.setOpacitiesAndColorsTo( &m_opacities, &m_colors );

    return( true );
}

const bool KVSMLTransferFunction::write( const std::string& filename )
{
    kvs::IgnoreUnusedVariable( filename );
    kvsMessageError("Not yet implemented.");

    return( false );
}

const bool KVSMLTransferFunction::CheckFileExtension( const std::string& filename )
{
    const kvs::File file( filename );
    if ( file.extension() == "kvsml" || file.extension() == "KVSML" ||
         file.extension() == "xml"   || file.extension() == "XML" )
    {
        return( true );
    }

    return( false );
}

const bool KVSMLTransferFunction::CheckFileFormat( const std::string& filename )
{
    kvs::XMLDocument document;
    if ( document.read( filename ) )
    {
        kvs::TransferFunctionParser parser;
        if ( parser.parse( document ) )
        {
            return( true );
        }
    }

    return( false );
}

} // end of namespace kvs
