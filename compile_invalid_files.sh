
for filename in ./invalid/*.s; do
    valgrind ./asm "$filename"
done