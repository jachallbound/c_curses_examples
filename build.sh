#!/bin/bash

# Move config.c into src/
cp config.h src/config.h

# Build
cd src
make clean && \
make all

# Copy executable
cp main ../main
cd ..

# gcc -g movement.c -lcurses -o movement