#!/bin/bash
# Copyright (C) 2011 Ion Torrent Systems, Inc. All Rights Reserved
#AUTORUNDISABLE
#as of 6/21 the stack size being set on SGE nodes is too large, setting manually to the default
ulimit -s 8192
#normal plugin script
VERSION="2.2.3-31037"
$DIRNAME/alignment.py startplugin.json >> $TSP_FILEPATH_PLUGIN_DIR/launch_sh_output.txt
cp $DIRNAME/Alignment_block.php $TSP_FILEPATH_PLUGIN_DIR/
cp -r $DIRNAME/library $TSP_FILEPATH_PLUGIN_DIR/
