IDIR =../include
CC=gcc
CFLAGS=-Wall -I $(IDIR)

ODIR=build
LDIR =../lib

LIBS=-lm

_DEPS = appointment.h list.h element.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o utility.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
OBJ_O = $(patsubst %,$(ODIR)/%,$(_OBJ))

VPATH = src

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

terminder: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

build-clean: terminder\
	clean

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~