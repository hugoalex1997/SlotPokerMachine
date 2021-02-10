#!/bin/bash

rm -rf build
rm -rf external
mkdir build

cmake -B build
cd build
make
cd ..

#Run Game
./build/bin/PokerSlot