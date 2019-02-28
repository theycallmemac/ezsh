PROMPT_SRC = src/prompt.c

PROMPT_OBJ = $(PROMPT_SRC:.c=.o)

PROMPT = prompt

EXP_SRC = src/explorer.c

EXP_OBJ = $(EXP_SRC:.c=.o)

EXP = exp

INFO_SRC = src/infograph.c

INFO_OBJ = $(INFO_SRC:.c=.o)

INFO = info

all:	$(PROMPT) $(EXP) $(INFO)

$(PROMPT): $(PROMPT_OBJ)
		gcc -o $(PROMPT) $(PROMPT_OBJ) -lreadline 

$(EXP): $(EXP_OBJ)
		gcc -o $(EXP) $(EXP_OBJ) -lncurses

$(INFO): $(INFO_OBJ)
		gcc -o $(INFO) $(INFO_OBJ) -lncurses

clean:
		rm $(PROMPT) $(EXP) $(PROMPT_OBJ) $(EXP_OBJ) $(INFO) $(INFO_OBJ)

.PHONY: all clean

