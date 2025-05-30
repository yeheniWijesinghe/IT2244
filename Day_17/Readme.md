```
//ex3
#include<stdio.h>
#include<unistd.h>//sleep,fork
#include<stdlib.h>//exit


int main(){
	printf("Program started. \n");
	
	printf("Sleeping for 3 seconds... \n");
	sleep(3); //pause for 3 sec
	
	printf("Exiting the program. \n");
	exit(0); //clean exit
	
	return 0;
}
```
ans:-
```
Program started.
Sleeping for 3 seconds...
Exiting the program.
```
```
//ex4
#include<stdio.h>
#include<unistd.h>//sleep,fork
#include<stdlib.h>//exit
#include<sys/wait.h>//for wait


int main(){
	pid_t pid;//a data type for initialize a pid
	
	printf("Parent process started. PID: %d\n",getpid());
	
	pid = fork();//create new child
	
	if(pid<0){
		perror("fork faild");
		exit(1);
	}
	if(pid==0){
		//child
		printf("Child process. PID: %d, Sleeping for 2 sec...\n",getpid());
		sleep(2);
		printf("Child process exiting.\n");
		exit(0);//child exits with status 0
	}
	else{
		//parent process
		int status;
		printf("Parent waiting for child to finish...\n");
		wait(&status);//wait for child to finish
		if(WIFEXITED(status)){ //return true if the child terminate normally
			printf("Child exited with status: %d\n",WEXITSTATUS(status));// gets the actual exit code (0 here)
		}
		else{
			printf("Child did not exit normaly.\n");
		}
		printf("Parent process ending.\n");
	}
	
	return 0;
}
```
ans:-
```
Parent process started. PID: 9518
Parent waiting for child to finish...
Child process. PID: 9519, Sleeping for 2 sec...
Child process exiting.
Child exited with status: 0
Parent process ending.
```
```
//ex4
Exercise:
first child: sleep for 1 sec
second child: sleep for 3 sec
parent: both children have finished

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(){
	pid_t pid;
	printf("Parent process started. PID: %d\n",getpid());
	pid = fork();
	
	if(pid<0){
		printf("Fork faild.\n");
		return 0;
	}
	if(pid==0){
		printf("Child process has started. Sleeping for 1 sec\nMy PID: %d\nMy PPID: %d\n",getpid(),getppid());
		sleep(1);
		printf("Child process 01 exiting...\n");
		return 0;
	}
	else{
		pid_t pid2;
		pid2 = fork();
		if(pid2<0){
			printf("Fork faild.\n");
			return 0;
		}
		if(pid2==0){
			printf("Child process has started. Sleeping for 3 sec\nMy PID: %d\nMy PPID: %d\n",getpid(),getppid());
			sleep(3);
			printf("Child process 02 exiting...\n");
			return 0;
		}
		else{
		//parent process
		wait(NULL);
		wait(NULL);
		printf("Parent process ending.\n");
		}
	}
	
	
	return 0;
}
```
ans:-
```
Parent process started. PID: 15513
Parent waiting for child to finish...
Child process has started. Sleeping for 1 sec
My PID: 15514
My PPID: 15513
Child process has started. Sleeping for 3 sec
My PID: 15515
My PPID: 15513
Child process 01 exiting...
Child process 02 exiting...
Parent process ending.
```


