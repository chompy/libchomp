#!/usr/bin/env bash
if [[ "$OSTYPE" == "linux-gnu" ]]; then
    echo "linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "macosx"
elif [[ "$OSTYPE" == "cygwin" ]]; then
    echo "win32"
elif [[ "$OSTYPE" == "msys" ]]; then
    echo "win32"
elif [[ "$OSTYPE" == "win32" ]]; then
    echo "win32"
else
    echo "unknown"
fi