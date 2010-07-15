#!/bin/bash

ConfFile="../oclconf/oclconf_local3x2.xml"
Nodes=( local_00 local_01 local_02 local_10 local_11 local_12 )
Ports=( 28980    28981    28982    28983    28984    28985 )

OCLCONF_URI=$ConfFile LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OCLTOP/lib $OCLTOP/bin/master -r localhost:${Ports[0]} -r localhost:${Ports[1]} -r localhost:${Ports[2]} -r localhost:${Ports[3]} -r localhost:${Ports[4]} -r localhost:${Ports[5]}
