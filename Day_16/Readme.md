Exercise 01

```

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int A,B,C;
int main() {
    pid_t pidA = getpid(); 

    printf("\nI'm A\n");
    printf("My pid: %d\n", pidA);
	printf("Enter A: ");
			scanf("%d", &A);
			printf("Enter B: ");
			scanf("%d", &B);
			printf("Enter C: ");
			scanf("%d", &C);

    pid_t f = fork();
    if (f == 0) {

        sleep(1); 
        printf("\nI'm B\n");
        printf("My ppid: %d\n", getppid());
        printf("My pid: %d\n", getpid());
		
		//factorial of A
		int fac = 1;
	
		for(int i=1; i<=A; i++){
			fac*=i;
		}
		printf("Factorial of %d is: %d\n",A,fac);
        return 0;
    }

    pid_t k = fork();
    if (k == 0) {
        
        sleep(2); 
        printf("\nI'm C\n");
        printf("My ppid: %d\n", getppid());
        printf("My pid: %d\n", getpid());
		
		//fibbonacci of C
			int x=0;
			int y=1;
	
			for(int i=1; i<=C; i++){
				printf("%d ",x);
				int z = x+y;
				x = y;
				y = z;
			}
			printf("\n");
			
			//check C is prime
			
			int isPrime;
			
			if (C <= 1) {
				isPrime = 0;  
			} else {
				for (int i = 2; i * i <= C; i++) {
					if (C % i == 0) {
						isPrime = 0;
						break;
					}
				}
			}

			if (isPrime)
				printf("%d is a prime number.\n", C);
			else
				printf("%d is not a prime number.\n", C);
			
			
        return 0;
    }

    
    wait(NULL);
    wait(NULL);

    return 0;
}
```

Answer:-

```
[2021ict39@fedora ~]$ ./ex2

I'm A
My pid: 18134
Enter A: 5
Enter B: 7
Enter C: 3

I'm B
My ppid: 18134
My pid: 18166
Factorial of 5 is: 120

I'm C
My ppid: 18134
My pid: 18167
0 1 1
3 is a prime number.
[2021ict39@fedora ~]$ gcc ex2.c -o ex2
[2021ict39@fedora ~]$ ./ex2

I'm A
My pid: 18191
Enter A: 8
Enter B: 5
Enter C: 6

I'm B
My ppid: 18191
My pid: 18201
Factorial of 8 is: 40320

I'm C
My ppid: 18191
My pid: 18202
0 1 1 2 3 5
6 is not a prime number.
```
