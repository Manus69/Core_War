#!/bin/bash

for filename in ./cor_files_native/*.cor; do
    diff "$filename" "./cor_files_my/$(filename)"
done