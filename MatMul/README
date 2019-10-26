Group members: Emmy Woods, Chris Cornell, Brandon Roth

how to build and run:

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
