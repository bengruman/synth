CC = g++

LIBS = -lopenal

INCDIR = inc
SRCDIR = src
OBJDIR = obj

_DEPS = synth.h synth_err.h al_api.h
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

_OBJ = main.o synth_err.o al_api.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

CFLAGS = -I$(INCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

synth: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o $(SRCDIR)/*~ core $(INCDIR)/*~