# Compiler
CC          = gcc

# Executable name
TARGET      = prgm

# Paths
SRCDIR      = src
OBJDIR      = obj
PATHLIBH    = lib
PATHLIBA    = lib

# Libraries to link
LIBS        = $(addprefix -l, $(patsubst lib%, %, $(basename $(notdir $(wildcard $(PATHLIBA)/*.a))))) -lm

# Compiler and linker flags
INCLUDES    = -I$(PATHLIBH)
LDFLAGS     = -L$(PATHLIBA) $(LIBS)
CFLAGS      = -Wall -Wextra -g -O0 $(INCLUDES)

EXEC        = $(addprefix $(OBJDIR)/, $(TARGET))

CFILES      = $(notdir $(wildcard $(addprefix $(SRCDIR)/, *c)))
SRC         = $(addprefix $(SRCDIR)/, $(CFILES))

OBJ         = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

all : build

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

build : $(EXEC)

rebuild : clean build

prepare :
	mkdir $(SRCDIR) $(OBJDIR) $(PATHLIBH) $(PATHLIBA)

clean :
	rm -f $(OBJDIR)/*.o

mrproper :
	rm -fr $(OBJDIR)/*

.PHONY : clean mrproper prepare