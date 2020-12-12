Compilation instructions
g++ project2.cpp -pthreads
a/a.out

Design Write-Up

      In the main, I have 5 threads that call a function, divide, and inside the function divide it 
makes 20 threads that calls another function, findMin which returns the minimum value of a 
given index of an array. 5 threads each call divide so I have 100 threads in total and each thread 
is in charge of finding the minimum of 100 indexes in the array. Each thread stores the found 
minimum into a global array of size 100. The first layer of 5 threads each finds a minimum of 20 
indexes in the global array and stores the minimums into another global array. Then the main 
thread finds the minimum of those 5 minimums and returns the ultimate minimum. Some of 
the problems I came up with was the a-synchronousness of the threads because the threads 
will fail to load the values from the 10000 random numbers into a 0 so my minimum would 
always be a 0. But I solved this by putting in the prinf statements to check the indexs of the 
counters.




