CFLAGS=-Wall -pedantic -std=c11 -I. -g
CC=gcc
LIBS=-lm

# get all c files whose name starts test. This is used to extract the target name
#https://stackoverflow.com/questions/13995906/get-filename-without-extension-within-makefile
TEST_LIST_CFILES:=$(wildcard test_list*.c)
LIST_TARGETS:=$(patsubst %.c,%,$(TEST_LIST_CFILES))
LIST_OBJS:=$(patsubst %.c,%.o,$(TEST_LIST_CFILES))

TEST_HASH_CFILES:=$(wildcard test_hash*.c)
HASH_TARGETS:=$(patsubst %.c,%,$(TEST_HASH_CFILES))
HASH_OBJS:=$(patsubst %.c,%.o,$(TEST_HASH_CFILES))

TEST_QUEUE_CFILES:=$(wildcard test_queue*.c)
QUEUE_TARGETS:=$(patsubst %.c,%,$(TEST_QUEUE_CFILES))
QUEUE_OBJS:=$(patsubst %.c,%.o,$(TEST_QUEUE_CFILES))

all: $(LIST_TARGETS) $(HASH_TARGETS) $(QUEUE_TARGETS)

$(LIST_TARGETS) : %: %.o list.o
	$(CC) $(CFLAGS) $< list.o -o $@ 

$(HASH_TARGETS) : %: %.o hash.o queue.o
	$(CC) $(CFLAGS) $< hash.o queue.o -o $@ 

$(QUEUE_TARGETS) : %: %.o queue.o
	$(CC) $(CFLAGS) $< queue.o -o $@ 

$(QUEUE_OBJS) : %.o: %.c queue.h
	$(CC) $(CFLAGS) -c $< 

$(LIST_OBJS) : %.o: %.c list.h
	$(CC) $(CFLAGS) -c $< 

$(HASH_OBJS) : %.o: %.c hash.h queue.h
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -rf *.o
