#!/bin/bash

for filename in ./champs/*.s; do
    ./native_asm/asm "$filename"
done