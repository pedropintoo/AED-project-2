#!/bin/bash
cd ..
make GraphTestTopoInsuccessBest &> /dev/null  # don't appear
./GraphTestTopoInsuccessBest $1 $2 $3 > testTopo/data_topoTests.txt
