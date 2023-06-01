#!/bin/bash

# Build
cd src
make clean && \
make all
cp main ../main
cd ..

# gcc -g movement.c -lcurses -o movement