#!/bin/bash
cd ..
make imageTestBlur &> /dev/null  # don't appear
./imageTestBlur $1 $2 $3 $4 $5 $6 > testBlur/data_blurTests.txt