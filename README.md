# Threads_OS_HW3
Find the number of sentences with Threads 
It s my Operating System homework.

## Requirements

    pThread library
    Ubuntu OS
    gcc




## Description of Homework

You have a file named input.txt. Read this file line by line by creating X threads. Each thread find the number of sentences
in its own section. For this purpose, your main function includes the following operations in order:
1. Take the value (x) from the user - X = Number of threads .
2. Calculate the number of lines of the file and decide how many lines each thread should read. The value should be
rounded up when this value is not an integer
3. When creating the threads, it must be indicated the begining line of thread
4. The number of scanned lines and number of sentences returned from the thread must be printed.
Each of your threads should do the following:
1. Started from the number of lines assigned by the Main function.
2. The last thread can scan fewer lines than the others (because you round up). Therefore, it should return how many lines
th thread scans to the main function. In addition, it will send the number of sentences.
Write a C / C ++ program that does all this. You can examine the pthread_create and pthread_join commands in pthread
library. To run your program (for C code):

## Build & Run
    gcc name.c –lpthread
    ./a.out


