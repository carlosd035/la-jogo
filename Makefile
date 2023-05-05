CG = gcc;
CFLAGS = -lncurses -I$(IDIR)
IDIR = ./includes/
SRC = ./src/
SOURCES = $(SRCDIR)*.c 
all: rougue
rogue: 
	$(CC) $v(SOUCERS) $(CFLAGS) -o $@

run : 
	./rogue
