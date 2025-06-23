capitalize() {
    for word in $@; do
        first_char=$(echo ${word:0:1} | tr '[:lower:]' '[:upper:]')
        rest_chars=${word:1}
        echo -n "$first_char$rest_chars "
    done
    echo
}

read -p "Enter text: " text
capitalize $text

answer
[yeheni@DESKTOP-CF9TBQU ~]$ vi 5.sh
[yeheni@DESKTOP-CF9TBQU ~]$ chmod 777 5.sh
[yeheni@DESKTOP-CF9TBQU ~]$ ./5.sh
Enter text: Hello, welcome
Hello, Welcome