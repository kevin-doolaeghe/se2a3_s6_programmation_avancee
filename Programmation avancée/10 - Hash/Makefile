# Makefile pour le TP Hash Table

# Nom de l'éxécutable à créer
EXEC = hash

# Nom du compilateur
CC = gcc

# Options de compilation, prêt pour utiliser valgrind
CFLAGS = -Wall -Wextra -g -O0

# Chemins et nom de la bibliothèque
# LIBNAME = liblistechaines.a
PATHLIBA = .
PATHLIBH = .

# Flags de compilation : le .h à la compilation, la bibliothèque à l'édition de liens
LDFLAGS = -L$(PATHLIBA) -llistechaines
INCLUDES= -I$(PATHLIBH)

CFILES = $(EXEC).c
OBJS  = $(patsubst %.c,%.o,$(CFILES))

all : $(EXEC)

# Edition de liens
$(EXEC) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Compilation
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm -f $(OBJS)

mrproper : clean
	rm -f $(EXEC)

.PHONY : clean
