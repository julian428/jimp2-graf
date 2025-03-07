CC = gcc
CFLAGS = -Wextra -g
LDFLAGS = -lm

SRC = main.c
OBJ = $(SRC:.c=.o)
EXEC = graph

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.txt $(OBJ) $(EXEC)
