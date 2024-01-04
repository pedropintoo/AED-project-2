#!/bin/bash
cd ..
make GraphTestTopoSuccess &> /dev/null  # don't appear
./GraphTestTopoSuccess $1 $2 $3 $4 $5 > testTopo/data_topoTests.txt
