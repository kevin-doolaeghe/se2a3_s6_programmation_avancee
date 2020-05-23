CC = gcc
EXEC = out
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

PATHLIBA = .
PATHLIBH = .

LIB = 
LDFLAGS = -L$(PATHLIBA) $(LIB)
INCLUDES= -I$(PATHLIBH)

CFLAGS = -Wall -Wextra -g -O0

all : $(EXEC)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean :
	rm -f $(OBJ)

mrproper : clean
	rm -f $(EXEC)