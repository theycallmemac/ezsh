PROMPT_SRC = src/prompt.c

PROMPT_OBJ = $(PROMPT_SRC:.c=.o)

PROMPT = prompt

EXP_SRC = src/explorer.c

EXP_OBJ = $(EXP_SRC:.c=.o)

EXP = exp

INFO_SRC = src/infograph.c

INFO_OBJ = $(INFO_SRC:.c=.o)

INFO = info

MSG_SRC = src/messages.c

MSG_OBJ = $(MSG_SRC:.c=.o)

MSG = msg


all:	$(PROMPT) $(EXP) $(INFO) $(MSG)

$(PROMPT): $(PROMPT_OBJ)
		gcc -o $(PROMPT) $(PROMPT_OBJ) -lreadline -pthread

$(EXP): $(EXP_OBJ)
		gcc -o $(EXP) $(EXP_OBJ) -lncurses -pthread

$(INFO): $(INFO_OBJ)
		gcc -o $(INFO) $(INFO_OBJ) -lncurses

$(MSG): $(MSG_OBJ)
		gcc -o $(MSG) $(MSG_OBJ)


clean:
		rm $(PROMPT) $(EXP) $(PROMPT_OBJ) $(EXP_OBJ) $(INFO) $(INFO_OBJ) $(MSG) $(MSG_OBJ)

.PHONY: all clean

