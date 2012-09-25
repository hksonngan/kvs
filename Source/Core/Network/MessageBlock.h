/****************************************************************************/
/**
 *  @file MessageBlock.h
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
#ifndef KVS__MESSAGE_BLOCK_H_INCLUDE
#define KVS__MESSAGE_BLOCK_H_INCLUDE

#include <kvs/ValueArray>


namespace kvs
{

/*==========================================================================*/
/**
 *  Message block class.
 */
/*==========================================================================*/
class MessageBlock
{
protected:

    /*     MessageBlock
     *
     *    --------------    ---
     *   | message_size |    |
     *    --------------     |
     *   |              |
     *   |              | m_block
     *   |   message    |
     *   |              |    |
     *   |              |    |
     *    --------------    ---
     */

    kvs::ValueArray<unsigned char> m_block; ///< message block

public:

    MessageBlock();
    MessageBlock( const void* data, const size_t data_size );
    MessageBlock( const std::string& data );
    template<typename T>
    MessageBlock( const std::vector<T>& data );
    virtual ~MessageBlock();

    size_t size() const;
    void* pointer();
    const void* pointer() const;
    size_t blockSize() const;
    void* blockPointer();
    const void* blockPointer() const;
    std::string toString() const;

    void copy( const void* data, const size_t data_size );
    void copy( const std::string& data );
    template <typename T>
    void copy( const std::vector<T>& data );
    void* allocate( const size_t data_size );
    void deallocate();
};

} // end of namespace kvs

#endif // KVS__MESSAGE_BLOCK_H_INCLUDE
