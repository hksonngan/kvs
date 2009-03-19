/****************************************************************************/
/**
 *  @file PolygonRenderingFunction.h
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
#ifndef KVS_CORE_POLYGON_RENDERING_FUNCTION_H_INCLUDE
#define KVS_CORE_POLYGON_RENDERING_FUNCTION_H_INCLUDE


#include <kvs/PolygonObject>
#include <kvs/RGBColor>


namespace
{

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const size_t         nvertices = polygon->nvertices();
        const unsigned char* colors    = polygon->colors().pointer();
        const float*         coords  = polygon->coords().pointer();
        const unsigned char  opacity   = polygon->opacity();

        size_t index = 0;
        for( size_t i = 0; i < nvertices; i++, index += 3 )
        {
            glColor4ub( *( colors + index ),
                        *( colors + index + 1 ),
                        *( colors + index + 2 ),
                        opacity );
            glVertex3fv( coords + index );
/*
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );

            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
*/
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer()   + index),
                        *(polygon->colors().pointer()   + index+1),
                        *(polygon->colors().pointer()   + index+2),
                        polygon->opacity( i ) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity(con0/3) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity(con1/3) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity(con2/3) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }

    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nopacities(); i++ )
        {
            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( i ) );
            size_t index = 9 * i;

            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity(i) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PCs_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );

            index = 9 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PCs_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PCs_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );

            index = 9 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PCs_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer()   + index),
                        *(polygon->colors().pointer()   + index+1),
                        *(polygon->colors().pointer()   + index+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glColor4ub( *(polygon->colors().pointer()   + con3),
                        *(polygon->colors().pointer()   + con3+1),
                        *(polygon->colors().pointer()   + con3+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer()   + index),
                        *(polygon->colors().pointer()   + index+1),
                        *(polygon->colors().pointer()   + index+2),
                        polygon->opacity( i ) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity(con0/3) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity(con1/3) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity(con2/3) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glColor4ub( *(polygon->colors().pointer()   + con3),
                        *(polygon->colors().pointer()   + con3+1),
                        *(polygon->colors().pointer()   + con3+2),
                        polygon->opacity(con3/3) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nopacities(); i++ )
        {
            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( i ) );
            size_t index = 12 * i;

            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity(i) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PCs_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );

            index = 12 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PCs_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PCs_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );

            index = 12 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PCs_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_VC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer() + index),
                        *(polygon->normals().pointer() + index+1),
                        *(polygon->normals().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_VC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer() + con0),
                        *(polygon->colors().pointer() + con0+1),
                        *(polygon->colors().pointer() + con0+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_VC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer()   + index),
                        *(polygon->colors().pointer()   + index+1),
                        *(polygon->colors().pointer()   + index+2),
                        polygon->opacity( i ) );
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_VC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity(con0/3) );
            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity(con1/3) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity(con2/3) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_PC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_PC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_PC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nopacities(); i++ )
        {
            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( i ) );
            size_t index = 9 * i;

            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glNormal3f( *(polygon->normals().pointer()    + index+3),
                        *(polygon->normals().pointer()    + index+4),
                        *(polygon->normals().pointer()    + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glNormal3f( *(polygon->normals().pointer()    + index+6),
                        *(polygon->normals().pointer()    + index+7),
                        *(polygon->normals().pointer()    + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_PC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity(i) );
            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_PCs_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );

            index = 9 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glNormal3f( *(polygon->normals().pointer()    + index+3),
                        *(polygon->normals().pointer()    + index+4),
                        *(polygon->normals().pointer()    + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glNormal3f( *(polygon->normals().pointer()    + index+6),
                        *(polygon->normals().pointer()    + index+7),
                        *(polygon->normals().pointer()    + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_PCs_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_PCs_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );

            index = 9 * i;
            glNormal3f( *(polygon->normals().pointer()  + index),
                        *(polygon->normals().pointer()  + index+1),
                        *(polygon->normals().pointer()  + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glNormal3f( *(polygon->normals().pointer()  + index+3),
                        *(polygon->normals().pointer()  + index+4),
                        *(polygon->normals().pointer()  + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glNormal3f( *(polygon->normals().pointer()  + index+6),
                        *(polygon->normals().pointer()  + index+7),
                        *(polygon->normals().pointer()  + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_VN_PCs_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );
            glNormal3f( *(polygon->normals().pointer()  + con0),
                        *(polygon->normals().pointer()  + con0+1),
                        *(polygon->normals().pointer()  + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glNormal3f( *(polygon->normals().pointer()  + con1),
                        *(polygon->normals().pointer()  + con1+1),
                        *(polygon->normals().pointer()  + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glNormal3f( *(polygon->normals().pointer()  + con2),
                        *(polygon->normals().pointer()  + con2+1),
                        *(polygon->normals().pointer()  + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_VC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()  + index),
                        *(polygon->normals().pointer()  + index+1),
                        *(polygon->normals().pointer()  + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_VC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glColor4ub( *(polygon->colors().pointer() + con0),
                        *(polygon->colors().pointer() + con0+1),
                        *(polygon->colors().pointer() + con0+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()  + con0),
                        *(polygon->normals().pointer()  + con0+1),
                        *(polygon->normals().pointer()  + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()  + con1),
                        *(polygon->normals().pointer()  + con1+1),
                        *(polygon->normals().pointer()  + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()  + con2),
                        *(polygon->normals().pointer()  + con2+1),
                        *(polygon->normals().pointer()  + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glColor4ub( *(polygon->colors().pointer()   + con3),
                        *(polygon->colors().pointer()   + con3+1),
                        *(polygon->colors().pointer()   + con3+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()  + con3),
                        *(polygon->normals().pointer()  + con3+1),
                        *(polygon->normals().pointer()  + con3+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_VC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer()   + index),
                        *(polygon->colors().pointer()   + index+1),
                        *(polygon->colors().pointer()   + index+2),
                        polygon->opacity( i ) );
            glNormal3f( *(polygon->normals().pointer()  + index),
                        *(polygon->normals().pointer()  + index+1),
                        *(polygon->normals().pointer()  + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_VC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity(con0/3) );
            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity(con1/3) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity(con2/3) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glColor4ub( *(polygon->colors().pointer()   + con3),
                        *(polygon->colors().pointer()   + con3+1),
                        *(polygon->colors().pointer()   + con3+2),
                        polygon->opacity(con3/3) );
            glNormal3f( *(polygon->normals().pointer()    + con3),
                        *(polygon->normals().pointer()    + con3+1),
                        *(polygon->normals().pointer()    + con3+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_PC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nvertices(); i++ )
        {
            size_t index = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_PC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glNormal3f( *(polygon->normals().pointer()    + con3),
                        *(polygon->normals().pointer()    + con3+1),
                        *(polygon->normals().pointer()    + con3+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_PC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nopacities(); i++ )
        {
            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( i ) );
            size_t index = 12 * i;

            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glNormal3f( *(polygon->normals().pointer()    + index+3),
                        *(polygon->normals().pointer()    + index+4),
                        *(polygon->normals().pointer()    + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glNormal3f( *(polygon->normals().pointer()    + index+6),
                        *(polygon->normals().pointer()    + index+7),
                        *(polygon->normals().pointer()    + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glNormal3f( *(polygon->normals().pointer()    + index+9),
                        *(polygon->normals().pointer()    + index+10),
                        *(polygon->normals().pointer()    + index+11) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_PC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity(i) );
            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glNormal3f( *(polygon->normals().pointer()    + con3),
                        *(polygon->normals().pointer()    + con3+1),
                        *(polygon->normals().pointer()    + con3+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_PCs_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );

            index = 12 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glNormal3f( *(polygon->normals().pointer()    + index+3),
                        *(polygon->normals().pointer()    + index+4),
                        *(polygon->normals().pointer()    + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glNormal3f( *(polygon->normals().pointer()    + index+6),
                        *(polygon->normals().pointer()    + index+7),
                        *(polygon->normals().pointer()    + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glNormal3f( *(polygon->normals().pointer()    + index+9),
                        *(polygon->normals().pointer()    + index+10),
                        *(polygon->normals().pointer()    + index+11) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_PCs_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glNormal3f( *(polygon->normals().pointer()    + con3),
                        *(polygon->normals().pointer()    + con3+1),
                        *(polygon->normals().pointer()    + con3+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_PCs_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );

            index = 12 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glNormal3f( *(polygon->normals().pointer()    + index+3),
                        *(polygon->normals().pointer()    + index+4),
                        *(polygon->normals().pointer()    + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glNormal3f( *(polygon->normals().pointer()    + index+6),
                        *(polygon->normals().pointer()    + index+7),
                        *(polygon->normals().pointer()    + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glNormal3f( *(polygon->normals().pointer()    + index+9),
                        *(polygon->normals().pointer()    + index+10),
                        *(polygon->normals().pointer()    + index+11) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_VN_PCs_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glNormal3f( *(polygon->normals().pointer()    + con0),
                        *(polygon->normals().pointer()    + con0+1),
                        *(polygon->normals().pointer()    + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glNormal3f( *(polygon->normals().pointer()    + con1),
                        *(polygon->normals().pointer()    + con1+1),
                        *(polygon->normals().pointer()    + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glNormal3f( *(polygon->normals().pointer()    + con2),
                        *(polygon->normals().pointer()    + con2+1),
                        *(polygon->normals().pointer()    + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glNormal3f( *(polygon->normals().pointer()    + con3),
                        *(polygon->normals().pointer()    + con3+1),
                        *(polygon->normals().pointer()    + con3+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_VC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nnormals(); i++ )
        {
            size_t index = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );

            index = 9 * i;
            glColor4ub( *(polygon->colors().pointer()   + index),
                        *(polygon->colors().pointer()   + index+1),
                        *(polygon->colors().pointer()   + index+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glColor4ub( *(polygon->colors().pointer()   + index+3),
                        *(polygon->colors().pointer()   + index+4),
                        *(polygon->colors().pointer()   + index+5),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glColor4ub( *(polygon->colors().pointer()   + index+6),
                        *(polygon->colors().pointer()   + index+7),
                        *(polygon->colors().pointer()   + index+8),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_VC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_VC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nnormals(); i++ )
        {
            size_t nindex = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + nindex),
                        *(polygon->normals().pointer()    + nindex+1),
                        *(polygon->normals().pointer()    + nindex+2) );

            size_t vindex = 9 * i;
            glColor4ub( *(polygon->colors().pointer()   + vindex),
                        *(polygon->colors().pointer()   + vindex+1),
                        *(polygon->colors().pointer()   + vindex+2),
                        polygon->opacity( nindex ) );
            glVertex3f( *(polygon->coords().pointer() + vindex),
                        *(polygon->coords().pointer() + vindex+1),
                        *(polygon->coords().pointer() + vindex+2) );
            glColor4ub( *(polygon->colors().pointer()   + vindex+3),
                        *(polygon->colors().pointer()   + vindex+4),
                        *(polygon->colors().pointer()   + vindex+5),
                        polygon->opacity( nindex+1 ) );
            glVertex3f( *(polygon->coords().pointer() + vindex+3),
                        *(polygon->coords().pointer() + vindex+4),
                        *(polygon->coords().pointer() + vindex+5) );
            glColor4ub( *(polygon->colors().pointer()   + vindex+6),
                        *(polygon->colors().pointer()   + vindex+7),
                        *(polygon->colors().pointer()   + vindex+8),
                        polygon->opacity( nindex+2 ) );
            glVertex3f( *(polygon->coords().pointer() + vindex+6),
                        *(polygon->coords().pointer() + vindex+7),
                        *(polygon->coords().pointer() + vindex+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_VC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity(con0/3) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity(con1/3) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity(con2/3) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_PC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nnormals(); i++ )
        {
            size_t index = 3 * i;
            glNormal3f( *(polygon->normals().pointer() + index),
                        *(polygon->normals().pointer() + index+1),
                        *(polygon->normals().pointer() + index+2) );

            index = 9 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_PC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_PC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nopacities(); i++ )
        {
            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( i ) );

            size_t index = 3 * i;

            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );

            index = 9 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_PC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity(i) );
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_PCs_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()  + index),
                        *(polygon->normals().pointer()  + index+1),
                        *(polygon->normals().pointer()  + index+2) );

            index = 9 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_PCs_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()  + index),
                        *(polygon->normals().pointer()  + index+1),
                        *(polygon->normals().pointer()  + index+2) );

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_PCs_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );
            glNormal3f( *(polygon->normals().pointer()  + index),
                        *(polygon->normals().pointer()  + index+1),
                        *(polygon->normals().pointer()  + index+2) );

            index = 9 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Tri_PN_PCs_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_TRIANGLES );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;

            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );
            glNormal3f( *(polygon->normals().pointer()  + index),
                        *(polygon->normals().pointer()  + index+1),
                        *(polygon->normals().pointer()  + index+2) );

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_VC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nnormals(); i++ )
        {
            size_t index = 12 * i;
            glNormal3f( *(polygon->normals().pointer()    + i),
                        *(polygon->normals().pointer()    + i+1),
                        *(polygon->normals().pointer()    + i+2) );
            glColor4ub( *(polygon->colors().pointer()   + index),
                        *(polygon->colors().pointer()   + index+1),
                        *(polygon->colors().pointer()   + index+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glColor4ub( *(polygon->colors().pointer()   + index+3),
                        *(polygon->colors().pointer()   + index+4),
                        *(polygon->colors().pointer()   + index+5),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glColor4ub( *(polygon->colors().pointer()   + index+6),
                        *(polygon->colors().pointer()   + index+7),
                        *(polygon->colors().pointer()   + index+8),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glColor4ub( *(polygon->colors().pointer()   + index+9),
                        *(polygon->colors().pointer()   + index+10),
                        *(polygon->colors().pointer()   + index+11),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_VC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glColor4ub( *(polygon->colors().pointer()   + con3),
                        *(polygon->colors().pointer()   + con3+1),
                        *(polygon->colors().pointer()   + con3+2),
                        polygon->opacity( 0 ) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_VC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nnormals(); i++ )
        {
            size_t nindex = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + nindex),
                        *(polygon->normals().pointer()    + nindex+1),
                        *(polygon->normals().pointer()    + nindex+2) );

            size_t vindex = 12 * i;
            glColor4ub( *(polygon->colors().pointer()   + vindex),
                        *(polygon->colors().pointer()   + vindex+1),
                        *(polygon->colors().pointer()   + vindex+2),
                        polygon->opacity( nindex ) );
            glVertex3f( *(polygon->coords().pointer() + vindex),
                        *(polygon->coords().pointer() + vindex+1),
                        *(polygon->coords().pointer() + vindex+2) );
            glColor4ub( *(polygon->colors().pointer()   + vindex+3),
                        *(polygon->colors().pointer()   + vindex+4),
                        *(polygon->colors().pointer()   + vindex+5),
                        polygon->opacity( nindex+1 ) );
            glVertex3f( *(polygon->coords().pointer() + vindex+3),
                        *(polygon->coords().pointer() + vindex+4),
                        *(polygon->coords().pointer() + vindex+5) );
            glColor4ub( *(polygon->colors().pointer()   + vindex+6),
                        *(polygon->colors().pointer()   + vindex+7),
                        *(polygon->colors().pointer()   + vindex+8),
                        polygon->opacity( nindex+2 ) );
            glVertex3f( *(polygon->coords().pointer() + vindex+6),
                        *(polygon->coords().pointer() + vindex+7),
                        *(polygon->coords().pointer() + vindex+8) );
            glColor4ub( *(polygon->colors().pointer()   + vindex+9),
                        *(polygon->colors().pointer()   + vindex+10),
                        *(polygon->colors().pointer()   + vindex+11),
                        polygon->opacity( nindex+3 ) );
            glVertex3f( *(polygon->coords().pointer() + vindex+9),
                        *(polygon->coords().pointer() + vindex+10),
                        *(polygon->coords().pointer() + vindex+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_VC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glColor4ub( *(polygon->colors().pointer()   + con0),
                        *(polygon->colors().pointer()   + con0+1),
                        *(polygon->colors().pointer()   + con0+2),
                        polygon->opacity(con0/3) );
            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glColor4ub( *(polygon->colors().pointer()   + con1),
                        *(polygon->colors().pointer()   + con1+1),
                        *(polygon->colors().pointer()   + con1+2),
                        polygon->opacity(con1/3) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glColor4ub( *(polygon->colors().pointer()   + con2),
                        *(polygon->colors().pointer()   + con2+1),
                        *(polygon->colors().pointer()   + con2+2),
                        polygon->opacity(con2/3) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glColor4ub( *(polygon->colors().pointer()   + con3),
                        *(polygon->colors().pointer()   + con3+1),
                        *(polygon->colors().pointer()   + con3+2),
                        polygon->opacity(con3/3) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_PC_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nnormals(); i++ )
        {
            size_t index = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );

            index = 12 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_PC_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( 0 ) );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_PC_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nopacities(); i++ )
        {
            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity( i ) );

            size_t index = 3 * i;

            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );

            index = 12 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_PC_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        const kvs::RGBColor& col = polygon->color( 0 );

        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            glColor4ub( col.r(), col.g(), col.b(), polygon->opacity(i) );

            size_t index = 3 * i;
            glNormal3f( *(polygon->normals().pointer()    + index),
                        *(polygon->normals().pointer()    + index+1),
                        *(polygon->normals().pointer()    + index+2) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_PCs_O( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer()  + index),
                        *(polygon->normals().pointer()  + index+1),
                        *(polygon->normals().pointer()  + index+2) );

            index = 12 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_PCs_O_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( 0 ) );
            glNormal3f( *(polygon->normals().pointer() + index),
                        *(polygon->normals().pointer() + index+1),
                        *(polygon->normals().pointer() + index+2) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_PCs_Os( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->ncolors(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );
            glNormal3f( *(polygon->normals().pointer() + index),
                        *(polygon->normals().pointer() + index+1),
                        *(polygon->normals().pointer() + index+2) );

            index = 12 * i;
            glVertex3f( *(polygon->coords().pointer() + index),
                        *(polygon->coords().pointer() + index+1),
                        *(polygon->coords().pointer() + index+2) );
            glVertex3f( *(polygon->coords().pointer() + index+3),
                        *(polygon->coords().pointer() + index+4),
                        *(polygon->coords().pointer() + index+5) );
            glVertex3f( *(polygon->coords().pointer() + index+6),
                        *(polygon->coords().pointer() + index+7),
                        *(polygon->coords().pointer() + index+8) );
            glVertex3f( *(polygon->coords().pointer() + index+9),
                        *(polygon->coords().pointer() + index+10),
                        *(polygon->coords().pointer() + index+11) );
        }
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  
 *  @param  polygon     
 */
/*==========================================================================*/
void Rendering_Quad_PN_PCs_Os_Cs( const kvs::PolygonObject* polygon )
{
    glBegin( GL_QUADS );
    {
        for( size_t i = 0; i < polygon->nconnections(); i++ )
        {
            size_t index = 3 * i;
            glColor4ub( *(polygon->colors().pointer() + index),
                        *(polygon->colors().pointer() + index+1),
                        *(polygon->colors().pointer() + index+2),
                        polygon->opacity( i ) );
            glNormal3f( *(polygon->normals().pointer() + index),
                        *(polygon->normals().pointer() + index+1),
                        *(polygon->normals().pointer() + index+2) );

            index = 4 * i;
            size_t con0 = *(polygon->connections().pointer() + index)   * 3;
            size_t con1 = *(polygon->connections().pointer() + index+1) * 3;
            size_t con2 = *(polygon->connections().pointer() + index+2) * 3;
            size_t con3 = *(polygon->connections().pointer() + index+3) * 3;

            glVertex3f( *(polygon->coords().pointer() + con0),
                        *(polygon->coords().pointer() + con0+1),
                        *(polygon->coords().pointer() + con0+2) );
            glVertex3f( *(polygon->coords().pointer() + con1),
                        *(polygon->coords().pointer() + con1+1),
                        *(polygon->coords().pointer() + con1+2) );
            glVertex3f( *(polygon->coords().pointer() + con2),
                        *(polygon->coords().pointer() + con2+1),
                        *(polygon->coords().pointer() + con2+2) );
            glVertex3f( *(polygon->coords().pointer() + con3),
                        *(polygon->coords().pointer() + con3+1),
                        *(polygon->coords().pointer() + con3+2) );
        }
    }
    glEnd();
}

typedef void (*PolygonRenderingFunctionType)( const kvs::PolygonObject* polygon );

enum PolygonRenderingType
{
    Type_Tri_VC_O = 0,
    Type_Tri_VC_O_Cs,
    Type_Tri_VC_Os,
    Type_Tri_VC_Os_Cs,
    Type_Tri_PC_O,
    Type_Tri_PC_O_Cs,
    Type_Tri_PC_Os,
    Type_Tri_PC_Os_Cs,
    Type_Tri_PCs_O,
    Type_Tri_PCs_O_Cs,
    Type_Tri_PCs_Os,
    Type_Tri_PCs_Os_Cs,

    Type_Quad_VC_O,
    Type_Quad_VC_O_Cs,
    Type_Quad_VC_Os,
    Type_Quad_VC_Os_Cs,
    Type_Quad_PC_O,
    Type_Quad_PC_O_Cs,
    Type_Quad_PC_Os,
    Type_Quad_PC_Os_Cs,
    Type_Quad_PCs_O,
    Type_Quad_PCs_O_Cs,
    Type_Quad_PCs_Os,
    Type_Quad_PCs_Os_Cs,

    Type_Tri_VN_VC_O,
    Type_Tri_VN_VC_O_Cs,
    Type_Tri_VN_VC_Os,
    Type_Tri_VN_VC_Os_Cs,
    Type_Tri_VN_PC_O,
    Type_Tri_VN_PC_O_Cs,
    Type_Tri_VN_PC_Os,
    Type_Tri_VN_PC_Os_Cs,
    Type_Tri_VN_PCs_O,
    Type_Tri_VN_PCs_O_Cs,
    Type_Tri_VN_PCs_Os,
    Type_Tri_VN_PCs_Os_Cs,

    Type_Quad_VN_VC_O,
    Type_Quad_VN_VC_O_Cs,
    Type_Quad_VN_VC_Os,
    Type_Quad_VN_VC_Os_Cs,
    Type_Quad_VN_PC_O,
    Type_Quad_VN_PC_O_Cs,
    Type_Quad_VN_PC_Os,
    Type_Quad_VN_PC_Os_Cs,
    Type_Quad_VN_PCs_O,
    Type_Quad_VN_PCs_O_Cs,
    Type_Quad_VN_PCs_Os,
    Type_Quad_VN_PCs_Os_Cs,

    Type_Tri_PN_VC_O,
    Type_Tri_PN_VC_O_Cs,
    Type_Tri_PN_VC_Os,
    Type_Tri_PN_VC_Os_Cs,
    Type_Tri_PN_PC_O,
    Type_Tri_PN_PC_O_Cs,
    Type_Tri_PN_PC_Os,
    Type_Tri_PN_PC_Os_Cs,
    Type_Tri_PN_PCs_O,
    Type_Tri_PN_PCs_O_Cs,
    Type_Tri_PN_PCs_Os,
    Type_Tri_PN_PCs_Os_Cs,

    Type_Quad_PN_VC_O,
    Type_Quad_PN_VC_O_Cs,
    Type_Quad_PN_VC_Os,
    Type_Quad_PN_VC_Os_Cs,
    Type_Quad_PN_PC_O,
    Type_Quad_PN_PC_O_Cs,
    Type_Quad_PN_PC_Os,
    Type_Quad_PN_PC_Os_Cs,
    Type_Quad_PN_PCs_O,
    Type_Quad_PN_PCs_O_Cs,
    Type_Quad_PN_PCs_Os,
    Type_Quad_PN_PCs_Os_Cs,

    NumberOfRenderingTypes
};

PolygonRenderingFunctionType Rendering[NumberOfRenderingTypes] =
{
    &Rendering_Tri_VC_O,
    &Rendering_Tri_VC_O_Cs,
    &Rendering_Tri_VC_Os,
    &Rendering_Tri_VC_Os_Cs,
    &Rendering_Tri_PC_O,
    &Rendering_Tri_PC_O_Cs,
    &Rendering_Tri_PC_Os,
    &Rendering_Tri_PC_Os_Cs,
    &Rendering_Tri_PCs_O,
    &Rendering_Tri_PCs_O_Cs,
    &Rendering_Tri_PCs_Os,
    &Rendering_Tri_PCs_Os_Cs,

    &Rendering_Quad_VC_O,
    &Rendering_Quad_VC_O_Cs,
    &Rendering_Quad_VC_Os,
    &Rendering_Quad_VC_Os_Cs,
    &Rendering_Quad_PC_O,
    &Rendering_Quad_PC_O_Cs,
    &Rendering_Quad_PC_Os,
    &Rendering_Quad_PC_Os_Cs,
    &Rendering_Quad_PCs_O,
    &Rendering_Quad_PCs_O_Cs,
    &Rendering_Quad_PCs_Os,
    &Rendering_Quad_PCs_Os_Cs,

    &Rendering_Tri_VN_VC_O,
    &Rendering_Tri_VN_VC_O_Cs,
    &Rendering_Tri_VN_VC_Os,
    &Rendering_Tri_VN_VC_Os_Cs,
    &Rendering_Tri_VN_PC_O,
    &Rendering_Tri_VN_PC_O_Cs,
    &Rendering_Tri_VN_PC_Os,
    &Rendering_Tri_VN_PC_Os_Cs,
    &Rendering_Tri_VN_PCs_O,
    &Rendering_Tri_VN_PCs_O_Cs,
    &Rendering_Tri_VN_PCs_Os,
    &Rendering_Tri_VN_PCs_Os_Cs,

    &Rendering_Quad_VN_VC_O,
    &Rendering_Quad_VN_VC_O_Cs,
    &Rendering_Quad_VN_VC_Os,
    &Rendering_Quad_VN_VC_Os_Cs,
    &Rendering_Quad_VN_PC_O,
    &Rendering_Quad_VN_PC_O_Cs,
    &Rendering_Quad_VN_PC_Os,
    &Rendering_Quad_VN_PC_Os_Cs,
    &Rendering_Quad_VN_PCs_O,
    &Rendering_Quad_VN_PCs_O_Cs,
    &Rendering_Quad_VN_PCs_Os,
    &Rendering_Quad_VN_PCs_Os_Cs,

    &Rendering_Tri_PN_VC_O,
    &Rendering_Tri_PN_VC_O_Cs,
    &Rendering_Tri_PN_VC_Os,
    &Rendering_Tri_PN_VC_Os_Cs,
    &Rendering_Tri_PN_PC_O,
    &Rendering_Tri_PN_PC_O_Cs,
    &Rendering_Tri_PN_PC_Os,
    &Rendering_Tri_PN_PC_Os_Cs,
    &Rendering_Tri_PN_PCs_O,
    &Rendering_Tri_PN_PCs_O_Cs,
    &Rendering_Tri_PN_PCs_Os,
    &Rendering_Tri_PN_PCs_Os_Cs,

    &Rendering_Quad_PN_VC_O,
    &Rendering_Quad_PN_VC_O_Cs,
    &Rendering_Quad_PN_VC_Os,
    &Rendering_Quad_PN_VC_Os_Cs,
    &Rendering_Quad_PN_PC_O,
    &Rendering_Quad_PN_PC_O_Cs,
    &Rendering_Quad_PN_PC_Os,
    &Rendering_Quad_PN_PC_Os_Cs,
    &Rendering_Quad_PN_PCs_O,
    &Rendering_Quad_PN_PCs_O_Cs,
    &Rendering_Quad_PN_PCs_Os,
    &Rendering_Quad_PN_PCs_Os_Cs,
};

PolygonRenderingType GetPolygonRenderingType( const kvs::PolygonObject* polygon )
{
    const size_t nopacities = polygon->nopacities();
    const size_t ncolors    = polygon->ncolors();
    const size_t nconnects  = polygon->nconnections();
    const kvs::PolygonObject::PolygonType polygon_type = polygon->polygonType();
    const kvs::PolygonObject::NormalType  normal_type  = polygon->normalType();
    const kvs::PolygonObject::ColorType   color_type   = polygon->colorType();

    if( polygon->normals().size() == 0 )
    {
        if( polygon_type == kvs::PolygonObject::Triangle )
        {
            if( color_type == kvs::PolygonObject::VertexColor )
            {
                if( nopacities == 1 )
                    return( ( nconnects == 0 ) ? Type_Tri_VC_O : Type_Tri_VC_O_Cs );
                else
                    return( ( nconnects == 0 ) ? Type_Tri_VC_Os : Type_Tri_VC_Os_Cs );
            }
            else if( color_type == kvs::PolygonObject::PolygonColor )
            {
                if( ncolors == 1 )
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Tri_PC_O : Type_Tri_PC_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Tri_PC_Os : Type_Tri_PC_Os_Cs );
                }
                else
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Tri_PCs_O : Type_Tri_PCs_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Tri_PCs_Os : Type_Tri_PCs_Os_Cs );
                }
            }
        }
        else if( polygon_type == kvs::PolygonObject::Quadrangle )
        {
            if( color_type == kvs::PolygonObject::VertexColor )
            {
                if( nopacities == 1 )
                    return( ( nconnects == 0 ) ? Type_Quad_VC_O : Type_Quad_VC_O_Cs );
                else
                    return( ( nconnects == 0 ) ? Type_Quad_VC_Os : Type_Quad_VC_Os_Cs );
            }
            else if( color_type == kvs::PolygonObject::PolygonColor )
            {
                if( ncolors == 1 )
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Quad_PC_O : Type_Quad_PC_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Quad_PC_Os : Type_Quad_PC_Os_Cs );
                }
                else
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Quad_PCs_O : Type_Quad_PCs_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Quad_PCs_Os : Type_Quad_PCs_Os_Cs );
                }
            }
        }
    }

    else if( normal_type == kvs::PolygonObject::VertexNormal )
    {
        if( polygon_type == kvs::PolygonObject::Triangle )
        {
            if( color_type == kvs::PolygonObject::VertexColor )
            {
                if( nopacities == 1 )
                    return( ( nconnects == 0 ) ? Type_Tri_VN_VC_O : Type_Tri_VN_VC_O_Cs );
                else
                    return( ( nconnects == 0 ) ? Type_Tri_VN_VC_Os : Type_Tri_VN_VC_Os_Cs );
            }
            else if( color_type == kvs::PolygonObject::PolygonColor )
            {
                if( ncolors == 1 )
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Tri_VN_PC_O : Type_Tri_VN_PC_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Tri_VN_PC_Os : Type_Tri_VN_PC_Os_Cs );
                }
                else
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Tri_VN_PCs_O : Type_Tri_VN_PCs_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Tri_VN_PCs_Os : Type_Tri_VN_PCs_Os_Cs );
                }
            }
        }
        else if( polygon_type == kvs::PolygonObject::Quadrangle )
        {
            if( color_type == kvs::PolygonObject::VertexColor )
            {
                if( nopacities == 1 )
                    return( ( nconnects == 0 ) ? Type_Quad_VN_VC_O : Type_Quad_VN_VC_O_Cs );
                else
                    return( ( nconnects == 0 ) ? Type_Quad_VN_VC_Os : Type_Quad_VN_VC_Os_Cs );
            }
            else if( color_type == kvs::PolygonObject::PolygonColor )
            {
                if( ncolors == 1 )
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Quad_VN_PC_O : Type_Quad_VN_PC_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Quad_VN_PC_Os : Type_Quad_VN_PC_Os_Cs );
                }
                else
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Quad_VN_PCs_O : Type_Quad_VN_PCs_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Quad_VN_PCs_Os : Type_Quad_VN_PCs_Os_Cs );
                }
            }
        }
    }

    else if( normal_type == kvs::PolygonObject::PolygonNormal )
    {
        if( polygon_type == kvs::PolygonObject::Triangle )
        {
            if( color_type == kvs::PolygonObject::VertexColor )
            {
                if( nopacities == 1 )
                    return( ( nconnects == 0 ) ? Type_Tri_PN_VC_O : Type_Tri_PN_VC_O_Cs );
                else
                    return( ( nconnects == 0 ) ? Type_Tri_PN_VC_Os : Type_Tri_PN_VC_Os_Cs );
            }
            else if( color_type == kvs::PolygonObject::PolygonColor )
            {
                if( ncolors == 1 )
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Tri_PN_PC_O : Type_Tri_PN_PC_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Tri_PN_PC_Os : Type_Tri_PN_PC_Os_Cs );
                }
                else
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Tri_PN_PCs_O : Type_Tri_PN_PCs_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Tri_PN_PCs_Os : Type_Tri_PN_PCs_Os_Cs );
                }
            }
        }

        else if( polygon_type == kvs::PolygonObject::Quadrangle )
        {
            if( color_type == kvs::PolygonObject::VertexColor )
            {
                if( nopacities == 1 )
                    return( ( nconnects == 0 ) ? Type_Quad_PN_VC_O : Type_Quad_PN_VC_O_Cs );
                else
                    return( ( nconnects == 0 ) ? Type_Quad_PN_VC_Os : Type_Quad_PN_VC_Os_Cs );
            }
            else if( color_type == kvs::PolygonObject::PolygonColor )
            {
                if( ncolors == 1 )
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Quad_PN_PC_O : Type_Quad_PN_PC_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Quad_PN_PC_Os : Type_Quad_PN_PC_Os_Cs );
                }
                else
                {
                    if( nopacities == 1 )
                        return( ( nconnects == 0 ) ? Type_Quad_PN_PCs_O : Type_Quad_PN_PCs_O_Cs );
                    else
                        return( ( nconnects == 0 ) ? Type_Quad_PN_PCs_Os : Type_Quad_PN_PCs_Os_Cs );
                }
            }
        }
    }

    return( Type_Tri_VC_O );
};

void PolygonRenderingFunction( const kvs::PolygonObject* polygon )
{
    if( polygon->nvertices() > 0 )
    {
        PolygonRenderingType type = GetPolygonRenderingType( polygon );
        Rendering[type]( polygon );
    }
};

} // end of namespace

#endif // KVS_CORE_POLYGON_RENDERING_FUNCTION_H_INCLUDE
