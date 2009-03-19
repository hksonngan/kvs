/****************************************************************************/
/**
 *  @file TagParser.h
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
#ifndef KVS_CORE_KVSML_TAG_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_TAG_PARSER_H_INCLUDE

#include <string>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include <kvs/Tokenizer>
#include <kvs/AnyValueArray>
#include <kvs/ValueArray>
#include <kvs/File>
#include <kvs/Message>
#include <kvs/XMLDocument>
#include <kvs/XMLElement>
#include <kvs/Vector3>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

namespace TagParser
{

TiXmlNode* FindNode( const kvs::XMLDocument* document, const std::string& name );

TiXmlNode* FindChildNode( const TiXmlNode* node, const std::string& name );

TiXmlElement* NodeToElement( const TiXmlNode* node );

TiXmlText* NodeToText( const TiXmlNode* node );

std::string GetAttributeValue( const TiXmlElement* element, const std::string& name );

template <typename T>
inline const bool ParseValue(
    const TiXmlNode*    value_node,
    kvs::ValueArray<T>* data_array )
{
    TiXmlText* value_text = kvs::TagParser::NodeToText( value_node );
    if( !value_text )
    {
        kvsMessageError("No value in <Value>");
        return( false );
    }

    const std::string delim(" \n");
    kvs::Tokenizer t( value_text->Value(), delim );

    const int nloops = data_array->size();
    for( int i = 0; i < nloops; i++ )
    {
        data_array->at( i ) = static_cast<T>( atof( t.token().c_str() ) );
    }

    return( true );
}

template <typename T1, typename T2>
inline const bool ReadArray(
    const std::string&   file,
    const std::string&   format,
    kvs::ValueArray<T1>* data_array )
{
    if( format == "binary" )
    {
        FILE* ifs = fopen( file.c_str(), "rb" );
        if( !ifs )
        {
            kvsMessageError("Cannot open '%s'.", file.c_str());
            return( false );
        }

        if( typeid(T1) == typeid(T2) )
        {
            fread( data_array->pointer(), data_array->size(), sizeof(T1), ifs );
        }
        else
        {
            const size_t nloops = data_array->size();
            for( size_t i = 0; i < nloops; i++ )
            {
                T2 data = T2(0);
                fread( &data, 1, sizeof(T2), ifs );
                data_array->at(i) = static_cast<T1>( data );
            }
        }
        fclose( ifs );
    }
    else if( format == "ascii" )
    {
        FILE* ifs = fopen( file.c_str(), "r" );
        if( !ifs )
        {
            kvsMessageError("Cannot open '%s'.", file.c_str());
            return( false );
        }

        fseek( ifs, 0, SEEK_END );
        size_t size = ftell( ifs );

        char* buffer = (char*)malloc( sizeof(char) * size );
        if ( !buffer )
        {
            kvsMessageError("Cannot allocate memory.");
            fclose( ifs );
            return( false );
        }

        fseek( ifs, 0, SEEK_SET );
        if ( size != fread( buffer, 1, size, ifs ) )
        {
            kvsMessageError( "Cannot read '%s'.", file.c_str() );
            return( false );
        }

        const std::string delim(" \n");
        kvs::Tokenizer t( buffer, delim );

        size_t index = 0;
        while( !t.isLast() )
        {
            data_array->at(index) = static_cast<T1>( atof( t.token().c_str() ) );

            index++;
        }

        fclose( ifs );

        return( true );
    }
    else
    {
        kvsMessageError("Unknown format '%s'.",format.c_str());
        return( false );
    }

    return( true );
}

template <typename T>
inline const bool ReadArray(
    const std::string&  file,
    const std::string&  format,
    kvs::AnyValueArray* data_array )
{
    if( format == "binary" )
    {
        FILE* ifs = fopen( file.c_str(), "rb" );
        if( !ifs )
        {
            kvsMessageError("Cannot open '%s'.", file.c_str());
            return( false );
        }

        fread( data_array->pointer(), data_array->size(), sizeof(T), ifs );

        fclose( ifs );
    }
    else if( format == "ascii" )
    {
        FILE* ifs = fopen( file.c_str(), "r" );
        if( !ifs )
        {
            kvsMessageError("Cannot open '%s'.", file.c_str());
            return( false );
        }

        fseek( ifs, 0, SEEK_END );
        size_t size = ftell( ifs );

        char* buffer = (char*)malloc( sizeof(char) * size );
        if ( !buffer )
        {
            kvsMessageError("Cannot allocate memory.");
            fclose( ifs );
            return( false );
        }

        fseek( ifs, 0, SEEK_SET );
        if ( size != fread( buffer, 1, size, ifs ) )
        {
            kvsMessageError( "Cannot read '%s'.", file.c_str() );
            return( false );
        }

        const std::string delim(" \n");
        kvs::Tokenizer t( buffer, delim );

        T* data = (T*)data_array->pointer();
        size_t index = 0;
        while( !t.isLast() )
        {
            data[index] = static_cast<T>( atof( t.token().c_str() ) );
            index++;
        }

        fclose( ifs );
    }
    else
    {
        kvsMessageError("Unknown format '%s'.",format.c_str());
        return( false );
    }

    return( true );
}

template <typename T>
inline const bool ParseArray(
    const TiXmlNode*    array_node,
    kvs::ValueArray<T>* data_array )
{
    TiXmlElement* array_element = kvs::TagParser::NodeToElement( array_node );
    std::string file = kvs::TagParser::GetAttributeValue( array_element, "file" );
    if( file == "" )
    {
        // <DataArray>xxx</DataArray>
        TiXmlText* array_text = kvs::TagParser::NodeToText( array_node );
        if( !array_text )
        {
            kvsMessageError("No value in <DataArray>");
            return( false );
        }

        const std::string delim(" \n");
        kvs::Tokenizer t( array_text->Value(), delim );

        const size_t nloops = data_array->size();
        for( size_t i = 0; i < nloops; i++ )
        {
            data_array->at( i ) = static_cast<T>( atof( t.token().c_str() ) );
        }
    }
    else
    {
        // <DataArray file="xxx" type="xxx" format="xxx"/>
        std::string format = kvs::TagParser::GetAttributeValue( array_element, "format" );
        if( format == "" )
        {
            kvsMessageError("'format' is not specified in <DataArray/>.");
            return( false );
        }

        kvs::XMLDocument* document
            = reinterpret_cast<kvs::XMLDocument*>(array_node->GetDocument());

        std::string path = kvs::File( document->filename() ).pathName(true);
        std::string filename = path + kvs::File::Separator() + file;

        std::string type = kvs::TagParser::GetAttributeValue( array_element, "type" );
        if( type == "" )
        {
            kvsMessageError("'type' is not specified in <DataArray/>.");
            return( false );
        }

        if( type == "char" )
        {
            return( kvs::TagParser::ReadArray<T,char>( filename, format, data_array ) );
        }
        else if( type == "unsigned char" || type == "uchar" )
        {
            return( kvs::TagParser::ReadArray<T,unsigned char>( filename, format, data_array ) );
        }
        else if( type == "short" )
        {
            return( kvs::TagParser::ReadArray<T,short>( filename, format, data_array ) );
        }
        else if( type == "unsigned short" || type == "ushort" )
        {
            return( kvs::TagParser::ReadArray<T,unsigned short>( filename, format, data_array ) );
        }
        else if( type == "int" )
        {
            return( kvs::TagParser::ReadArray<T,int>( filename, format, data_array ) );
        }
        else if( type == "unsigned int" || type == "uint" )
        {
            return( kvs::TagParser::ReadArray<T,unsigned int>( filename, format, data_array ) );
        }
        else if( type == "float" )
        {
            return( kvs::TagParser::ReadArray<T,float>( filename, format, data_array ) );
        }
        else if( type == "double" )
        {
            return( kvs::TagParser::ReadArray<T,double>( filename, format, data_array ) );
        }
        else
        {
            kvsMessageError("Unknown 'type' in <DataArray>.");
            return( false );
        }
    }

    return( true );
}

template <typename T>
inline const bool ParseArray( const TiXmlNode* array_node, kvs::AnyValueArray* data_array )
{
    TiXmlElement* array_element = kvs::TagParser::NodeToElement( array_node );
    std::string file = kvs::TagParser::GetAttributeValue( array_element, "file" );

    // Internal data.
    if( file == "" )
    {
        TiXmlText* array_text = kvs::TagParser::NodeToText( array_node );
        if( !array_text )
        {
            kvsMessageError("No value in <DataArray>");
            return( false );
        }

        // <DataArray type="xxx">xxx</DataArray>
        const std::string delim(" \n");
        kvs::Tokenizer t( array_text->Value(), delim );

        const std::type_info& type = data_array->typeInfo()->type();
        if( type == typeid(kvs::Int8) )
        {
            kvs::Int8* data = (kvs::Int8*)data_array->pointer();
            const size_t nloops = data_array->size();
            for( size_t i = 0; i < nloops; i++ )
            {
                data[i] = static_cast<kvs::Int8>( atoi( t.token().c_str() ) );
            }
        }
        else if( type == typeid(kvs::UInt8) )
        {
            kvs::UInt8* data = (kvs::UInt8*)data_array->pointer();
            const size_t nloops = data_array->size();
            for( size_t i = 0; i < nloops; i++ )
            {
                data[i] = static_cast<kvs::UInt8>( atoi( t.token().c_str() ) );
            }
        }
        else
        {
            T* data = (T*)data_array->pointer();
            const size_t nloops = data_array->size();
            for( size_t i = 0; i < nloops; i++ )
            {
                data[i] = static_cast<T>( atof( t.token().c_str() ) );
            }
        }
    }

    // External data.
    else
    {
        // <DataArray file="xxx" type="xxx" format="xxx"/>
        std::string format = kvs::TagParser::GetAttributeValue( array_element, "format" );
        if( format == "" )
        {
            kvsMessageError("'format' is not specified in <Array/>.");
            return( false );
        }
        kvs::XMLDocument* document
            = reinterpret_cast<kvs::XMLDocument*>(array_node->GetDocument());
        std::string path = kvs::File( document->filename() ).pathName(true);
        std::string filename = path + kvs::File::Separator() + file;
        return( kvs::TagParser::ReadArray<T>( filename, format, data_array ) );
    }

    return( true );
}




enum WritingDataType
{
    Ascii = 0,
    ExternalAscii,
    ExternalBinary
};

inline const std::string GetDataFormat( const WritingDataType writing_type )
{
    switch ( writing_type )
    {
    case Ascii:
    case ExternalAscii:
        return("ascii");
    case ExternalBinary:
        return("binary");
    default:
        return("unknown");
    }
}

inline const std::string GetDataFilename( const std::string& filename, const std::string& type )
{
    const std::string basename( kvs::File( filename ).baseName() );
    const std::string pathname( kvs::File( filename ).pathName() );
    const std::string sep( kvs::File::Separator() );
    const std::string ext( "dat" );

    return( pathname + sep + basename + "_" + type + "." + ext );
}

template <typename T>
inline const std::string GetDataType( const kvs::ValueArray<T>& data_array )
{
    kvs::IgnoreUnusedVariable( data_array );

    if (      typeid(T) == typeid(kvs::Int8)   ) return("char");
    else if ( typeid(T) == typeid(kvs::UInt8)  ) return("uchar");
    else if ( typeid(T) == typeid(kvs::Int16)  ) return("short");
    else if ( typeid(T) == typeid(kvs::UInt16) ) return("ushort");
    else if ( typeid(T) == typeid(kvs::Int32)  ) return("int");
    else if ( typeid(T) == typeid(kvs::UInt32) ) return("uint");
    else if ( typeid(T) == typeid(kvs::Int64)  ) return("long");
    else if ( typeid(T) == typeid(kvs::UInt64) ) return("ulong");
    else if ( typeid(T) == typeid(kvs::Real32) ) return("float");
    else if ( typeid(T) == typeid(kvs::Real64) ) return("double");
    else return("unknown");
}

inline const std::string GetDataType( const kvs::AnyValueArray& data_array )
{
    const std::type_info& type = data_array.typeInfo()->type();
    if (      type == typeid(kvs::Int8)   ) return("char");
    else if ( type == typeid(kvs::UInt8)  ) return("uchar");
    else if ( type == typeid(kvs::Int16)  ) return("short");
    else if ( type == typeid(kvs::UInt16) ) return("ushort");
    else if ( type == typeid(kvs::Int32)  ) return("int");
    else if ( type == typeid(kvs::UInt32) ) return("uint");
    else if ( type == typeid(kvs::Int64)  ) return("long");
    else if ( type == typeid(kvs::UInt64) ) return("ulong");
    else if ( type == typeid(kvs::Real32) ) return("float");
    else if ( type == typeid(kvs::Real64) ) return("double");
    else return("unknown");
}

template <typename T>
inline const bool WriteArray(
    const WritingDataType     writing_type,
    const kvs::ValueArray<T>& data_array,
    const std::string&        filename )
{
    if ( writing_type == ExternalAscii )
    {
        std::ofstream ofs( filename.c_str() );
        if ( ofs.fail() )
        {
            kvsMessageError("Cannot open file '%s'.", filename.c_str() );
            return( false );
        }

        const size_t data_size = data_array.size();
        if ( typeid(T) == typeid(kvs::Int8) || typeid(T) == typeid(kvs::UInt8) )
        {
            for ( size_t i = 0; i < data_size; i++ ) ofs << int(data_array.at(i)) << " ";
        }
        else
        {
            for ( size_t i = 0; i < data_size; i++ ) ofs << data_array.at(i) << " ";
        }

        ofs.close();
    }
    else if ( writing_type == ExternalBinary )
    {
        std::ofstream ofs( filename.c_str() );
        if ( ofs.fail() )
        {
            kvsMessageError("Cannot open file '%s'.", filename.c_str() );
            return( false );
        }
        const char* data_pointer = reinterpret_cast<const char*>( data_array.pointer() );
        const size_t data_byte_size = data_array.byteSize();
        ofs.write( data_pointer, data_byte_size );
        ofs.close();
    }

    return( true );
}

inline const bool WriteArray(
    const WritingDataType     writing_type,
    const kvs::AnyValueArray& data_array,
    const std::string&        filename )
{
    if ( writing_type == ExternalAscii )
    {
        std::ofstream ofs( filename.c_str() );
        if ( ofs.fail() )
        {
            kvsMessageError("Cannot open file '%s'.", filename.c_str() );
            return( false );
        }

        const std::type_info& data_type = data_array.typeInfo()->type();
        const size_t data_size = data_array.size();
        if ( data_type == typeid(kvs::Int8) )
        {
            const kvs::Int8* values = data_array.pointer<kvs::Int8>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << kvs::Int16(values[i]) << " ";
        }
        else if ( data_type == typeid(kvs::UInt8) )
        {
            const kvs::UInt8* values = data_array.pointer<kvs::UInt8>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << kvs::UInt16(values[i]) << " ";
        }
        else if ( data_type == typeid(kvs::Int16) )
        {
            const kvs::Int16* values = data_array.pointer<kvs::Int16>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::UInt16) )
        {
            const kvs::UInt16* values = data_array.pointer<kvs::UInt16>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Int32) )
        {
            const kvs::Int32* values = data_array.pointer<kvs::Int32>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::UInt32) )
        {
            const kvs::UInt32* values = data_array.pointer<kvs::UInt32>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Int64) )
        {
            const kvs::Int64* values = data_array.pointer<kvs::Int64>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::UInt64) )
        {
            const kvs::UInt64* values = data_array.pointer<kvs::UInt64>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Int16) )
        {
            const kvs::Int16* values = data_array.pointer<kvs::Int16>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Real32) )
        {
            const kvs::Real32* values = data_array.pointer<kvs::Real32>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Real64) )
        {
            const kvs::Real64* values = data_array.pointer<kvs::Real64>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Real128) )
        {
            const kvs::Real128* values = data_array.pointer<kvs::Real128>();
            for ( size_t i = 0; i < data_size; i++ ) ofs << values[i] << " ";
        }

        ofs.close();
    }
    else if ( writing_type == ExternalBinary )
    {
        std::ofstream ofs( filename.c_str() );
        if ( ofs.fail() )
        {
            kvsMessageError("Cannot open file '%s'.", filename.c_str() );
            return( false );
        }
        const void* data_pointer = data_array.pointer();
        const size_t data_byte_size = data_array.byteSize();
        ofs.write( static_cast<const char*>(data_pointer), data_byte_size );
        ofs.close();
    }

    return( true );
}

template <typename T>
inline const bool ComposeArray(
    TiXmlNode*                parent_node,
    const WritingDataType     writing_type,
    const kvs::ValueArray<T>& data_array,
    const size_t              veclen,
    const std::string&        file )
{
    if ( data_array.size() == 0 ) return( true );

    // <DataValue> : In the case of one component.
    if ( data_array.size() == veclen )
    {
        // <DataValue>xxx</DataValue>
        kvs::XMLElement data_elem("DataValue");
        TiXmlNode* data_node = parent_node->InsertEndChild( data_elem );

        // Write the data array to string-stream.
        std::ostringstream oss( std::ostringstream::out );
        if ( typeid(T) == typeid(kvs::Int8) || typeid(T) == typeid(kvs::UInt8) )
        {
            for ( size_t i = 0; i < veclen; i++ ) oss << int(data_array.at(i)) << " ";
        }
        else
        {
            for ( size_t i = 0; i < veclen; i++ ) oss << data_array.at(i) << " ";
        }

        // Insert the data array as string-stream to the parent node.
        TiXmlText data_text;
        data_text.SetValue( oss.str() );

        return( data_node->InsertEndChild( data_text ) != NULL );
    }

    // <DataArray>
    else
    {
        // <DataArray>xxx</DataArray>
        kvs::XMLElement data_elem("DataArray");
        if ( writing_type == Ascii )
        {
            // Write the data array to string-stream.
            std::ostringstream oss( std::ostringstream::out );
            const size_t data_size = data_array.size();
            if ( typeid(T) == typeid(kvs::Int8) || typeid(T) == typeid(kvs::UInt8) )
            {
                for ( size_t i = 0; i < data_size; i++ ) oss << int(data_array.at(i)) << " ";
            }
            else
            {
                for ( size_t i = 0; i < data_size; i++ ) oss << data_array.at(i) << " ";
            }

            // Insert the data array as string-stream to the parent node.
            TiXmlText data_text;
            data_text.SetValue( oss.str() );

            TiXmlNode* data_node = parent_node->InsertEndChild( data_elem );
            return( data_node->InsertEndChild( data_text ) != NULL );
        }

        // <DataArray type="float" format="xxx" file="xxx"/>
        else
        {
            // Type name of the data array.
            const std::string type( kvs::TagParser::GetDataType( data_array ) );
            const std::string format( kvs::TagParser::GetDataFormat( writing_type ) );

            // Set attributes.
            data_elem.setAttribute( "type", type );
            data_elem.setAttribute( "format", format );
            data_elem.setAttribute( "file", file );
            parent_node->InsertEndChild( data_elem );

            // Set text.
//            return( WriteArray( writing_type, data_array, type, file ) );
            return( WriteArray( writing_type, data_array, file ) );
        }
    }

//    return( true );
}

inline const bool ComposeArray(
    TiXmlNode*                parent_node,
    const WritingDataType     writing_type,
    const kvs::AnyValueArray& data_array,
    const size_t              veclen,
    const std::string&        file )
{
    kvs::IgnoreUnusedVariable( veclen );

    if ( data_array.size() == 0 ) return( true );

    // Internal data: <DataArray type="xxx">xxx</DataArray>
    kvs::XMLElement data_elem("DataArray");
    if ( writing_type == Ascii )
    {
        // Set attribute.
        const std::string type( kvs::TagParser::GetDataType( data_array ) );
        data_elem.setAttribute( "type", type );

        // Write the data array to string-stream.
        std::ostringstream oss( std::ostringstream::out );
        const std::type_info& data_type = data_array.typeInfo()->type();
        const size_t data_size = data_array.size();
        if ( data_type == typeid(kvs::Int8) )
        {
            const kvs::Int8* values = data_array.pointer<kvs::Int8>();
            for ( size_t i = 0; i < data_size; i++ ) oss << kvs::Int16(values[i]) << " ";
        }
        else if ( data_type == typeid(kvs::UInt8) )
        {
            const kvs::UInt8* values = data_array.pointer<kvs::UInt8>();
            for ( size_t i = 0; i < data_size; i++ ) oss << kvs::UInt16(values[i]) << " ";
        }
        else if ( data_type == typeid(kvs::Int16) )
        {
            const kvs::Int16* values = data_array.pointer<kvs::Int16>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::UInt16) )
        {
            const kvs::UInt16* values = data_array.pointer<kvs::UInt16>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Int32) )
        {
            const kvs::Int32* values = data_array.pointer<kvs::Int32>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::UInt32) )
        {
            const kvs::UInt32* values = data_array.pointer<kvs::UInt32>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Int64) )
        {
            const kvs::Int64* values = data_array.pointer<kvs::Int64>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::UInt64) )
        {
            const kvs::UInt64* values = data_array.pointer<kvs::UInt64>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Int16) )
        {
            const kvs::Int16* values = data_array.pointer<kvs::Int16>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Real32) )
        {
            const kvs::Real32* values = data_array.pointer<kvs::Real32>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Real64) )
        {
            const kvs::Real64* values = data_array.pointer<kvs::Real64>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }
        else if ( data_type == typeid(kvs::Real128) )
        {
            const kvs::Real128* values = data_array.pointer<kvs::Real128>();
            for ( size_t i = 0; i < data_size; i++ ) oss << values[i] << " ";
        }

        // Insert the data array as string-stream to the parent node.
        TiXmlText data_text;
        data_text.SetValue( oss.str() );

        TiXmlNode* data_node = parent_node->InsertEndChild( data_elem );
        return( data_node->InsertEndChild( data_text ) != NULL );
    }

    // External data: <DataArray type="xxx" format="xxx" file="xxx"/>
    else
    {
        // Type name of the data array.
        const std::string type( kvs::TagParser::GetDataType( data_array ) );
        const std::string format( kvs::TagParser::GetDataFormat( writing_type ) );

        // Set attributes.
        data_elem.setAttribute( "type", type );
        data_elem.setAttribute( "format", format );
        data_elem.setAttribute( "file", file );
        parent_node->InsertEndChild( data_elem );

            // Set text.
//            return( WriteArray( writing_type, data_array, type, file ) );
        return( WriteArray( writing_type, data_array, file ) );
    }
}

} // end of namespace TagParser

} // end of namespace kvs

#endif // KVS_CORE_KVSML_TAG_PARSER_H_INCLUDE
