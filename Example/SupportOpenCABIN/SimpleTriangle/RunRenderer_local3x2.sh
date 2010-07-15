#!/bin/bash

ConfFile="../oclconf/oclconf_local3x2.xml"
Nodes=( local_00 local_01 local_02 local_10 local_11 local_12 )
Ports=( 28980    28981    28982    28983    28984    28985 )

CurrentPath=`pwd`
for (( i = 0; i < ${#Nodes[*]}; i++ ))
{
    echo "${Nodes[i]}"
    ssh localhost "cd $CurrentPath; OCLCONF_URI=$ConfFile OCLCONF_RENDERER=${Nodes[i]} LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OCLTOP/lib DISPLAY=:0.0 $OCLTOP/bin/renderer -p ${Ports[i]}" &
}

echo -n 'Enter to exit'
read line

killall -KILL renderer
