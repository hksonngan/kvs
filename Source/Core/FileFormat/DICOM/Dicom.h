/****************************************************************************/
/**
 *  @file Dicom.h
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
#ifndef KVS__DICOM_H_INCLUDE
#define KVS__DICOM_H_INCLUDE

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <kvs/FileFormatBase>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector2>
#include "Attribute.h"
#include "Window.h"
#include "Element.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  DICOM class.
 */
/*===========================================================================*/
class Dicom : public kvs::FileFormatBase
{
public:

    typedef kvs::FileFormatBase BaseClass;
    typedef dcm::Element Element;
    typedef std::list<dcm::Element> ElementList;

protected:

    dcm::Attribute m_attribute; ///< attribute
    std::list<dcm::Element> m_element_list; ///< element list
    std::string m_modality; ///< (0008,0060) modality
    std::string m_manufacturer; ///< (0008,0070) manufacturer
    double m_slice_thickness; ///< (0018,0050) slice thickness
    double m_slice_spacing; ///< (0018,0088) spacing between slices
    int m_series_number; ///< (0020,0011) series number
    int m_image_number; ///< (0020,0013) image number
    double m_slice_location; ///< (0020,1041) slice location
    unsigned short m_row; ///< (0028,0010) rows (height)
    unsigned short m_column; ///< (0028,0011) columns (width)
    kvs::Vector2f m_pixel_spacing; ///< (0028,0030) pixel spacing
    unsigned short m_bits_allocated; ///< (0028,0100) bits allocated
    unsigned short m_bits_stored; ///< (0028,0101) bits stored
    unsigned short m_high_bit; ///< (0028,0102) high bit
    bool m_pixel_representation; ///< (0028,0103) pixel representation
    int m_window_level; ///< (0028,1050) window center
    int m_window_width; ///< (0028,1051) window width
    double m_rescale_intersept; ///< (0028,1052) rescale intersept
    double m_rescale_slope; ///< (0028,1053) rescale slope
    dcm::Window m_window; ///< window
    int m_min_raw_value; ///< min. value of the raw data
    int m_max_raw_value; ///< max. value of the raw data
    std::ios::pos_type m_position; ///< raw data position
    kvs::ValueArray<char> m_raw_data; ///< raw data

public:

    Dicom();
    Dicom( const std::string& filename );
    Dicom( const Dicom& dicom );
    virtual ~Dicom();

public:

    void initialize();
    void clear();

public:

    Dicom& operator = ( const Dicom& d );
    friend std::ostream& operator << ( std::ostream& os, const Dicom& d );

public:

    unsigned short width() const;
    unsigned short height() const;
    int seriesNumber() const;
    int imageNumber() const;
    double sliceLocation() const;
    unsigned short row() const;
    unsigned short column() const;
    unsigned int size() const;
    unsigned short bitsAllocated() const;
    unsigned short bytesAllocated() const;
    unsigned short bitsStored() const;
    unsigned short bytesStored() const;
    unsigned short highBit() const;
    bool pixelRepresentation() const;
    int windowLevel() const;
    int windowWidth() const;
    int minWindowValue() const;
    int maxWindowValue() const;
    int minRawValue() const;
    int maxRawValue() const;
    int minValue() const;
    int maxValue() const;
    double rescaleIntersept() const;
    double rescaleSlope() const;
    const dcm::Attribute& attribute() const;
    const std::list<dcm::Element>& elementList() const;
    const std::string& modality() const;
    const kvs::Vector2f& pixelSpacing() const;
    const std::string& manufacturer() const;
    double sliceThickness() const;
    double sliceSpacing() const;
    const dcm::Window& window() const;
    const std::ios::pos_type& position() const;
    const kvs::ValueArray<char>& rawData() const;
    kvs::ValueArray<kvs::UInt8> pixelData() const;
    int rawValue( const size_t index ) const;
    int rawValue( const size_t i, const size_t j ) const;
    int value( const size_t index ) const;
    int value( const size_t x, const size_t y ) const;

public:

    void setRawData( const kvs::ValueArray<char>& raw_data );
    void changeWindow( const int level, const int width );
    void resetWindow();
    std::list<dcm::Element>::iterator findElement( const dcm::Tag tag );

public:

    bool read( const std::string& filename );
    bool write( const std::string& filename );

private:

    bool read_header( std::ifstream& ifs );
    bool read_data( std::ifstream& ifs );
    bool write_header( std::ofstream& ofs );
    bool write_header_csv( std::ofstream& ofs );
    bool write_raw_data( std::ofstream& ofs );

    void set_windowing_parameter();
    void set_min_max_window_value();
    template <typename T>
    void calculate_min_max_raw_value();
    void set_min_max_raw_value();
    template <typename T>
    kvs::ValueArray<kvs::UInt8> rescale_pixel_data( const int level, const int width ) const;
    kvs::ValueArray<kvs::UInt8> get_pixel_data( const int level, const int width ) const;
    void parse_element( dcm::Element& element );

public:

    static bool CheckFileExtension( const std::string& filename );
    static bool CheckFileFormat( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__DICOM_H_INCLUDE
