#!/bin/bash
set -e

make clean
make test
sleep 1
printf "Compilation Complete\n\n\n"

./bin/test
