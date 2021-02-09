#!/bin/sh

option="$1";

if [ "$option" = "-f" ]; then
rm -rf cmake-build-debug
rm -rf external
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cd ..
fi

cd cmake-build-debug
make
cd ..

#Run Game
./run_app.sh