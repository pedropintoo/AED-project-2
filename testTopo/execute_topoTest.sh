#!/bin/bash
cd ..
make GraphTestTopo &> /dev/null  # don't appear
./GraphTestTopo $1 $2 $3 $4 > testTopo/data_topoTests.txt
