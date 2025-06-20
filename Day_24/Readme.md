## Question 01
Write a C program that creates two threads. Each thread should print 
a message indicating it is running. The main thread should wait for both 
threads to finish before exiting.

```
#include <stdio.h>
#include <pthread.h>

void* threadFunc(void* arg) {
    int threadNum = *(int*)arg;
    printf("Thread %d is running.\n", threadNum);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int t1_id = 1, t2_id = 2;

    pthread_create(&t1, NULL, threadFunc, &t1_id);
    pthread_create(&t2, NULL, threadFunc, &t2_id);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads finished.\n");
    return 0;
}
```

answer
```
[yeheni@DESKTOP-CF9TBQU ~]$ vi q01.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc q01.c -o q01
[yeheni@DESKTOP-CF9TBQU ~]$ ./q01
Thread 2 is running.
Thread 1 is running.
Both threads finished.
```

## Question 02:
Write a program to create 5 threads. Each thread should print its thread
ID and then exit. The main thread should join all threads and print a 
completion message.
use pthread_self()-to get id.

```
#include <stdio.h>
#include <pthread.h>

void* printThreadID(void* arg) {
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu\n", tid);
    return NULL;
}

int main() {
    pthread_t threads[5];

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, printThreadID, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All 5 threads have finished.\n");
    return 0;
}
```

answer
```
[yeheni@DESKTOP-CF9TBQU ~]$ vi q02.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc q02.c -o q02
[yeheni@DESKTOP-CF9TBQU ~]$ ./q02
Thread ID: 123884642838208
Thread ID: 123884634445504
Thread ID: 123884626052800
Thread ID: 123884617660096
Thread ID: 123884609267392
All 5 threads have finished.
```

## Question 03
Write a program that creates a thread which prints numbers from 1 to 10 
with a 1-second delay between each number.The main thread should wait for 
this thread to finish.

```
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* printNumbers(void* arg) {
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", i);
        sleep(1);  // Sleep for 1 second
    }
    return NULL;
}

int main() {
    pthread_t t;

    pthread_create(&t, NULL, printNumbers, NULL);
    pthread_join(t, NULL);

    printf("Number printing thread finished.\n");
    return 0;
}
```

answer
```
[yeheni@DESKTOP-CF9TBQU ~]$ vi q03.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc q03.c -o q03
[yeheni@DESKTOP-CF9TBQU ~]$ ./q03
1
2
3
4
5
6
7
8
9
10
Number printing thread finished.
```

## Question 04
Create two threads where one thread increments a global counter 100 times
and the other thread decrements the same counter 100 times. 
Print the final value of the counter after both threads finish.

```
#include <stdio.h>
#include <pthread.h>

int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < 1000; i++) {
        counter++;
    }
    return NULL;
}

void* decrement(void* arg) {
    for (int i = 0; i < 1000; i++) {
        counter--;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, decrement, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", counter);
    return 0;
}
```

answer
```
[yeheni@DESKTOP-CF9TBQU ~]$ vi q04.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc q04.c -o q04
[yeheni@DESKTOP-CF9TBQU ~]$ ./q04
Final counter value: 0
```

## Question 05
Implement a thread function that takes an integer argument, squares it,
and returns the result to the main thread using pthread_exit and pthread_join.

```
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* square(void* arg) {
    int num = *(int*)arg;
    int* result = malloc(sizeof(int)); //Allocate memory on the heap to store an integer.result points to this allocated memory.
    *result = num * num;  //Store the result in the allocated memory.
	//function used by a thread to terminate itself and optionally return a value (retval) to any thread that joins it.
    pthread_exit(result); //Exit the thread and return the pointer result to the caller.
}

int main() {
    pthread_t t;
    int num = 5;

    pthread_create(&t, NULL, square, &num);

    int* res; //Declare a pointer res to receive the result
    pthread_join(t, (void**)&res);//pthread_join stores the thread's return value (a void*) in res.

    printf("Square of %d is %d\n", num, *res);
    free(res); //Free the memory allocated by the thread to avoid memory leaks.
    return 0;
}
```

answer
```
      |     ^~~~~~
[yeheni@DESKTOP-CF9TBQU ~]$ vi q05.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc q05.c -o q05
[yeheni@DESKTOP-CF9TBQU ~]$ ./q05
Square of 5 is 25
```
