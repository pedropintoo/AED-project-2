#!/bin/bash
cd ..
make GraphTestTopoInsuccessWorst &> /dev/null  # don't appear
./GraphTestTopoInsuccessWorst $1 $2 $3 $4 $5 > testTopo/data_topoTests.txt
