CC = gcc
EXEC = prog
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all : $(EXEC)

%.o : %.c
	$(CC) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

clean :
	rm -f $(OBJ)

mrproper : clean
	rm -f $(EXEC)