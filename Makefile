CC=gcc
CFLAGS= -O3 -march=native


all: parser

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

parser: parser.o driver.c
	$(CC) $(CFLAGS) -o $@ $^

clean: #make clean to run
	rm *.o *.h.gch parser