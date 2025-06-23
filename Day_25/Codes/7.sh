#!/bin/bash

while true
do
    echo "==================== MENU ===================="
    echo "1. Display calendar of the current month"
    echo "2. Display today's date and time"
    echo "3. Display usernames currently logged in the system"
    echo "4. Display your name at the given x, y position"
    echo "5. Display your terminal number"
    echo "6. Exit"
    echo "=============================================="
    read -p "Enter your choice: " choice

    case $choice in
        1)
            echo "----- Calendar of Current Month -----"
            cal
            ;;
        2)
            echo "----- Today's Date and Time -----"
            date
            ;;
        3)
            echo "----- Usernames Currently Logged In -----"
            echo "Current User: $(whoami)"
            ;;
        4)
            read -p "Enter x position: " x
            read -p "Enter y position: " y

            if command -v tput > /dev/null 2>&1; then
                tput cup $x $y
                echo "Yeheni"  # You can replace with your actual name
            else
                echo "tput not available. Displaying name here:"
                echo "Yeheni"
            fi
            ;;
        5)
            echo "----- Terminal Number -----"
            tty
            ;;
        6)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter a valid option."
            ;;
    esac

    echo ""
done



answer
[yeheni@DESKTOP-CF9TBQU ~]$ vi 7.sh
[yeheni@DESKTOP-CF9TBQU ~]$ chmod 777 7.sh
[yeheni@DESKTOP-CF9TBQU ~]$ ./7.sh
==================== MENU ====================
1. Display calendar of the current month
2. Display today's date and time
3. Display usernames currently logged in the system
4. Display your name at the given x, y position
5. Display your terminal number
6. Exit
==============================================
Enter your choice: 1
----- Calendar of Current Month -----
      June 2025
Su Mo Tu We Th Fr Sa
 1  2  3  4  5  6  7
 8  9 10 11 12 13 14
15 16 17 18 19 20 21
22 23 24 25 26 27 28
29 30


==================== MENU ====================
1. Display calendar of the current month
2. Display today's date and time
3. Display usernames currently logged in the system
4. Display your name at the given x, y position
5. Display your terminal number
6. Exit
==============================================
Enter your choice: 2
----- Today's Date and Time -----
Mon Jun 23 23:34:35 +0530 2025

==================== MENU ====================
1. Display calendar of the current month
2. Display today's date and time
3. Display usernames currently logged in the system
4. Display your name at the given x, y position
5. Display your terminal number
6. Exit
==============================================
Enter your choice: 3
----- Usernames Currently Logged In -----
Current User: yeheni

==================== MENU ====================
1. Display calendar of the current month
2. Display today's date and time
3. Display usernames currently logged in the system
4. Display your name at the given x, y position
5. Display your terminal number
6. Exit
==============================================
Enter your choice: 4
Enter x position: 4
Enter y position: 5
tput not available. Displaying name here:
Yeheni

==================== MENU ====================
1. Display calendar of the current month
2. Display today's date and time
3. Display usernames currently logged in the system
4. Display your name at the given x, y position
5. Display your terminal number
6. Exit
==============================================
Enter your choice: 5
----- Terminal Number -----
/dev/pts/1

==================== MENU ====================
1. Display calendar of the current month
2. Display today's date and time
3. Display usernames currently logged in the system
4. Display your name at the given x, y position
5. Display your terminal number
6. Exit
==============================================
Enter your choice: 6
Exiting...
[yeheni@DESKTOP-CF9TBQU ~]$