## Threads

Single threaded program.
```
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

//A normal C function that is executed as a thread when its name is specified in pthread_create()

void *helloworld(void*vargp){
	sleep(1);
	printf("Hello World\n");
	return NULL;
}

int main(){
	pthread_t thread_id;
	printf("Before Thread\n");
	pthread_create(&thread_id, NULL, helloworld, NULL);
	pthread_join(thread_id, NULL);
	printf("After Thread\n");
	exit(0);
}
```
Answer - 
```
[2021ict39@fedora ~]$ vi thread.c
[2021ict39@fedora ~]$ gcc thread.c -o thread
[2021ict39@fedora ~]$ ./thread
Before Thread
Hello World
After Thread
```

Multi threaded program.
```
#include<stdio.h>
#include<pthread.h>

//Function to be executed
void* print_message(void* arg){
	char* message = (char*)arg;
	printf("%s\n", message);
	return NULL;
}

int main(){
	pthread_t thread1, thread2;
	
	//create first thread
	pthread_create(&thread1, NULL, print_message, "Hello from thread 01");
	
	//second thread
	pthread_create(&thread2, NULL, print_message, "Hello from thread 02");
	
	//wait for threads to finish
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf("Both threads comlpeted\n");
	return 0;
}
```
Answer -
```
[2021ict39@fedora ~]$ vi multiThread.c
[2021ict39@fedora ~]$ gcc multiThread.c -o multiThread
[2021ict39@fedora ~]$ ./multiThread
Hello from thread 01
Hello from thread 02
Both threads comlpeted
```

Example 01 - Independent threads
```
#include<stdio.h>
#include<pthread.h>

//Function to be executed
void* print_message(void* arg){
	char* message = (char*)arg;
	printf("%s\n", message);
	return NULL;
}

int main(){
	pthread_t thread[3];
	char* message[] = {
		"Thread1 says hi!",
		"Thread2 says hello!",
		"Thread3 says hey!"
	};
	
	for(int i=0; i<3; i++){
		pthread_create(&thread[i], NULL, print_message, message[i]);
	}
	
	//wait for threads to finish
	for(int i=0; i<3; i++){
		pthread_join(thread[i], NULL);
	}
	
	printf("All threads comlpeted\n");
	return 0;
}
```
Answer -
```
[2021ict39@fedora ~]$ vi threadEx.c
[2021ict39@fedora ~]$ gcc threadEx.c -o threadEx
[2021ict39@fedora ~]$ ./threadEx
Thread1 says hi!
Thread1 says hello!
Thread3 says hey!
All threads comlpeted
```

Example 02 - Dependent threads
```
//Using threads to compute parts of sum(Parallel Sum)

#include <stdio.h>
#include <pthread.h>

#define SIZE 6

int arr[SIZE] = {1, 2,3 ,4, 5,6};
int sum1=0, sum2=0;

void* sum_part1(void* arg){
	for(int i=0; i<SIZE/2; i++){
		sum1 += arr[i];
	}
	return NULL;
}

void* sum_part2(void* arg){
	for(int i=SIZE/2; i<SIZE; i++){
		sum2 += arr[i];
	}
	return NULL;
}

int main(){
   pthread_t t1,t2;
  
   pthread_create(&t1,NULL,sum_part1,NULL);
   pthread_create(&t2,NULL,sum_part2,NULL);
   
 
   pthread_join(t1,NULL);
   pthread_join(t2,NULL);
 
   
   printf("Total sum = %d\n", sum1 + sum2);
   
   return 0;
}
```
Answer -
```
[2021ict39@fedora ~]$ vi thread_sum.c
[2021ict39@fedora ~]$ gcc thread_sum.c -o thread_sum
[2021ict39@fedora ~]$ ./thread_sum
Total sum = 21
```

