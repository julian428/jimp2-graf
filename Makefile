CC = gcc
CFLAGS = -Wextra -g
LDFLAGS = -lm

SRC = main.c lib/utils.c lib/userinput.c lib/api.c
OBJ = $(SRC:.c=.o)
EXEC = graph

all: 
	nix-shell --run "$(EXEC)"

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.txt $(OBJ) $(EXEC)
