#!/bin/sh
set -x #debug

if [[ $# -lt 2 ]]
then
   echo 'usage: $0 <target> <...path/to/src>'
   exit 1
fi

target=$1
path=$2
rebuild=$3

if [ $target == 'client' ]; then
  if [ "$rebuild" == 'rebuild' ]; then
    rm -rf ${path}/client/build
    cmake -S ${path}/client -B ${path}/client/build
  fi
  cmake --build ${path}/client/build
elif [ $target == 'server' ]; then
  if [ "$rebuild" == 'rebuild' ]; then
    rm -rf ${path}/server/build
    cmake -S ${path}/server -B ${path}/server/build
  fi
  cmake --build ${path}/server/build
elif [ $target == 'both' ]; then
  if [ "$rebuild" == 'rebuild' ]; then
    rm -rf ${path}/server/build ${path}/client/build
    cmake -S ${path}/server -B ${path}/server/build
    cmake -S ${path}/client -B ${path}/client/build
  fi
  cmake --build ${path}/client/build
  cmake --build ${path}/server/build
else
  echo 'usage: target in [client | server | both]'
  exit 1
fi