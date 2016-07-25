#!/usr/bin/env bash
if [ ! -d ../../examples ]; then
    echo "You must be inside an example project to execute this script."
    exit
fi
make cleanup
make
cd ../../
make cleanup
make