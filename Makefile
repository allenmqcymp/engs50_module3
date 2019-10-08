CFLAGS=-Wall -pedantic -std=c11 -I. -g
CC=gcc
LIBS=-lm

# get all c files whose name starts test. This is used to extract the target name
#https://stackoverflow.com/questions/13995906/get-filename-without-extension-within-makefile
TEST_CFILES:=$(wildcard test*.c)
TARGETS:=$(patsubst %.c,%,$(TEST_CFILES))

all: $(TARGETS)

$(TARGETS) : %: %.o list.o
	$(CC) $(CFLAGS) $< list.o -o $@ 


%.o: %.c list.h
	$(CC) $(CFLAGS) -c $< 


clean:
	rm -rf *.o
