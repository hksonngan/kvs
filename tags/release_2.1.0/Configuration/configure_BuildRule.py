#!/usr/bin/python

import sys
import os
import string


#=============================================================================
#  Initialize.
#=============================================================================
if len( sys.argv ) != 2:
    sys.exit( 0 )

source_path = sys.argv[1]
find_path   = "../Source/" + source_path


#=============================================================================
#  Set object_list, object_dir_list, header_dir_list.
#=============================================================================
#  Initialize.
object_list     = []
object_dir_list = []
header_dir_list = []
vert_shader_dir_list = []
geom_shader_dir_list = []
frag_shader_dir_list = []

#  Search sources.
for root, dirs, files in os.walk( find_path ):

    for filename in files:

        file_path = os.path.join( root, filename )

        if os.path.splitext( filename )[1] == ".cpp":

            #  Append to object_list.
            object_list.append( file_path.replace( ".cpp", ".o" ) )

            #  Append to object_dir_list.
            if not root in object_dir_list:
                object_dir_list.append( root )

        if os.path.splitext( filename )[1] == ".h":

            #  Append to header_dir_list.
            if not root in header_dir_list:
                header_dir_list.append( root )

        if os.path.splitext( filename )[1] == ".vert":

            #  Append to vert_shader_dir_list.
            if not root in vert_shader_dir_list:
                vert_shader_dir_list.append( root )

        if os.path.splitext( filename )[1] == ".geom":

            #  Append to geom_shader_dir_list.
            if not root in geom_shader_dir_list:
                geom_shader_dir_list.append( root )

        if os.path.splitext( filename )[1] == ".frag":

            #  Append to frag_shader_dir_list.
            if not root in frag_shader_dir_list:
                frag_shader_dir_list.append( root )


#  Strip find_path.
object_list     = list( map( lambda x: x.replace( find_path, "." ), object_list ) )
object_dir_list = list( map( lambda x: x.replace( find_path, "." ), object_dir_list ) )
header_dir_list = list( map( lambda x: x.replace( find_path, "." ), header_dir_list ) )
vert_shader_dir_list = list( map( lambda x: x.replace( find_path, "." ), vert_shader_dir_list ) )
geom_shader_dir_list = list( map( lambda x: x.replace( find_path, "." ), geom_shader_dir_list ) )
frag_shader_dir_list = list( map( lambda x: x.replace( find_path, "." ), vert_shader_dir_list ) )

#  Sort.
object_list.sort()
object_dir_list.sort()
object_dir_list.reverse()
header_dir_list.sort()
vert_shader_dir_list.sort()
geom_shader_dir_list.sort()
frag_shader_dir_list.sort()


#=============================================================================
#  Write makefile for make.
#=============================================================================
sys.stdout = open( find_path + "/BuildRule.mk", "w" )

object_list     = list( map( lambda x: x.replace( "\\", "/" ), object_list ) )
object_dir_list = list( map( lambda x: x.replace( "\\", "/" ), object_dir_list ) )
header_dir_list = list( map( lambda x: x.replace( "\\", "/" ), header_dir_list ) )
vert_shader_dir_list = list( map( lambda x: x.replace( "\\", "/" ), vert_shader_dir_list ) )
geom_shader_dir_list = list( map( lambda x: x.replace( "\\", "/" ), geom_shader_dir_list ) )
frag_shader_dir_list = list( map( lambda x: x.replace( "\\", "/" ), frag_shader_dir_list ) )


#  Write a caution.
print( "#  DON'T EDIT THIS FILE." )
print( "#  THIS IS GENERATED BY \"Configuration/configure_BuildRule.py\"." )
print( "" )

#  Write object files.
print( "" )
print( "OBJECTS := \\" )

for filename in object_list:
    print( "$(OUTDIR)/%s \\" % filename )

print( "" )
print( "" )


#  Write build rules.
for dirname in object_dir_list:
    print( "" )
    print( "$(OUTDIR)/%s/%%.o: %s/%%.cpp %s/%%.h" % ( dirname, dirname, dirname ) )
    print( "\t$(MKDIR) $(OUTDIR)/%s" % dirname )
    print( "\t$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<" )

print( "" )


#  Write "install" target.
print( "" )
print( "install::" )

for dirname in header_dir_list:
    print( "\t$(MKDIR) $(INSTALL_DIR)/include/%s/%s" % ( source_path, dirname ) )
    print( "\t$(INSTALL) %s/*.h $(INSTALL_DIR)/include/%s/%s" % ( dirname, source_path, dirname ) )

for dirname in vert_shader_dir_list:
    print( "\t$(MKDIR) $(INSTALL_DIR)/include/%s/%s" % ( source_path, dirname ) )
    print( "\t$(INSTALL) %s/*.vert $(INSTALL_DIR)/include/%s/%s" % ( dirname, source_path, dirname ) )

for dirname in geom_shader_dir_list:
    print( "\t$(MKDIR) $(INSTALL_DIR)/include/%s/%s" % ( source_path, dirname ) )
    print( "\t$(INSTALL) %s/*.geom $(INSTALL_DIR)/include/%s/%s" % ( dirname, source_path, dirname ) )

for dirname in frag_shader_dir_list:
    print( "\t$(MKDIR) $(INSTALL_DIR)/include/%s/%s" % ( source_path, dirname ) )
    print( "\t$(INSTALL) %s/*.frag $(INSTALL_DIR)/include/%s/%s" % ( dirname, source_path, dirname ) )


#=============================================================================
#  Write makefile for nmake.
#=============================================================================
sys.stdout = open( find_path + "/BuildRule.vc.mk", "w" )

object_list     = list( map( lambda x: x.replace( "/", "\\" ).replace( ".o", ".obj" ), object_list ) )
object_dir_list = list( map( lambda x: x.replace( "/", "\\" ), object_dir_list ) )
header_dir_list = list( map( lambda x: x.replace( "/", "\\" ), header_dir_list ) )
vert_shader_dir_list = list( map( lambda x: x.replace( "/", "\\" ), vert_shader_dir_list ) )
geom_shader_dir_list = list( map( lambda x: x.replace( "/", "\\" ), geom_shader_dir_list ) )
frag_shader_dir_list = list( map( lambda x: x.replace( "/", "\\" ), frag_shader_dir_list ) )


#  Write a caution.
print( "#  DON'T EDIT THIS FILE." )
print( "#  THIS IS GENERATED BY \"Configuration/configure_BuildRule.py\"." )
print( "" )


#  Write object files.
print( "" )
print( "OBJECTS = \\" )

for filename in object_list:
    print( "$(OUTDIR)\\%s \\" % filename )

print( "" )
print( "" )


#  Write build rules.
for dirname in object_dir_list:
    print( "" )
    print( "{%s\\}.cpp{$(OUTDIR)\\%s\\}.obj::" % ( dirname, dirname ) )
    print( "\tIF NOT EXIST $(OUTDIR)\\%s $(MKDIR) $(OUTDIR)\\%s" %( dirname, dirname ) )
    print( "\t$(CPP) /c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) /Fo$(OUTDIR)\\%s\\ @<<" % dirname )
    print( "$<" )
    print( "<<" )

print( "" )


#  Write "install" target.
print( "" )
print( "install::" )

for dirname in header_dir_list:
    print( "\tIF NOT EXIST $(INSTALL_DIR)\\include\\%s\\%s $(MKDIR) $(INSTALL_DIR)\\include\\%s\\%s" % ( source_path, dirname, source_path, dirname ) )
    print( "\t$(INSTALL) %s\\*.h $(INSTALL_DIR)\\include\\%s\\%s" % ( dirname, source_path, dirname ) )

for dirname in vert_shader_dir_list:
    print( "\tIF NOT EXIST $(INSTALL_DIR)\\include\\%s\\%s $(MKDIR) $(INSTALL_DIR)\\include\\%s\\%s" % ( source_path, dirname, source_path, dirname ) )
    print( "\t$(INSTALL) %s\\*.vert $(INSTALL_DIR)\\include\\%s\\%s" % ( dirname, source_path, dirname ) )

for dirname in geom_shader_dir_list:
    print( "\tIF NOT EXIST $(INSTALL_DIR)\\include\\%s\\%s $(MKDIR) $(INSTALL_DIR)\\include\\%s\\%s" % ( source_path, dirname, source_path, dirname ) )
    print( "\t$(INSTALL) %s\\*.geom $(INSTALL_DIR)\\include\\%s\\%s" % ( dirname, source_path, dirname ) )

for dirname in frag_shader_dir_list:
    print( "\tIF NOT EXIST $(INSTALL_DIR)\\include\\%s\\%s $(MKDIR) $(INSTALL_DIR)\\include\\%s\\%s" % ( source_path, dirname, source_path, dirname ) )
    print( "\t$(INSTALL) %s\\*.frag $(INSTALL_DIR)\\include\\%s\\%s" % ( dirname, source_path, dirname ) )