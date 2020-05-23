CC          = gcc

OBJDIR      = out
PROGS       = prog

EXEC        = $(addprefix $(OBJDIR)/, $(PROGS))
SRC         = tp6.c
OBJ         = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

CFLAGS      = -Wall -Wextra -g -O0

PATHLIBA    = .
PATHLIBH    = .

LIB         = -llistechaines
LDFLAGS     = -L$(PATHLIBA) $(LIB)
INCLUDES    = -I$(PATHLIBH)

all : $(EXEC)

$(OBJDIR)/%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean :
	rm -f $(OBJ)

mrproper : clean
	rm -f $(EXEC)