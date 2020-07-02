#!/bin/bash

for filename in ./unit_tests/*.s; do
    ./native_asm/asm "$filename"
done

for filename in ./unit_tests/*.cor; do
    mv "$filename" "./unit_tests_native_cor_files/$filename"
done  