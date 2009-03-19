/****************************************************************************/
/**
 *  @file DicomList.h
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
#ifndef KVS__DICOM_LIST_H_INCLUDE
#define KVS__DICOM_LIST_H_INCLUDE

#include <algorithm>
#include <vector>
#include <string>
#include <kvs/Vector2>

#include "Dicom.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  DICOM list class.
 */
/*===========================================================================*/
class DicomList
{
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

    std::vector<kvs::Dicom*> m_list;            ///< DICOM list
    size_t                   m_row;             ///< row
    size_t                   m_column;          ///< column
    double                   m_slice_thickness; ///< slice thickness
    double                   m_slice_spacing;   ///< slice spacing
    kvs::Vector2f            m_pixel_spacing;   ///< pixel spacing
    int                      m_min_raw_value;   ///< min. value of the raw data
    int                      m_max_raw_value;   ///< max. value of the raw data

public:

    DicomList( void );

    DicomList( const std::string& dirname, const bool extension_check = true );

    virtual ~DicomList( void );

public:

    const kvs::Dicom* operator [] ( const size_t index ) const;

    kvs::Dicom* operator [] ( const size_t index );

public:

    void push_back( const kvs::Dicom& dicom );

    void push_back( kvs::Dicom* dicom );

    const size_t size( void ) const;

    void clear( void );

public:

    const size_t row( void ) const;

    const size_t column( void ) const;

    const size_t nslices( void ) const;

    const size_t width( void ) const;

    const size_t height( void ) const;

    const double sliceThickness( void ) const;

    const double sliceSpacing( void ) const;

    const kvs::Vector2f& pixelSpacing( void ) const;

    const int minRawValue( void ) const;

    const int maxRawValue( void ) const;

public:

    const bool read( const std::string& dirname, const bool extension_check = true );

    void sort( void )
    {
        std::sort( m_list.begin(), m_list.end(), SortingBySliceLocation() );
    }

    template <typename CompareMethod>
    void sort( void )
    {
        std::sort( m_list.begin(), m_list.end(), CompareMethod() );
    }
};

} // end of namespace kvs

#endif // KVS__DICOM_LIST_H_INCLUDE
