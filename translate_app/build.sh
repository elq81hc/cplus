# bin/bash

# build project
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build