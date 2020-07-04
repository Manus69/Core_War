#!/bin/bash

for filename in ./unit_tests_my_cor_files/*.cor; do
    valgrind ./asm -n "te" "$filename"
done