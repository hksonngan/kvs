/****************************************************************************/
/**
 *  @file Bounds.h
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
#ifndef KVS__BOUNDS_H_INCLUDE
#define KVS__BOUNDS_H_INCLUDE

#include <vector>
#include <kvs/ClassName>
#include <kvs/Module>
#include <kvs/ObjectBase>
#include <kvs/LineObject>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <kvs/Type>
#include "FilterBase.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Create bounds object from volume data.
 */
/*==========================================================================*/
class Bounds : public kvs::FilterBase, public kvs::LineObject
{
    // Class name.
    kvsClassName( Bounds );

    // Module information.
    kvsModuleCategory( Filter );
    kvsModuleBaseClass( kvs::FilterBase );
    kvsModuleSuperClass( kvs::LineObject );

public:

    enum Type
    {
        Box    = 0, ///< box type bounds
        Corner = 1, ///< corner type bounds
        Circle = 2, ///< circle type bounds
    };

protected:

    Type  m_type;         ///< bounds type
    float m_corner_scale; ///< length of corner line
    float m_division;     ///< division of circle

public:

    Bounds( void );

    Bounds( const kvs::ObjectBase* object );

    Bounds( const kvs::ObjectBase* object, const Bounds::Type type );

    virtual ~Bounds( void );

public:

    SuperClass* exec( const kvs::ObjectBase* object );

public:

    void setType( const Bounds::Type type );

    void setCornerScale( const float corner_scale );

    void setCircleDivision( const float division );

private:

    void initialize( void );

    void create_box_bounds( void );

    void create_corner_bounds( void );

    void create_circle_bounds( void );

    void set_corner(
        const kvs::Vector3f&      pos1,
        const kvs::Vector3f&      pos2,
        std::vector<kvs::Real32>* vertex,
        std::vector<kvs::UInt32>* connect );
};

} // end of namespace kvs

#endif // KVS__BOUNDS_H_INCLUDE
