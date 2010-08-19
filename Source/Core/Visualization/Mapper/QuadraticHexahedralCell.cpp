/*****************************************************************************/
/**
 *  @file   HexahedralCell.cpp
 *  @author Takuma KAWAMURA
 *  @brief  Quadratic tetrahedral cell class.
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "QuadraticHexahedralCell.h"


namespace kvs
{

// template instantiation
template class QuadraticHexahedralCell<char>;
template class QuadraticHexahedralCell<unsigned char>;
template class QuadraticHexahedralCell<short>;
template class QuadraticHexahedralCell<unsigned short>;
template class QuadraticHexahedralCell<int>;
template class QuadraticHexahedralCell<unsigned int>;
template class QuadraticHexahedralCell<long>;
template class QuadraticHexahedralCell<unsigned long>;
template class QuadraticHexahedralCell<float>;
template class QuadraticHexahedralCell<double>;

} // end of namespace kvs
