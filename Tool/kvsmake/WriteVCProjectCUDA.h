/****************************************************************************/
/**
 *  @file WriteVCProjectCUDA.h
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
#ifndef KVS_KVSMAKE_WRITE_VC_PROJECT_CUDA_H_INCLUDE
#define KVS_KVSMAKE_WRITE_VC_PROJECT_CUDA_H_INCLUDE

#include <string>  // For std::string.
#include <fstream> // For std::ifstream, std::ofstream.


namespace kvsmake
{

void WriteVCProjectCUDA( const std::string& project_name );

void WriteVCProjectCUDABody(
    std::ifstream&     in,
    std::ofstream&     out,
    const std::string& project_name );

} // end of namespace kvsmake

#endif // KVS_KVSMAKE_WRITE_VC_PROJECT_CUDA_H_INCLUDE
