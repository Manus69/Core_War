#!/bin/bash

for filename in ./unit_tests/*.s; do
    ./native_asm/asm "$filename"
done
