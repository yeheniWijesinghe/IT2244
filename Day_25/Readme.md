## EXERCISES
Child B: Reads two numbers from the user and writes them to shared memory.
Child C: Reads the numbers from shared memory, performs + - * / operations, and writes the results 
to shared memory.
Parent A: Reads and displays the results.
Everyone prints their PID and PPID.

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

// Shared structure
typedef struct {
    int a, b;
    int sum, diff, prod;
    float quot;
} SharedData;

int main() {
    size_t size = sizeof(SharedData);

    SharedData *shared_mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    pid_t pidB = fork();

    if (pidB == 0) { // Child B process
        printf("Child B Process: PID=%d, PPID=%d\n", getpid(), getppid());
        printf("Enter value for a: ");
        scanf("%d", &shared_mem->a);
        printf("Enter value for b: ");
        scanf("%d", &shared_mem->b);
        exit(0);
    } 
    else if (pidB > 0) {
        wait(NULL); // Wait for child B to finish

        pid_t pidC = fork();

        if (pidC == 0) { // Child C process
            printf("Child C Process: PID=%d, PPID=%d\n", getpid(), getppid());

            int a = shared_mem->a;
            int b = shared_mem->b;

            shared_mem->sum = a + b;
            shared_mem->diff = a - b;
            shared_mem->prod = a * b;

            if (b != 0) {
                shared_mem->quot = (float)a / b;
            } else {
                shared_mem->quot = 0; // Handle division by zero
            }

            exit(0);
        } 
        else if (pidC > 0) {
            wait(NULL); // Wait for child C to finish

            printf("Parent A Process: PID=%d, PPID=%d\n", getpid(), getppid());
            printf("Results received from shared memory:\n");
            printf("%d + %d = %d\n", shared_mem->a, shared_mem->b, shared_mem->sum);
            printf("%d - %d = %d\n", shared_mem->a, shared_mem->b, shared_mem->diff);
            printf("%d * %d = %d\n", shared_mem->a, shared_mem->b, shared_mem->prod);

            if (shared_mem->b != 0) {
                printf("%d / %d = %.2f\n", shared_mem->a, shared_mem->b, shared_mem->quot);
            } else {
                printf("Division by zero is not allowed.\n");
            }

            munmap(shared_mem, size);
        } 
        else {
            perror("Fork for Child C failed");
            exit(1);
        }
    } 
    else {
        perror("Fork for Child B failed");
        exit(1);
    }

    return 0;
}
```

Answer
```
[yeheni@DESKTOP-CF9TBQU ~]$ vi sharedmemory.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc sharedmemory.c -o sharedmemory
[yeheni@DESKTOP-CF9TBQU ~]$ ./sharedmemory
Child B Process: PID=47, PPID=46
Enter value for a: 6
Enter value for b: 3
Child C Process: PID=48, PPID=46
Parent A Process: PID=46, PPID=11
Results received from shared memory:
6 + 3 = 9
6 - 3 = 3
6 * 3 = 18
6 / 3 = 2.00
```

