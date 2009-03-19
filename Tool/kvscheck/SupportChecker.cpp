/****************************************************************************/
/**
 *  @file SupportChecker.cpp
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
#if defined( KVS_SUPPORT_GLEW )
#include <kvs/glew/GLEW>
#endif

#include "SupportChecker.h"
#include <kvs/String>

#if defined( KVS_SUPPORT_GLUT )
#include <kvs/glut/GLUT>
#endif

#if defined( KVS_SUPPORT_SAGE )
#include <kvs/sage/SAGE>
#endif


namespace kvscheck
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
SupportChecker::SupportChecker( void )
{
#if defined( KVS_SUPPORT_GLUT )
    {
        const kvs::String description( kvs::glut::Description() );
        const kvs::String version( kvs::glut::Version() );
        m_descriptions.push_back( description );
        m_versions.push_back( version );
    }
#endif

#if defined( KVS_SUPPORT_GLEW )
    {
        const kvs::String description( kvs::glew::Description() );
        const kvs::String version( kvs::glew::Version() );
        m_descriptions.push_back( description );
        m_versions.push_back( version );
    }
#endif

#if defined( KVS_SUPPORT_SAGE )
    {
        const kvs::String description( kvs::sage::Description() );
        const kvs::String version( kvs::sage::Version() );
        m_descriptions.push_back( description );
        m_versions.push_back( version );
    }
#endif

#if defined( KVS_SUPPORT_QT )
    {
        const kvs::String description( "Qt - Cross-Platform Rich Client Development Framework" );
        const kvs::String version( "please type 'qmake -v'" );
        m_descriptions.push_back( description );
        m_versions.push_back( version );
    }
#endif
}

/*==========================================================================*/
/**
 *  Get the description list of the supported libraries.
 */
/*==========================================================================*/
const kvs::StringList& SupportChecker::descriptionList( void ) const
{
    return( m_descriptions );
}

/*==========================================================================*/
/**
 *  Get the version list of the supported libraries.
 */
/*==========================================================================*/
const kvs::StringList& SupportChecker::versionList( void ) const
{
    return( m_versions );
}

/*==========================================================================*/
/**
 *  Output supported libraries information.
 *  @param os [in] output stream
 *  @param checker [in] supported library checker
 */
/*==========================================================================*/
std::ostream& operator << ( std::ostream& os, const SupportChecker& checker )
{
    os << "Supported libraries:" << std::endl;

    const size_t nlibraries = checker.descriptionList().size();
    for ( size_t i = 0; i < nlibraries; i++ )
    {
        os << checker.descriptionList().at(i)
           << " (version: "<< checker.versionList().at(i) << ")";

        if ( i != nlibraries - 1 ) std::cout << std::endl;
    }

    return( os );
}

} // end of namespace kvscheck
