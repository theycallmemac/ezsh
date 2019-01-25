CC = gcc
CFLAGS = -g -Wall -pedantic --std=gnu99
LDFLAGS = -Lcu/ -lcu

OBJS = suites/tokenize/test_prompt_tokenize.o suites/colorize/test_prompt_colorize.o runTests.o

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o test suites/*.o

.PHONY: all clean
