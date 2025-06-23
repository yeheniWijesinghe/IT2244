## Pipe

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MSGSIZE 16

char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";

int main() {
    char inbuf[MSGSIZE + 1]; // +1 for null terminator
    int p[2];
    pid_t pid;

    if (pipe(p) < 0) {
        perror("pipe error");
        exit(1);
    }

    if ((pid = fork()) > 0) {
        // Parent process - writer
        close(p[0]); // Close unused read end

        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);

        close(p[1]); // Close write end after writing to send EOF
        wait(NULL);  // Wait for child
    } else if (pid == 0) {
        // Child process - reader
        close(p[1]); // Close unused write end

        int nbytes;
        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0) {
            inbuf[nbytes] = '\0'; // Null-terminate the string
            printf("%s\n", inbuf);
        }

        close(p[0]); // Close read end

        printf("Finished reading\n");
    } else {
        perror("fork error");
        exit(1);
    }

    return 0;
}
```
Answer
```
[yeheni@DESKTOP-CF9TBQU ~]$ vi pipe1.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc pipe1.c -o pipe1
[yeheni@DESKTOP-CF9TBQU ~]$ ./pipe1
hello, world #1
hello, world #2
hello, world #3
Finished reading
```

Exercise2
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int p2c[2]; // Pipe: parent to child
    int c2p[2]; // Pipe: child to parent

    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        // ================= PARENT ===================
        close(p2c[0]); // Close read end of parent-to-child
        close(c2p[1]); // Close write end of child-to-parent

        char shape;
        double input1, input2;

        printf("Area calculation program\n\n");
        printf("Circle => C\nTriangle => T\nSquare => S\nRectangle => R\n\n");
        printf("Enter your choice: ");
        scanf(" %c", &shape);

        write(p2c[1], &shape, sizeof(char)); // Send shape

        switch (shape) {
            case 'C':
                printf("Circle Area Calculation\n");
                printf("Enter the radius: ");
                scanf("%lf", &input1);
                write(p2c[1], &input1, sizeof(double));
                break;
            case 'T':
                printf("Triangle Area Calculation\n");
                printf("Enter the base: ");
                scanf("%lf", &input1);
                printf("Enter the height: ");
                scanf("%lf", &input2);
                write(p2c[1], &input1, sizeof(double));
                write(p2c[1], &input2, sizeof(double));
                break;
            case 'S':
                printf("Square Area Calculation\n");
                printf("Enter the side length: ");
                scanf("%lf", &input1);
                write(p2c[1], &input1, sizeof(double));
                break;
            case 'R':
                printf("Rectangle Area Calculation\n");
                printf("Enter the width: ");
                scanf("%lf", &input1);
                printf("Enter the height: ");
                scanf("%lf", &input2);
                write(p2c[1], &input1, sizeof(double));
                write(p2c[1], &input2, sizeof(double));
                break;
            default:
                printf("Invalid choice.\n");
                close(p2c[1]);
                close(c2p[0]);
                wait(NULL);
                exit(1);
        }

        close(p2c[1]); // Done sending inputs

        double area;
        read(c2p[0], &area, sizeof(double));
        printf("Area is: %.2lf\n", area);

        close(c2p[0]);
        wait(NULL); // Wait for child
    } else {
        // ================= CHILD ===================
        close(p2c[1]); // Close write end of parent-to-child
        close(c2p[0]); // Close read end of child-to-parent

        char shape;
        double a, b, area = 0;

        read(p2c[0], &shape, sizeof(char));

        switch (shape) {
            case 'C':
                read(p2c[0], &a, sizeof(double));
                area = 3.14159 * a * a;
                break;
            case 'T':
                read(p2c[0], &a, sizeof(double));
                read(p2c[0], &b, sizeof(double));
                area = 0.5 * a * b;
                break;
            case 'S':
                read(p2c[0], &a, sizeof(double));
                area = a * a;
                break;
            case 'R':
                read(p2c[0], &a, sizeof(double));
                read(p2c[0], &b, sizeof(double));
                area = a * b;
                break;
            default:
                area = -1;
        }

        write(c2p[1], &area, sizeof(double));

        close(p2c[0]);
        close(c2p[1]);
        _exit(0);
    }

    return 0;
}
```
Answer
```
[yeheni@DESKTOP-CF9TBQU ~]$ vi pipe2.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc pipe2.c -o pipe2
[yeheni@DESKTOP-CF9TBQU ~]$ ./pipe2
Area calculation program

Circle => C
Triangle => T
Square => S
Rectangle => R

Enter your choice: R
Rectangle Area Calculation
Enter the width: 45
Enter the height: 56
Area is: 2520.00
[yeheni@DESKTOP-CF9TBQU ~]$ ./pipe2
Area calculation program

Circle => C
Triangle => T
Square => S
Rectangle => R

Enter your choice: S
Square Area Calculation
Enter the side length: 45
Area is: 2025.00
[yeheni@DESKTOP-CF9TBQU ~]$ ./pipe2
Area calculation program

Circle => C
Triangle => T
Square => S
Rectangle => R

Enter your choice: T
Triangle Area Calculation
Enter the base: 34
Enter the height: 56
Area is: 952.00
[yeheni@DESKTOP-CF9TBQU ~]$ ./pipe2
Area calculation program

Circle => C
Triangle => T
Square => S
Rectangle => R

Enter your choice: C
Circle Area Calculation
Enter the radius: 45
Area is: 6361.72
```



