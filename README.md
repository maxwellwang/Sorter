fileSort.c, CS214's programmer's manual
NAME
fileSort.c - sorts a given file with either quick or insertion sort
Synopsis
First to compile the program, run the following on either a Meltdown or Command Center iLab machine.
gcc fileSort.c
Then to run the program:
./a.out <flag> <file_path>
DESCRIPTION
The fileSort program reads in tokens from the file at 'file_path', sorts it using the sort specified by 'flag', and
prints the resulting sorted output. Sort flag can either be '-i' to use insertion sort or '-q' to use quicksort. File
path should contain a text file with tokens separated by commas. Tokens can either be strings of lowercase
letters or integers, and not both. Whitespace is allowed but ignored.
FUNCTION
This program works by reading from file and inserting tokens into a linked list. A buffer holds the token data
and reallocates to double in size if more space is needed. Depending on whether the data is integers or
strings, the program will select the correct comparator. It will then pass that comparator to either the quick
sort or insertion sort function with a function pointer. In the sorts themselves, the values of the Linked lists are
swapped, not the nodes themselves. Then, if no errors occur, the sorted linked list is then printed to stdout.
RETURN VALUE
On success, it will print out the contents of the input file in sorted order with each item on a new line. On error,
the program will print the error message.
ERRORS
fileSort will throw a fatal error if the wrong number of arguments are given or if the arguments given are
incorrect. If the file is empty, it will print a warning. System errors such as malloc failing will make it print the
error but keep going.
