/****************************************************************************/
/**
 *  @file FastTokenizer.cpp
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
#include "FastTokenizer.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructs a new empty FastTokenizer.
 */
/*==========================================================================*/
FastTokenizer::FastTokenizer( void )
    : m_ntokens( 0 )
{
}

/*==========================================================================*/
/**
 *  Constructs a new FastTokenizer.
 */
/*==========================================================================*/
FastTokenizer::FastTokenizer( char* const source, const char* const delimiter )
    : m_ntokens( 0 )
{
    this->set( source, delimiter );
}

/*==========================================================================*/
/**
 *  Destroys the FastTokenizer.
 */
/*==========================================================================*/
FastTokenizer::~FastTokenizer( void )
{
}

} // end of namespace test
