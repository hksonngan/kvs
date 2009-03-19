/****************************************************************************/
/**
 *  @file Module.h
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
#ifndef KVS_CORE_MODULE_H_INCLUDE
#define KVS_CORE_MODULE_H_INCLUDE

#define KVS_MODULE_IMPORTER kvs::ImporterBase::ModuleTag
#define KVS_MODULE_FILTER   kvs::FilterBase::ModuleTag
#define KVS_MODULE_MAPPER   kvs::MapperBase::ModuleTag
#define KVS_MODULE_OBJECT   kvs::ObjectBase::ModuleTag
#define KVS_MODULE_RENDERER kvs::RendererBase::ModuleTag

#define kvsModuleBase                           \
    public:                                     \
    struct  ModuleTag{};                        \
    typedef ModuleTag ModuleCategory

#define kvsModuleBaseClass( base_class )        \
    typedef base_class BaseClass

#define kvsModuleSuperClass( super_class )      \
    typedef super_class SuperClass

#define kvsModuleCategory( module_category )                            \
    public:                                                             \
    typedef kvs:: module_category##Base::ModuleTag ModuleCategory

namespace kvs
{

template <typename T>
struct ModuleTraits
{
    typedef typename T::ModuleCategory ModuleCategory;
};

} // end of namespace kvs

#endif // KVS_CORE_MODULE_H_INCLUDE
