IDIR =../include
CC=cc
CFLAGS=-I$(IDIR) `pkg-config --libs --cflags raylib`

ODIR=obj
LDIR =../lib

_DEPS = globalGameFunctions.h player.h dino.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o globalGameFunctions.o player.o dino.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
		$(CC) -c $< -o $@ $(CFLAGS)

main: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ main
