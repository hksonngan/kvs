#!/bin/bash
#*****************************************************************************/
#
#  @file   run_local3x2.sh
#  @author Naohisa Sakamoto
#  @brief  Script to execute master/renderer program for OpenCABIN
#
#-----------------------------------------------------------------------------
#
#  Copyright 2007 Visualization Laboratory, Kyoto University.
#  All rights reserved.
#  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
#
#  $Id$
#
#*****************************************************************************/

# Global parameters
ConfFile="../oclconf/oclconf_local3x2.xml"
Nodes=( local_00 local_01 local_02 local_10 local_11 local_12 )
Ports=( 28980    28981    28982    28983    28984    28985 )

# Master function
Master() {
    OCLCONF_URI=$ConfFile LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OCLTOP/lib $OCLTOP/bin/master -r localhost:${Ports[0]} -r localhost:${Ports[1]} -r localhost:${Ports[2]} -r localhost:${Ports[3]} -r localhost:${Ports[4]} -r localhost:${Ports[5]}
}

# Renderer function
Renderer() {
    CurrentPath=`pwd`
    for (( i = 0; i < ${#Nodes[*]}; i++ ))
    {
	echo "${Nodes[i]}"
	ssh localhost "cd $CurrentPath; OCLCONF_URI=$ConfFile OCLCONF_RENDERER=${Nodes[i]} LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OCLTOP/lib DISPLAY=:0.0 $OCLTOP/bin/renderer -p ${Ports[i]}" &
    }

    echo -n 'Enter to exit'
    read line

    killall -KILL renderer
}

# Main process
case $1 in
master) Master;;
renderer) Renderer;;
*) echo "Usage) $0 [master|renderer]";;
esac
