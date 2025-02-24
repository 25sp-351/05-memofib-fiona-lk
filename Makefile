all: memfib
OBJS = memfib.o
CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm

memfib: $(OBJS)
	$(CC) -o memfib $(CFLAGS) $(OBJS) $(LDFLAGS)

memfib.o: memfib.c memfib.h
	$(CC) $(CFLAGS) -c memfib.c -o memfib.o

clean:
	rm -f memfib $(OBJS)