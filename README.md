Group members: Emmy Woods, Chris Cornell, Brandon Roth

how to build and run matrix multiplication:

the sequential version:
gcc mmseq.c -o mmseq
./mmseq

the OpenMP version:
gcc mmomp.c -o mmomp -fopenmp
./mmomp

the pthread version:
gcc mmpthread.c -lpthread -o mmpthread
./mmpthread

How to test:

time ./mmseq
time ./mmomp
time ./mmpthread

The is a constant defined for the size of the matrix called SIZE that needs to be 
changed before testing. In the pthread version, there's also a constant for the 
number of threads which can be changed.

There is also code for printing matrices that is commented out. 
Uncomment that to print matrices to check correctness.

how to run ehashs:

This is precompiled per the instructions but can be rebuilt with "gcc ehashs.c -o ehashs hashfun.o"

./ehashs <"four lower case letter hash">

prints the hash passed in and then if it meets the requirments, the cracked hash string.

output of what is going on can be turned on by uncommenting the printf line.

 
This is precompiled per the instructions but can be rebuilt with "gcc ehashp.c -o ehashp hashfun.o -fopenmp"

./ehashp <"four lower case letter hash">

prints the hash passed in and then if it meets the requirments, the cracked hash string.

output of what is going on can be turned on by uncommenting the printf line.

example for timing:

p948@cs2:~/MatMul$ time ./ehashp 6385695050
 hash input = 6385695050
found!!
The answer is: slow

real	0m6.589s
user	0m0.422s
sys	0m1.351s
p948@cs2:~/MatMul$ time ./ehashs 6385695050
 hash input = 6385695050
The answer is: slow

real	1m24.532s
user	0m0.555s
sys	0m1.714s


