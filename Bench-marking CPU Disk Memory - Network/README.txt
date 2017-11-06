#########################################################################################################################################################

CS553 Programming Assignment #1 : Benchmarking	

#########################################################################################################################################################

Benchmarking of following parts of a computer system:

1) CPU
2) MEMORY
3) DISK
4) NETWORK

#########################################################################################################################################################

1) CPU

#########################################################################################################################################################

Objetive : CPU benchmark result is to find maximum GIOPS and GFLOPS performed by processor for different number of threads.

ProgrammingLanguage Used : C

FileName : cpu.c

No of Iterations : 100000000
No of Int Operations : 16
No of Float Operations : 16

***********************************************************************
Function
**********************************************************************

1) th_int():

purpose: This function takes integer values and do integer operations(addition,multiplication and subtraction)

2) th_int_avx():

purpose: This function takes integer values and do integer operations with AVX(addition,multiplication)

3) th_float():

purpose: This function takes float values and do floating point operations(addition,multiplication and subtraction)

4) th_float_avx():

purpose: This function takes float values and do floating point operations with AVX(addition,multiplication)

5) ops():

parameters: Number of threads, Type of operations, Time taken
purpose: This function calculates IOPS, GIOPS, FLOPS and GFLOPS for CPU.

**********************************************************************************
Execution
********************************************************************************

For executing CPU Benchmark follow this instructions:

1) Copy cpu.c and makefile source code in your Cloud folder using scp command.
2) Run makefile using command "make"
3) Run Linpack to compare results


**********************************************************************************
Result
********************************************************************************

1) Time taken to perform IOPS and FLOPS using different number of threads at a time
2) Benchmarking results for comparisons



#########################################################################################################################################################

2) MEMORY

#########################################################################################################################################################

Objetive : Stream benchmarking.

ProgrammingLanguage Used : C

FileName : cpu.c

No of Iterations taken: (1024*1024*1024)*block size/Thread count
No of operations taken: 3*4*4 + 1= 49

***********************************************************************
Function
**********************************************************************

1) Seqaccess(): 

Pur[ose: This function runs the sequential write access using memset and write onto memory. It calculates the total time taken when run for multiple threads and multiple block size.

2) random-access(): 

Purpose: This function runs the random write access using memset and write onto memory. It calculates the total time taken when run for multiple threads and multiple block size.

3) Readwriteops(): 

Purpose: This function runs the read and write using memcpy and moving the pointer of both the file. It calculates the total time taken when run for multiple threads and multiple block size.
Parameters in make file: Operations, Thread count , block size

Returns: 2 files with latency and throughput respectively.

Purpose:
Varying the number of thread and block size each operation (Sequential read access, random read access and read write operations), calculates time taken by each operation to complete and calculate latency and throughput.

Methods for executing the code:
To run the memory run the following operations.
Place the memory code and makefile into linux folder
Inside the memory folder run the following command.
Make experiment5
Make experiment6
Make experiment7
Make experiment8 

Output values:
Memoutlat.txt (Prints all the operations latency with thread number in 8B case)
Memoutthvsthread.txt (Prints all the operations latency with thread number in 8KB,8MB,80MB case)



#########################################################################################################################################################

2) DISK

#########################################################################################################################################################

No of Iterations taken: (1024*1024*1024)*block size/Thread count

No of operations taken: 3*4*4 + 1= 49

Benchmark: Iozone benchmarking.

Function in C: 

1)seqreadaccess: This function runs the sequential write access using memset and write onto memory. It calculates the total time taken when run for multiple threads and multiple block size.

2) randomreadaccess: This function runs the random write access using memset and write onto memory. It calculates the total time taken when run for multiple threads and multiple block size

3)readwriteops: This function runs the read and write using memcpy and moving the pointer of both the file. It calculates the total time taken when run for multiple threads and multiple block size.


Parameters in make file: Operations, Thread count, block size

Returns: 2 files with latency and throughput respectively.

Purpose:
Varying the number of thread and block size each operation (Sequential read access, random read access and read write operations), calculates time taken by each operation to complete and calculate latency and throughput.

Methods for executing the code:
To run the memory run the following operations.
Place the memory code and makefile into linux folder
Inside the memory folder run the following command.
gcc filecreate.c
./a.out
Make experiment1
Make experiment2
Make experiment3
Make experiment4
 

Output values: 


Diskoutlat.txt (Prints all the operations latency with thread number in 8B case)
diskoutthvsthread.txt (Prints all the operations latency with thread number in 8KB,8MB,80MB case)



#########################################################################################################################################################

4) NETWORK

#########################################################################################################################################################

Objetive : Network benchmark result is to find network speed over the loopback interface card.

ProgrammingLanguage Used : C

FileName : tcp_s.c, tcp_c.c, udp_s.c, udp_c.c

Packet_size = 64kb

Latancy unit: milliseconds
Throughput: Mb/sec

***********************************************************************
File
**********************************************************************

1) tcp_s.c :

purpose: This file implements multithreaded tcp server to connect with multiple udp clients for further communications.

2) tcp_c.c :

purpose: This file implements multithreaded tcp client to connect with tcp server and transfer data between two processes.

3) udp_s.c :

purpose: This file implements multithreaded udp server to connect with multiple udp clients for further communications.

4) udp_c.c :

purpose: This file implements multithreaded udp client to connect with tcp server and transfer data between two processes.

**********************************************************************************
Execution
********************************************************************************

For executing Network Benchmark follow this instructions:

1) Copy tcp_s.c, tcp_c.c, udp_s.c, udp_c.c and makefile source code in your Cloud folder using scp command.
2) Run makefile using command "make" in one terminal
2) Run makefile using command "make" in another terminal
3) Run iperf to compare results


**********************************************************************************
Result
********************************************************************************


1) Time taken to send data packets from client to server.
2) Network speed of our system between two processes or nodes.
2) Benchmarking results for comparisons.
