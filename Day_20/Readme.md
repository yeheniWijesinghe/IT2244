## Shared Memory

Writer

```
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define SHM_SIZE 1024 //size of shared memory segment

int main(){
	key_t key = ftok("shmfile",1039); //generate unique key
	int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666); //create shared memory segment
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	
	char *shmaddr = (char*) shmat(shmid, NULL, 0); //attach to shared memory
	if(shmaddr == (char*) -1){
		perror("shmat");
		exit(1);
	}
	
	printf("Write Data: ");
	fgets(shmaddr, SHM_SIZE, stdin); //write data to shared memory
	
	printf("Data written in memory: %s\n",shmaddr);
	
	shmdt(shmaddr); //detach from shared memory
	
	return 0;
}
```

Reader
```
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define SHM_SIZE 1024 //size of shared memory segment

int main(){
	key_t key = ftok("shmfile", 1039); // generate unique key
	int shmid = shmget(key, SHM_SIZE, 0666); //access shared memory segment
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	
	char *shmaddr = (char*) shmat(shmid, NULL, 0); //attach to shared memory
	if(shmaddr == (char*) -1){
		perror("shmat");
		exit(1);
	}
	
	printf("Data read from memory: %s\n", shmaddr);
	
	shmdt(shmaddr); //detach from shared memory
	
	shmctl(shmid, IPC_RMID, NULL); //remove shared memory segment
	
	return 0;
}
```
Answer 
```
[2021ict39@fedora ~]$ touch shmfile
[2021ict39@fedora ~]$ chmod 644 shmfile
[2021ict39@fedora ~]$ vi writer.c
[2021ict39@fedora ~]$ gcc writer.c -o writer
[2021ict39@fedora ~]$ ./writer
Write Data: Hellooooooo
Data written in memory: Hellooooooo

[2021ict39@fedora ~]$ vi reader.c
[2021ict39@fedora ~]$ gcc reader.c -o reader
[2021ict39@fedora ~]$ ./reader
Data read from memory: Hellooooooo
```

Ex01
```
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/wait.h>

int main(){
	size_t size = 4096;
	char *shared_mem = mmap(NULL, size, PROT_READ |PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(shared_mem == MAP_FAILED){
		perror("mmap faild");
		exit(1);
	}
	
	pid_t pid = fork();
	if(pid == 0){
		//child process
		sprintf(shared_mem, "Hello from child!");
		printf("Child wrote: %s\n", shared_mem);
		exit(0);
	}
	else if(pid>0){
		//parent process
		wait(NULL);//wait for child to finish
		printf("Parent read: %s\n", shared_mem);
		munmap(shared_mem, size);
	}
	else{
		perror("fork failed");
		exit(1);
	}
	
	return 0;
}
```
Answer 

```
[2021ict39@fedora ~]$ vi Ex01.c
[2021ict39@fedora ~]$ gcc Ex01.c -o Ex01
[2021ict39@fedora ~]$ ./Ex01
Child wrote: Hello from child!
Parent read: Hello from child!

```

Ex02
```
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/wait.h>

int main(){
	size_t size = 4096;
	char *shared_mem = mmap(NULL, size, PROT_READ |PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(shared_mem == MAP_FAILED){
		perror("mmap faild");
		exit(1);
	}
	
	int n,r;
	scanf("Enter value for n: ", &n);
	scanf("Enter value for r: ", &r);
	
	pid_t pid = fork();
	if(pid == 0){
		//child process
		sleep(1);
		sprintf(shared_mem,"%d", n);
		sprintf(shared_mem,"%d", r);
		printf("Child receives: %d\n", shared_mem);
		exit(0);
	}
	else if(pid>0){
		//parent process
		wait(NULL);//wait for child to finish
		printf("Parent read: %d\n", shared_mem);
		munmap(shared_mem, size);
	}
	else{
		perror("fork failed");
		exit(1);
	}
	
	return 0;
}
```
Answer
```
[2021ict39@fedora ~]$ vi Ex02.c
[2021ict39@fedora ~]$ gcc Ex02.c -o Ex02
[2021ict39@fedora ~]$ ./Ex02
6
Child receives: -759250944
Parent read: -759250944
```
