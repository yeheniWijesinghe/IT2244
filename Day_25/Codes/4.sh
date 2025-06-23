read -p "Enter a date (dd-mm-yyyy): " date

if [[ $date =~ ^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-[0-9]{4}$ ]]; then
    echo "Valid date format."
else
    echo "Invalid date format."
fi

answer
[yeheni@DESKTOP-CF9TBQU ~]$ vi 4.sh
[yeheni@DESKTOP-CF9TBQU ~]$ chmod 777 4.sh
[yeheni@DESKTOP-CF9TBQU ~]$ ./4.sh
Enter a date (dd-mm-yyyy): 20-10-2001
Valid date format.
[yeheni@DESKTOP-CF9TBQU ~]$ ./4.sh
Enter a date (dd-mm-yyyy): 1920-10-20
Invalid date format.