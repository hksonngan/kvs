/****************************************************************************/
/**
 *  @file Matrix44.cpp
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
#include "Matrix44.h"


namespace kvs
{

// Template instantiation.
// template class Matrix44<char>;
// template class Matrix44<unsigned char>;
// template class Matrix44<short>;
// template class Matrix44<unsigned short>;
// template class Matrix44<int>;
// template class Matrix44<unsigned int>;
// template class Matrix44<long>;
// template class Matrix44<unsigned long>;
template class Matrix44<float>;
template class Matrix44<double>;

} // end of namespace kvs
