//01 - Recieve the sent message in a shared connection. 
//sender
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 10 //Max size for message queue

//structure for message queue
struct mesg_buffer { //tempory storage box
	long mesg_type;
	char mesg_text[100];
} message; //tempory variable

int main(){
	int msgid;
	//fork to generate unique key
	key_t key;
	key = ftok("progfile39", 39);
	//msgget reates a message queue and returns identifier
	
	msgid = msgget(key, 0666 | IPC_CREAT);
	message.mesg_type = 1;
	printf("Write Data : ");
	fgets(message.mesg_text, MAX, stdin);
	//mgsnd to send messege
	msgsnd(msgid, &message, sizeof(message), 0);
	//display the message
	printf("Data send is : %s\n", message.mesg_text);
	return 0;
}

//receive
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
//structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message; //tempory variable

int main(){
	key_t key;
	int msgid;
	
	//ftok to generate unique key
	key = ftok("progfile39", 39); //pathname which have permision for write and read
	//msgget creates a message queue and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	//msgrcv to recive message
	msgrcv(msgid, &message, sizeof(message), 1, 0);
	//display the message
	printf("Data recived is : %s\n", message.mesg_text);
	//to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}

answer -
[yeheni@DESKTOP-CF9TBQU ~]$ touch progfile39
[yeheni@DESKTOP-CF9TBQU ~]$ chmod 644 progfile39
[yeheni@DESKTOP-CF9TBQU ~]$ vi send39.c
[yeheni@DESKTOP-CF9TBQU ~]$ vi receive39.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc send39.c -o send39
[yeheni@DESKTOP-CF9TBQU ~]$ gcc receive39.c -o receive39
[yeheni@DESKTOP-CF9TBQU ~]$ ./send39
Write Data : Yeheni
Data send is : Yeheni

[yeheni@DESKTOP-CF9TBQU ~]$ ./receive39
Data recived is : Yeheni

//02 - Use file name 'send39' insted of 'progfile'.
	
//sender
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 10 //Max size for message queue

//structure for message queue
struct mesg_buffer { //tempory storage box
	long mesg_type;
	char mesg_text[100];
} message; //tempory variable

int main(){
	int msgid;
	//fork to generate unique key
	key_t key;
	key = ftok("send39", 39);
	//msgget reates a message queue and returns identifier
	
	msgid = msgget(key, 0666 | IPC_CREAT);
	message.mesg_type = 1;
	printf("Write Data : ");
	fgets(message.mesg_text, MAX, stdin);
	//mgsnd to send messege
	msgsnd(msgid, &message, sizeof(message), 0);
	//display the message
	printf("Data send is : %s\n", message.mesg_text);
	return 0;
}

//receive
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
//structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message; //tempory variable

int main(){
	key_t key;
	int msgid;
	
	//ftok to generate unique key
	key = ftok("send39", 39); //pathname which have permision for write and read
	//msgget creates a message queue and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	//msgrcv to recive message
	msgrcv(msgid, &message, sizeof(message), 1, 0);
	//display the message
	printf("Data recived is : %s\n", message.mesg_text);
	//to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}

answer - 
[yeheni@DESKTOP-CF9TBQU ~]$ gcc send39.c -o send39
[yeheni@DESKTOP-CF9TBQU ~]$ ./send39
Write Data : Yehe
Data send is : Yehe

[yeheni@DESKTOP-CF9TBQU ~]$ gcc recive39.c -o recive39
[yeheni@DESKTOP-CF9TBQU ~]$ ./recive39
Data recived is : Yehe


//03
Exercise
IPC using message queue

read inputs from parent process
Enter name: Yeheni
Enter regno: 39
Enter age: 23

Message sent succesfully.

give the output from the child process
Received name: Yeheni
Received regno: 39
Received age: 23

//answer 
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MSGKEY 1111
#define MAX_NAME_LEN 100
#define MAX_REGNO_LEN 100

struct person {
    long mtype; // Message type
    int age;
    char name[MAX_NAME_LEN];
    char regno[MAX_REGNO_LEN];
};

int main() {
    int msqid;
    struct person p1, p2;
    int f = fork();

    if (f == 0) {
        // Child process: Receiver
        msqid = msgget(MSGKEY, IPC_CREAT | 0666); 
        if (msqid == -1) {
            perror("msgget failed");
            exit(EXIT_FAILURE);
        }

        int msg_size = sizeof(struct person) - sizeof(long);

        if (msgrcv(msqid, &p2, msg_size, 0, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        } else {
            printf("Received Name: %s\n", p2.name);
            printf("Received RegNo: %s\n", p2.regno);
            printf("Received Age: %d\n", p2.age);
        }

        if (msgctl(msqid, IPC_RMID, NULL) == -1) {
            perror("msgctl failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process: Sender
        msqid = msgget(MSGKEY, IPC_CREAT | 0666);
        if (msqid == -1) {
            perror("msgget failed");
            exit(EXIT_FAILURE);
        }

        p1.mtype = 1;

        printf("Enter Name: ");
        scanf("%s", p1.name);

        printf("Enter RegNo: ");
        scanf("%s", p1.regno);

        printf("Enter Age: ");
        scanf("%d", &p1.age);

        int msg_size = sizeof(struct person) - sizeof(long);

        if (msgsnd(msqid, &p1, msg_size, IPC_NOWAIT) == -1) {
            perror("msgsnd failed");
        } else {
            printf("Message sent successfully.\n");
        }

        exit(0);
    }

    return 0;
}

answer -
[yeheni@DESKTOP-CF9TBQU ~]$ vi ex01.c
[yeheni@DESKTOP-CF9TBQU ~]$ gcc ex01.c -o ex01
[yeheni@DESKTOP-CF9TBQU ~]$ ./ex01
Enter Name: Yeheni
Enter RegNo: 2021ict39
Enter Age: 23
Message sent successfully.
Received Name: Yeheni
Received RegNo: 2021ict39
Received Age: 23
