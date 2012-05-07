/****************************************************************************/
/**
 *  @file Tokenizer.h
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
#ifndef KVS__TOKENIZER_H_INCLUDE
#define KVS__TOKENIZER_H_INCLUDE

#include <string>


namespace kvs
{

/*==========================================================================*/
/**
 *  Delimit tokens.
 */
/*==========================================================================*/
class Tokenizer
{
private:
    std::string            m_source;    ///< source std::string
    std::string            m_delimiter; ///< delimiter set
    std::string::size_type m_next;      ///< next token position

public:
    Tokenizer();
    Tokenizer( const std::string& source, const std::string& delimiter );

public:
    Tokenizer& operator = ( const std::string& source );

public:
    bool isLast() const;
    std::string token();
};

} // end of namespace kvs

#endif // KVS__TOKENIZER_H_INCLUDE
