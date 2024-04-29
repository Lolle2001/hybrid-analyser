#!/bin/bash

case $(uname) in
    Linux)
        make -f make/hybridp-linux.make -j12
        ;;
    Darwin)
        make -f make/hybridp-apple.make -j12
        ;;
    *)
        echo "Unsupported operating system"
        ;;
esac