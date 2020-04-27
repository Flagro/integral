CC = gcc
CFLAGS = -Wall -m32
AN = nasm
AFLAGS = -f elf32
RM = rm -f

.PHONY: all clean

all: main

main: main.o get_integral.o test.o root.o integral.o f1.o f2.o f3.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

get_integral.o: get_integral.c integral.o root.o f1.o f2.o f3.o
	$(CC) $(CFLAGS) -c $<

test.o: test.c integral.o root.o
	$(CC) $(CFLAGS) -c $<

integral.o: integral.c
	$(CC) $(CFLAGS) -c $<

root.o: root.c
	$(CC) $(CFLAGS) -c $<

%.o: %.asm
	$(AN) $(AFLAGS) $<

clean:
	$(RM) *o main