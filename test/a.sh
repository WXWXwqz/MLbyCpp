#!/bin/bash
make
./test
make clean
gnuplot -persist <<EOF
plot sin(x)
