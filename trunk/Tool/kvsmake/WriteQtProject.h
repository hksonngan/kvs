/****************************************************************************/
/**
 *  @file WriteQtProject.h
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
#ifndef KVS_KVSMAKE_WRITE_QT_PROJECT_H_INCLUDE
#define KVS_KVSMAKE_WRITE_QT_PROJECT_H_INCLUDE

#include <string>  // For std::string.
#include <fstream> // For std::ifstream, std::ofstream.


namespace kvsmake
{

void WriteQtProject( const std::string& project_name );

void WriteQtProjectBody(
    std::ifstream&     in,
    std::ofstream&     out,
    const std::string& project_name );

} // end of namespace kvsmake

#endif // KVS_KVSMAKE_WRITE_QT_PROJECT_H_INCLUDE
