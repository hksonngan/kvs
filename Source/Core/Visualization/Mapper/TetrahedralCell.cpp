/****************************************************************************/
/**
 *  @file TetrahedralCell.cpp
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
#include "TetrahedralCell.h"


namespace kvs
{

// template instantiation
template class TetrahedralCell<char>;
template class TetrahedralCell<unsigned char>;
template class TetrahedralCell<short>;
template class TetrahedralCell<unsigned short>;
template class TetrahedralCell<int>;
template class TetrahedralCell<unsigned int>;
template class TetrahedralCell<long>;
template class TetrahedralCell<unsigned long>;
template class TetrahedralCell<float>;
template class TetrahedralCell<double>;

} // end of namespace kvs
