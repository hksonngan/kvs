/****************************************************************************/
/**
 *  @file   QuadraticTetrahedralCell.cpp
 *  @author Naohisa Sakamoto
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
#include "QuadraticTetrahedralCell.h"


namespace kvs
{

// template instantiation
template class QuadraticTetrahedralCell<char>;
template class QuadraticTetrahedralCell<unsigned char>;
template class QuadraticTetrahedralCell<short>;
template class QuadraticTetrahedralCell<unsigned short>;
template class QuadraticTetrahedralCell<int>;
template class QuadraticTetrahedralCell<unsigned int>;
template class QuadraticTetrahedralCell<long>;
template class QuadraticTetrahedralCell<unsigned long>;
template class QuadraticTetrahedralCell<float>;
template class QuadraticTetrahedralCell<double>;

} // end of namespace kvs