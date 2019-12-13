CC = g++

LIBS = -lopenal -lpthread

INCDIR = inc
SRCDIR = src
OBJDIR = obj

_DEPS = al_api.h keyboard.h synth.h synth_err.h
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

_OBJ = al_api.o keyboard.o main.o synth.o synth_err.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

CFLAGS = -I$(INCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

synth: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o $(SRCDIR)/*~ core $(INCDIR)/*~