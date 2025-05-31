//01 - using pid
sender.c, receiver.c
answer - 
[2021ict39@fedora ~]$ gcc send.c -o send
[2021ict39@fedora ~]$ ./send
Write Data to Send: Yeheni
Data sent is: Yeheni

Use PID: 6382 in receiver to get your message.
[2021ict39@fedora ~]$ gcc recieve.c -o recieve
[2021ict39@fedora ~]$ ./recieve
Enter your sender's PID to receive your own message: 6382
Data received is: Yeheni

//01 - demo answer

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

//02 -


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
[2021ict39@fedora ~]$ gcc send39.c -o send39
[2021ict39@fedora ~]$ ./send39
Write Data : Yehe
Data send is : Yehe

[2021ict39@fedora ~]$ gcc recive39.c -o recive39
[2021ict39@fedora ~]$ ./recive39
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

/*answer

struct mesg_name { //tempory storage box
	long mesg_type;
	char mesg_text[100];
} message1; //tempory variable

struct mesg_regno { //tempory storage box
	int mesg_type;
	int mesg_rg;
} message2; //tempory variable

struct mesg_age { //tempory storage box
	long mesg_type;
	int mesg_a;
} message3; //tempory variable

#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 10
int main(){
	pid_t pidA = getpid(); 

    printf("\nI'm Parent\n");
    printf("My pid: %d\n", pidA);
	char name[50];
	int regno, age;
	printf("Enter Name: ");
			scanf("%s", &name);
			printf("Enter Regno: ");
			scanf("%d", &regno);
			printf("Enter Age: ");
			scanf("%d", &age);
			
	int msgid;
	//fork to generate unique key
	key_t key;
	key = ftok("progfile39", 39);
	//msgget reates a message queue and returns identifier
	
	msgid = msgget(key, 0666 | IPC_CREAT);
	message1.mesg_type = 1;
	printf("Enter Name : ");
	fgets(message1.mesg_text, MAX, stdin);
	
	message2.mesg_type = 1;
	printf("Enter Regno : ");
	fgets(message2.mesg_rg, MAX, stdin);
	
	message3.mesg_type = 1;
	printf("Enter Age : ");
	fgets(message3.mesg_a, MAX, stdin);
	
	//mgsnd to send messege
	msgsnd(msgid, &message1, sizeof(message1), 0);
	msgsnd(msgid, &message2, sizeof(message2), 0);
	msgsnd(msgid, &message3, sizeof(message3), 0);
	
	//display the message
	printf("Message sent successfully!\n");		
			
	int f = fork();
	if(f==0){
		pid_t pidB = getpid();
		printf("I'm the Child!\n");
		printf("My pid: %d\n", pidB);
		printf("My ppid: %d\n", getppid());
		
		key_t key;
		int msgid;
	
		//ftok to generate unique key
		key = ftok("progfile39", 39); //pathname which have permision for write and read
		//msgget creates a message queue and returns identifier
		msgid = msgget(key, 0666 | IPC_CREAT);
		//msgrcv to recive message
		msgrcv(msgid, &message1, sizeof(message1), 1, 0);
		msgrcv(msgid, &message2, sizeof(message2), 1, 0);
		msgrcv(msgid, &message3, sizeof(message3), 1, 0);
		//display the message
		printf("Recived Name : %s\n", message1.mesg_text);
		printf("Recived Regno : %d\n", message2.mesg_rg);
		printf("Recived Age : %d\n", message3.mesg_a);
		//to destroy the message queue
		msgctl(msgid, IPC_RMID, NULL);
	}
	
	return 0;
}
*/

//answer - demo
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