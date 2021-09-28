#This is a makefile
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=99 -g -ggdb $(WARNING) $(ERROR)

all:
	$(CC) shell_array.c -o shell_array
	$(CC) shell_list.c -o shell_list

exec:
	./shell_list
clean:
	rm -rf shell_array shell_list
	rm -rf *.exe
	rm -rf *.o
