/****************************************************************************/
/**
 *  @file ImageImporter.h
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
#ifndef KVS_CORE_IMAGE_IMPORTER_H_INCLUDE
#define KVS_CORE_IMAGE_IMPORTER_H_INCLUDE

#include "ImporterBase.h"
#include <kvs/ClassName>
#include <kvs/Module>
#include <kvs/ImageObject>
#include <kvs/KVSMLObjectImage>
#include <kvs/Bmp>
#include <kvs/Tiff>
#include <kvs/Ppm>
#include <kvs/Pgm>
#include <kvs/Pbm>
#include <kvs/Dicom>


namespace kvs
{

/*==========================================================================*/
/**
 *  Image object importer class.
 */
/*==========================================================================*/
class ImageImporter : public kvs::ImporterBase, public kvs::ImageObject
{
    // Class name.
    kvsClassName( ImageImporter );

    // Module information.
    kvsModuleCategory( Importer );
    kvsModuleBaseClass( kvs::ImporterBase );
    kvsModuleSuperClass( kvs::ImageObject );

public:

    ImageImporter( void );

    ImageImporter( const kvs::FileFormatBase* file_format );

    virtual ~ImageImporter( void );

public:

    kvs::ObjectBase* exec( const kvs::FileFormatBase* file_format );

private:

    void import( const kvs::KVSMLObjectImage* kvsml );

    void import( const kvs::Bmp* bmp );

    void import( const kvs::Tiff* tiff );

    void import( const kvs::Ppm* ppm );

    void import( const kvs::Pgm* pgm );

    void import( const kvs::Pbm* pbm );

    void import( const kvs::Dicom* dicom );
};

} // end of namespace kvs

#endif // KVS_CORE_IMAGE_IMPORTER_H_INCLUDE
