/****************************************************************************/
/**
 *  @file DicomList.h
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
#ifndef KVS__DICOM_LIST_H_INCLUDE
#define KVS__DICOM_LIST_H_INCLUDE

#include <algorithm>
#include <vector>
#include <string>
#include <kvs/Vector2>
#include <kvs/FileFormatBase>
#include <kvs/ClassName>
#include <kvs/Dicom>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  DICOM list class.
 */
/*===========================================================================*/
class DicomList : public kvs::FileFormatBase
{
    kvsClassName( kvs::DicomList );

public:

    typedef kvs::FileFormatBase BaseClass;

public:

    struct SortingByImageNumber
    {
        bool operator () ( const kvs::Dicom* dicom1, const kvs::Dicom* dicom2 );
    };

    struct SortingBySeriesNumber
    {
        bool operator () ( const kvs::Dicom* dicom1, const kvs::Dicom* dicom2 );
    };

    struct SortingBySliceLocation
    {
        bool operator () ( const kvs::Dicom* dicom1, const kvs::Dicom* dicom2 );
    };

protected:

    std::vector<kvs::Dicom*> m_list; ///< DICOM list
    size_t m_row; ///< row
    size_t m_column; ///< column
    double m_slice_thickness; ///< slice thickness
    double m_slice_spacing; ///< slice spacing
    kvs::Vector2f m_pixel_spacing; ///< pixel spacing
    int m_min_raw_value; ///< min. value of the raw data
    int m_max_raw_value; ///< max. value of the raw data
    bool m_extension_check; ///< check the file extension

public:

    DicomList();
    DicomList( const std::string& dirname, const bool extension_check = true );
    virtual ~DicomList();

public:

    const kvs::Dicom* operator [] ( const size_t index ) const;
    kvs::Dicom* operator [] ( const size_t index );

public:

    void push_back( const kvs::Dicom& dicom );
    void push_back( kvs::Dicom* dicom );
    size_t size() const;
    void clear();

public:

    size_t row() const;
    size_t column() const;
    size_t nslices() const;
    size_t width() const;
    size_t height() const;
    double sliceThickness() const;
    double sliceSpacing() const;
    const kvs::Vector2f& pixelSpacing() const;
    int minRawValue() const;
    int maxRawValue() const;
    void enableExtensionCheck();
    void disableExtensionCheck();

public:

    bool read( const std::string& dirname );
    bool write( const std::string& dirname );

    void sort()
    {
        std::sort( m_list.begin(), m_list.end(), SortingBySliceLocation() );
    }

    template <typename CompareMethod>
    void sort()
    {
        std::sort( m_list.begin(), m_list.end(), CompareMethod() );
    }

public:

    static bool CheckDirectory( const std::string& dirname, const bool extension_check = true );
};

} // end of namespace kvs

#endif // KVS__DICOM_LIST_H_INCLUDE
