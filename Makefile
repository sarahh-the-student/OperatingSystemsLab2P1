
all: prog1 prog2 my3proc
CFLAGS = -Wall -g

prog1: main.c
	gcc $(CFLAGS) main.c -o prog1

prog2: main2.c
	gcc $(CFLAGS) main2.c -o prog2

my3proc: main3.c
	gcc $(CFLAGS) main3.c -o my3proc

clean:
	rm -f prog1 prog2 my3proc