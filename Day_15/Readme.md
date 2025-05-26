```
//01
#include<stdio.h>
#include<unistd.h>
int main(){
	fork();
	printf("Hello World!\n");
}
```
```
[2021ict39@fedora ~]$ ./fork
Hello World!
Hello World!
```
```
//02
#include<stdio.h>
#include<unistd.h>
int main(){
	fork();
	fork();
	printf("Hello World!\n");
}
```
```
[2021ict39@fedora ~]$ ./fork
Hello World!
Hello World!
Hello World!
Hello World!
```
```
//03
#include<stdio.h>
#include<unistd.h>
int main(){
	int f = fork();
	if(f==0){
		printf("I'm the child!\n");
	}
	else{
		printf("I'm the parent!\n");
	}
	return 0;
}
```
```
[2021ict39@fedora ~]$ ./fork
I'm the parent!
I'm the child!
```
```
//04
#include<stdio.h>
#include<unistd.h>
int main(){
	int f = fork();
	if(f==0){
		printf("I'm the child!\n");
		int csum;
		for(int i=1; i<=5; i++){
			printf("%d ", i);
			csum+=i;
		}
		printf("\nSummation of child process: %d\n",csum);
	}
	else{
		printf("I'm the parent!\n");
		int psum;
		for(int i=6; i<=10; i++){
			printf("%d ", i);
			psum+=i;
		}
		printf("\nSummation of parent process: %d\n",psum);
	}
	return 0;
}
```
```
[2021ict39@fedora ~]$ ./ex1
I'm the parent!
6 7 8 9 10
Summation of parent process: 40
I'm the child!
1 2 3 4 5
Summation of child process: 15
```
```
//05
#include<stdio.h>
#include<unistd.h>
int main(){
	int n;
	int f = fork();
	if(f==0){
		n = 1;
	}
	else{
		n = 6;
	}
	
	int sum=0;
	for(int i=n; i<n+5; i++){
		printf("%d ", i);
		sum+=i;
	}
	printf("\nSummation : %d\n",sum);
		
	return 0;
}
```
```
[2021ict39@fedora ~]$ ./ex1
6 7 8 9 10
Summation : 40
1 2 3 4 5
Summation : 15
```
