CC = gcc
CFLAGS = -Wextra -g
LDFLAGS = -lm -lcurl -lcjson

SRC = main.c lib/utils.c lib/userinput.c lib/api.c
OBJ = $(SRC:.c=.o)
EXEC = graph

all: $(EXEC)

$(EXEC): $(OBJ)
	nix-shell --run "$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)"

%.o: %.c
	nix-shell --run "$(CC) $(CFLAGS) -c $< -o $@"

clean:
	rm -rf *.txt $(OBJ) $(EXEC)
