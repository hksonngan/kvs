/****************************************************************************/
/**
 *  @file PyramidalCell.cpp
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
#include "PyramidalCell.h"


namespace kvs
{

// template instantiation
template class PyramidalCell<char>;
template class PyramidalCell<unsigned char>;
template class PyramidalCell<short>;
template class PyramidalCell<unsigned short>;
template class PyramidalCell<int>;
template class PyramidalCell<unsigned int>;
template class PyramidalCell<long>;
template class PyramidalCell<unsigned long>;
template class PyramidalCell<float>;
template class PyramidalCell<double>;

} // end of namespace kvs
