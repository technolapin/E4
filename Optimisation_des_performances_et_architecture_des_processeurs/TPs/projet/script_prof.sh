#!/bin/bash

echo Example 1

echo "Cache size :  1024B"
echo "1024" &> $2
valgrind --tool=cachegrind --D1=1024,1,32 ./$1 &> way_1
valgrind --tool=cachegrind --D1=1024,2,32 ./$1 &> way_2
valgrind --tool=cachegrind --D1=1024,4,32 ./$1 &> way_4
valgrind --tool=cachegrind --D1=1024,8,32 ./$1 &> way_8

grep D1 way_* | grep misses &>> $2

echo "Cache size :  2048B"
echo "2048" &>> $2
valgrind --tool=cachegrind --D1=2048,1,32 ./$1 &> way_1
valgrind --tool=cachegrind --D1=2048,2,32 ./$1 &> way_2
valgrind --tool=cachegrind --D1=2048,4,32 ./$1 &> way_4
valgrind --tool=cachegrind --D1=2048,8,32 ./$1 &> way_8

grep D1 way_* | grep misses &>> $2 

echo "Cache size :  4096B"
echo "4096" &>> $2
valgrind --tool=cachegrind --D1=4096,1,32 ./$1 &> way_1
valgrind --tool=cachegrind --D1=4096,2,32 ./$1 &> way_2
valgrind --tool=cachegrind --D1=4096,4,32 ./$1 &> way_4
valgrind --tool=cachegrind --D1=4096,8,32 ./$1 &> way_8

grep D1 way_* | grep misses &>> $2 

echo "Cache size :  8192B"
echo "8192" &>> $2
valgrind --tool=cachegrind --D1=8192,1,32 ./$1 &> way_1
valgrind --tool=cachegrind --D1=8192,2,32 ./$1 &> way_2
valgrind --tool=cachegrind --D1=8192,4,32 ./$1 &> way_4
valgrind --tool=cachegrind --D1=8192,8,32 ./$1 &> way_8

grep D1 way_* | grep misses &>> $2 

echo Removing cachegrind files 
rm cachegrind.out*
