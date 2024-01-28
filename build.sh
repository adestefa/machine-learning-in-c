#!/bin/sh


set -xe 

#clang -Wall -Wextra -o out/twice src/twice.c
#clang -Wall -Wextra -o out/gates src/gates.c
clang -Wall -Wextra -o out/xor src/xor.c 

./out/xor