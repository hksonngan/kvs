#!/bin/bash
#*****************************************************************************/
#
#  @file   oclrun_tdw204.sh
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
ConfFile="../oclconf/oclconf_tdw204.xml"
Nodes=( SlavePC01 SlavePC02 )
Port=28980

# Master function
Master() {
    OCLCONF_URI=$ConfFile LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OCLTOP/lib $OCLTOP/bin/master
}

# Renderer function
Renderer() {
    CurrentPath=`pwd`
    for (( i = 0; i < ${#Nodes[*]}; i++ ))
    {
	echo "${Nodes[i]}"
	ssh ${Nodes[i]} "cd $CurrentPath; OCLCONF_URI=$ConfFile OCLCONF_RENDERER=${Nodes[i]} LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OCLTOP/lib DISPLAY=:0.0 $OCLTOP/bin/renderer -p $Port" &
    }

    echo -n 'Enter to exit'
    read line

    for (( i = 0; i < ${#Nodes[*]}; i++ ))
    {
	ssh ${Nodes[i]} 'killall -KILL renderer'
    }
}

# Main process
case $1 in
master) Master;;
renderer) Renderer;;
*) echo "Usage) $0 [master|renderer]";;
esac
