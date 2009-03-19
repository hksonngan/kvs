/****************************************************************************/
/**
 *  @file ValueArray.cpp
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
#include "ValueArray.h"


namespace kvs
{

// Template specialization.
template class ValueArray<char>;
template class ValueArray<unsigned char>;
template class ValueArray<short>;
template class ValueArray<unsigned short>;
template class ValueArray<int>;
template class ValueArray<unsigned int>;
template class ValueArray<long>;
template class ValueArray<unsigned long>;
template class ValueArray<float>;
template class ValueArray<double>;

} // end of namespace kvs
