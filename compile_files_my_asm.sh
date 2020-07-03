#!/bin/bash

rm -f "./cor_files_my/*.cor"

for filename in ./champs/*.s; do
    ./asm "$filename"
done

for filename in ./*.cor; do
    mv "$filename" "./cor_files_my/$filename"
done  