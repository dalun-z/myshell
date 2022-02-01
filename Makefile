
myshell: myshell.o argparse.o builtin.o
		gcc -o myshell myshell.o argparse.o builtin.o

myshell.o: myshell.c argparse.h builtin.h
			gcc -c myshell.c

argparse.o: argparse.c argparse.h
			gcc -c argparse.c

builtin.o: builtin.c builtin.h
			gcc -c builtin.c


clean: 
		rm -f *.o *~* *.exe