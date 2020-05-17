#!/bin/bash

for filename in ./champs/*.s; do
    ./asm "$filename"
done