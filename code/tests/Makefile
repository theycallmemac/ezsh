CC = gcc
CFLAGS = -g -Wall -pedantic --std=gnu99
LDFLAGS = -Lcu/ -lcu

PROMPT_OBJS = suites/prompt/tokenize/test_prompt_tokenize.o suites/prompt/colorize/test_prompt_colorize.o suites/prompt/execute/test_prompt_execute.o suites/prompt/cd/test_prompt_cd.o suites/prompt/help/test_prompt_help.o suites/prompt/files/test_prompt_files.o suites/prompt/strings/test_prompt_strings.o testPrompt.o

EXP_OBJS = suites/explorer/test_explorer_traversal.o testExp.o

all: testPrompt testExp

testPrompt: $(PROMPT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

testExp: $(EXP_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f testPrompt testExp *.o test suites/*.o suites/*/*/*.o regressions/*

.PHONY: all clean

