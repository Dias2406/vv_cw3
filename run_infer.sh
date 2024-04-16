#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

# Use the argument in the infer command
infer run -- gcc -c "$1"


