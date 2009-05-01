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
#include <kvs/File>
#include <kvs/XMLDocument>
#include <kvs/XMLDeclaration>
#include <kvs/XMLComment>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/IgnoreUnusedVariable>
#include "TransferFunctionTag.h"
#include "ColorMapTag.h"
#include "OpacityMapTag.h"
#include "DataArrayTag.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSMLTransferFunction class.
 */
/*===========================================================================*/
KVSMLTransferFunction::KVSMLTransferFunction( void ):
    m_writing_type( kvs::KVSMLTransferFunction::Ascii ),
    m_resolution( 0 )
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSMLTransferFunction class by reading a file.
 *  @param  filename [in] filename
 */
/*===========================================================================*/
KVSMLTransferFunction::KVSMLTransferFunction( const std::string& filename ):
    m_resolution( 0 )
{
    if ( this->read( filename ) ) { m_is_success = true; }
    else { m_is_success = false; }
}

/*===========================================================================*/
/**
 *  @brief  Destructs the KVSMLTransferFunction class.
 */
/*===========================================================================*/
KVSMLTransferFunction::~KVSMLTransferFunction( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a KVSML tag.
 *  @return KVSML tag
 */
/*===========================================================================*/
const kvs::kvsml::KVSMLTag& KVSMLTransferFunction::KVSMLTag( void ) const
{
    return( m_kvsml_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns a resolution.
 *  @return resolution
 */
/*===========================================================================*/
const size_t KVSMLTransferFunction::resolution( void ) const
{
    return( m_resolution );
}

/*===========================================================================*/
/**
 *  @brief  Returns an opacity array.
 *  @return opacity array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLTransferFunction::opacities( void ) const
{
    return( m_opacities );
}

/*===========================================================================*/
/**
 *  @brief  Returns a color array.
 *  @return color array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8>& KVSMLTransferFunction::colors( void ) const
{
    return( m_colors );
}

/*===========================================================================*/
/**
 *  @brief  Sets a resolution.
 *  @param  resolution [in] resolution
 */
/*===========================================================================*/
void KVSMLTransferFunction::setResolution( const size_t resolution )
{
    m_resolution = resolution;
}

/*===========================================================================*/
/**
 *  @brief  Sets a writing data type.
 *  @param  writing_type [in] writing data type
 */
/*===========================================================================*/
void KVSMLTransferFunction::setWritingDataType( const WritingDataType writing_type )
{
    m_writing_type = writing_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets an opacity array.
 *  @param  opacities [in] opacity array
 */
/*===========================================================================*/
void KVSMLTransferFunction::setOpacities( const kvs::ValueArray<kvs::Real32>& opacities )
{
    m_opacities = opacities;
}

/*===========================================================================*/
/**
 *  @brief  Sets a color array.
 *  @param  colors [in] color array
 */
/*===========================================================================*/
void KVSMLTransferFunction::setColors( const kvs::ValueArray<kvs::UInt8>& colors )
{
    m_colors = colors;
}

/*===========================================================================*/
/**
 *  @brief  Reads transfer function data from a give file.
 *  @param  filename [in] input filename
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool KVSMLTransferFunction::read( const std::string& filename )
{
    m_filename = filename;

    // XML document
    kvs::XMLDocument document;
    if ( !document.read( filename ) )
    {
        kvsMessageError( "%s", document.ErrorDesc().c_str() );
        return( false );
    }

    // <KVSML>
    if ( !m_kvsml_tag.read( &document ) )
    {
        kvsMessageError( "Cannot read <%s>.", m_kvsml_tag.name().c_str() );
        return( false );
    }

    // <TransferFunction>
    kvs::kvsml::TransferFunctionTag tfunc_tag;
    if ( !tfunc_tag.read( m_kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", tfunc_tag.name().c_str() );
        return( false );
    }

    if ( !tfunc_tag.hasResolution() )
    {
        kvsMessageError( "'resolution' is not specified in <%s>.", tfunc_tag.name().c_str() );
        return( false );
    }
    m_resolution = tfunc_tag.resolution();

    // <ColorMap> and <OpacityMap>
    kvs::kvsml::ColorMapTag color_map_tag;
    kvs::kvsml::OpacityMapTag opacity_map_tag;
    if ( color_map_tag.isExisted( tfunc_tag.node() ) )
    {
        // Both <ColorMap> and <OpacityMap> are existed.
        if ( opacity_map_tag.isExisted( tfunc_tag.node() ) )
        {
            if ( !color_map_tag.read( tfunc_tag.node() ) )
            {
                kvsMessageError( "Cannot read <%s>.", color_map_tag.name().c_str() );
                return( false );
            }

            if ( !opacity_map_tag.read( tfunc_tag.node() ) )
            {
                kvsMessageError( "Cannot read <%s>.", opacity_map_tag.name().c_str() );
                return( false );
            }

            // <DataArray> for <ColorMap>
            const size_t colors_nelements = m_resolution * 3;
            kvs::kvsml::DataArrayTag colors;
            if ( !colors.read( color_map_tag.node(), colors_nelements, &m_colors ) )
            {
                kvsMessageError( "Cannot read <%s> for <%s>.",
                                 colors.name().c_str(),
                                 color_map_tag.name().c_str() );
                return( false );
            }

            // <DataArray> for <OpacityMap>
            const size_t opacities_nelements = m_resolution;
            kvs::kvsml::DataArrayTag opacities;
            if ( !opacities.read( opacity_map_tag.node(), opacities_nelements, &m_opacities ) )
            {
                kvsMessageError( "Cannot read <%s> for <%s>.",
                                 opacities.name().c_str(),
                                 opacity_map_tag.name().c_str() );
                return( false );
            }
        }

        // <ColorMap> is existed, but <OpacityMap> is not existed.
        else
        {
            kvsMessageError( "Cannot find <%s>.", opacity_map_tag.name().c_str() );
            return( false );
        }
    }
    else
    {
        // <OpacityMap> is existed, but <ColorMap> is not existed.
        if ( opacity_map_tag.isExisted( tfunc_tag.node() ) )
        {
            kvsMessageError( "Cannot find <%s>.", color_map_tag.name().c_str() );
            return( false );
        }
        else
        {
            if ( !tfunc_tag.hasFile() )
            {
                /* <TransferFunction resolution="xxx">
                 *     a r b g
                 *     a r b g
                 *     .......
                 * </TransferFunction>
                 */
                TiXmlText* values = kvs::XMLNode::ToText( tfunc_tag.node() );
                if ( !values )
                {
                    kvsMessageError( "No values in <%s>", tfunc_tag.name().c_str() );
                    return( false );
                }

                const std::string delim(" \n");
                kvs::Tokenizer t( values->Value(), delim );

                m_opacities.allocate( m_resolution );
                m_colors.allocate( m_resolution * 3 );

                const size_t nloops = m_resolution;
                for ( size_t i = 0, i3 = 0; i < nloops; i++, i3 += 3 )
                {
                    m_opacities.at( i ) = static_cast<kvs::Real32>( atof( t.token().c_str() ) );
                    m_colors.at( i3 ) = static_cast<kvs::UInt8>( atoi( t.token().c_str() ) );
                    m_colors.at( i3 + 1 ) = static_cast<kvs::UInt8>( atoi( t.token().c_str() ) );
                    m_colors.at( i3 + 2 ) = static_cast<kvs::UInt8>( atoi( t.token().c_str() ) );
                }
            }
            else
            {
                /* <TransferFunction resolution="xxx" file="filename.dat"/>
                 *
                 * "filename.dat" should be described as follows:
                 *     a r b g
                 *     a r b g
                 *     .......
                 */
                std::ifstream ifs( tfunc_tag.file().c_str() );
                if ( !ifs.is_open() )
                {
                    kvsMessageError( "Cannot open %s.", tfunc_tag.file().c_str() );
                    return( false );
                }

                m_opacities.allocate( m_resolution );
                m_colors.allocate( m_resolution * 3 );

                kvs::Real32 a = 0;
                kvs::UInt8 r = 0;
                kvs::UInt8 g = 0;
                kvs::UInt8 b = 0;
                for ( size_t i = 0, i3 = 0; i < m_resolution; i++, i3 += 3 )
                {
                    ifs >> a >> r >> g >> b;
                    m_opacities.at( i ) = a;
                    m_colors.at( i3 ) = r;
                    m_colors.at( i3 + 1 ) = g;
                    m_colors.at( i3 + 2 ) = b;
                }

                ifs.close();
            }
        }
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Writes transfer function data to a give file.
 *  @param  filename [in] output filename
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool KVSMLTransferFunction::write( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument document;
    document.InsertEndChild( kvs::XMLDeclaration("1.0") );
    document.InsertEndChild( kvs::XMLComment(" Generated by kvs::KVSMLTransferFunction::write() ") );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.write( &document ) )
    {
        kvsMessageError( "Cannot write <%s>.", kvsml_tag.name().c_str() );
        return( false );
    }

    // <TransferFunction>
    kvs::kvsml::TransferFunctionTag tfunc_tag;
    tfunc_tag.setResolution( m_resolution );
    if ( !tfunc_tag.write( kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", tfunc_tag.name().c_str() );
        return( false );
    }

    // <ColorMap>
    kvs::kvsml::ColorMapTag color_map_tag;
    if ( !color_map_tag.write( tfunc_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", color_map_tag.name().c_str() );
        return( false );
    }

    // <DataArray>
    kvs::kvsml::DataArrayTag colors;
    if ( m_writing_type == ExternalAscii )
    {
        colors.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "cmap" ) );
        colors.setFormat( "ascii" );
    }
    else if ( m_writing_type == ExternalBinary )
    {
        colors.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "cmap" ) );
        colors.setFormat( "binary" );
    }

    if ( !colors.write( color_map_tag.node(), m_colors ) )
    {
        kvsMessageError( "Cannot write <%s> for <%s>.",
                         colors.name().c_str(),
                         color_map_tag.name().c_str() );
        return( false );
    }

    // <OpacityMap>
    kvs::kvsml::OpacityMapTag opacity_map_tag;
    if ( !opacity_map_tag.write( tfunc_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", opacity_map_tag.name().c_str() );
        return( false );
    }

    // <DataArray>
    kvs::kvsml::DataArrayTag opacities;
    if ( m_writing_type == ExternalAscii )
    {
        opacities.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "omap" ) );
        opacities.setFormat( "ascii" );
    }
    else if ( m_writing_type == ExternalBinary )
    {
        opacities.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "omap" ) );
        opacities.setFormat( "binary" );
    }

    if ( !opacities.write( opacity_map_tag.node(), m_opacities ) )
    {
        kvsMessageError( "Cannot write <%s> for <%s>.",
                         opacities.name().c_str(),
                         opacity_map_tag.name().c_str() );
        return( false );
    }

    return( document.write( m_filename ) );
}

/*===========================================================================*/
/**
 *  @brief  Checks the file extension.
 *  @param  filename [in] filename
 *  @return true, if the given filename has the supported extension
 */
/*===========================================================================*/
const bool KVSMLTransferFunction::CheckFileExtension( const std::string& filename )
{
    const kvs::File file( filename );
    if ( file.extension() == "kvsml" ||
         file.extension() == "KVSML" ||
         file.extension() == "xml"   ||
         file.extension() == "XML" )
    {
        return( true );
    }

    return( false );
}

/*===========================================================================*/
/**
 *  @brief  Check the file format.
 *  @param  filename [in] filename
 *  @return true, if the KVSMLTransferFunction class can read the given file
 */
/*===========================================================================*/
const bool KVSMLTransferFunction::CheckFileFormat( const std::string& filename )
{
    kvs::XMLDocument document;
    if ( !document.read( filename ) ) return( false );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.read( &document ) ) return( false );

    // <TransferFunction>
    kvs::kvsml::TransferFunctionTag tfunc_tag;
    if ( !tfunc_tag.read( kvsml_tag.node() ) ) return( false );

    return( false );
}

} // end of namespace kvs
