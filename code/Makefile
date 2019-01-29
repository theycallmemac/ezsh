PROMPT_SRC = src/prompt.c

PROMPT_OBJ = $(PROMPT_SRC:.c=.o)

PROMPT = prompt

EXP_SRC = src/explorer.c

EXP_OBJ = $(EXP_SRC:.c=.o)

EXP = exp


all:	$(PROMPT) $(EXP)

$(PROMPT): $(PROMPT_OBJ)
		gcc -o $(PROMPT) $(PROMPT_OBJ) -lreadline 

$(EXP): $(EXP_OBJ)
		gcc -o $(EXP) $(EXP_OBJ)

clean:
		rm $(PROMPT) $(EXP) $(PROMPT_OBJ) $(EXP_OBJ)

.PHONY: all clean

