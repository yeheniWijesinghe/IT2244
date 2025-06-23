read -p "Enter a string: " str
rev_str=$(echo "$str" | rev)

if [ "$str" = "$rev_str" ]; then
    echo "The string is a palindrome."
else
    echo "The string is not a palindrome."
fi

answer 

The string is not a palindrome.
[yeheni@DESKTOP-CF9TBQU ~]$ vi 3.sh
[yeheni@DESKTOP-CF9TBQU ~]$ chmod 777 3.sh
[yeheni@DESKTOP-CF9TBQU ~]$ ./3.sh
Enter a string: madam
The string is a palindrome.
[yeheni@DESKTOP-CF9TBQU ~]$ ./3.sh
Enter a string: banana
The string is not a palindrome.