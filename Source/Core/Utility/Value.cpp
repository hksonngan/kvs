/****************************************************************************/
/**
 *  @file Value.cpp
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
#include "Value.h"


namespace kvs
{

// Template specialization.
template class Value<char>;
template class Value<unsigned char>;
template class Value<short>;
template class Value<unsigned short>;
template class Value<int>;
template class Value<unsigned int>;
template class Value<long>;
template class Value<unsigned long>;
template class Value<float>;
template class Value<double>;

} // end of namespace kvs
