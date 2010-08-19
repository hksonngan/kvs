/****************************************************************************/
/**
 *  @file Vector.cpp
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
#include "Vector.h"

namespace kvs
{

// Template instantiation.
template class Vector<char>;
template class Vector<unsigned char>;
template class Vector<short>;
template class Vector<unsigned short>;
template class Vector<int>;
template class Vector<unsigned int>;
template class Vector<long>;
template class Vector<unsigned long>;
template class Vector<float>;
template class Vector<double>;

} // end of namespace kvs
