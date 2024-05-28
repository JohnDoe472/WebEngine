#! /bin/bash

declare ScriptDir=$(dirname "$0")

if [ -d "$ScriptDir/bin" ]; then
    rm -rf $ScriptDir/bin 
fi

if [ -d "$ScriptDir/build" ]; then
    rm -rf $ScriptDir/build 
fi

emcmake cmake -Bbuild
cmake --build build
