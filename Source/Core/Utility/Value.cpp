/****************************************************************************/
/**
 *  @file Value.cpp
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
#include "Value.h"
#include <kvs/Type>


namespace kvs
{

// Template specialization.
template class Value<kvs::Int8>;
template class Value<kvs::UInt8>;
template class Value<kvs::Int16>;
template class Value<kvs::UInt16>;
template class Value<kvs::Int32>;
template class Value<kvs::UInt32>;
template class Value<kvs::Int64>;
template class Value<kvs::UInt64>;
template class Value<kvs::Real32>;
template class Value<kvs::Real64>;
/*
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
*/
} // end of namespace kvs
