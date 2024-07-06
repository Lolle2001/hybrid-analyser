#!/bin/bash

case $(uname) in
    Linux)
        make -f make/analyser-linux.make -j12
        ;;
    Darwin)
        make -f make/hybridp-apple.make -j12
        ;;
    *)
        echo "Unsupported operating system"
        ;;
esac