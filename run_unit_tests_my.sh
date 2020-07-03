#!/bin/bash

rm -f "./unit_tests_my_cor_files/*.cor"

for filename in ./unit_tests/*.s; do
    ./asm "$filename"
done

for filename in ./*.cor; do
    mv "$filename" "./unit_tests_my_cor_files/$filename"
done  