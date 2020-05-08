# Threads_OS_HW3
**Find the number of sentences with Threads**<br>
It s my Operating System Homework3 / Ankara University .

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




## Working Principle
 First of all, we wanna read a file whose name is input.txt .You can easily create a sample file with name input.<br>
     fp = fopen("input.txt", "r");<br> 
 Now, we can read this file and we can detect number sentences.<br>
 Secondly, We are creating threads in the main function. Number of threads are taken from user.<br>
 
 I have 2 part of stage in this homework:<br>
 First one threads1.c file detect sentences but dont return the numbers to main function.<br>
 Second one threads2.c file detect sentences and threads return the number of sentences.<br>
 
 ## References
 
 * https://www.youtube.com/playlist?list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM  MOST USEFUL VIDEO SERIES:)

 * http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html

 * https://randu.org/tutorials/threads/

 * https://courses.engr.illinois.edu/cs241/fa2010/ppt/10-pthread-examples.pdf

 * https://www.ibm.com/support/knowledgecenter/SSLTBW_2.4.0/com.ibm.zos.v2r4.bpxbd00/ptjoin.htm
 
 
 
 
 


