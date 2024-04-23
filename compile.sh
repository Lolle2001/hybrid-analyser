#!/bin/bash

if [[ $(uname) -eq "Linux" ]]
then
    make -f hybridp-linux.make -j12
elif [[ $(uname) -eq "Darwin" ]]
then
    make -f hybridp-apple.make -j12
fi