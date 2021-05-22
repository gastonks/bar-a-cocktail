# commande pour compiler
CC=gcc
CFLAGS=-Wall
RM=rm -r
#nom des dossiers
SRC=src
OBJ=obj
DATA=data
DOC=doc
#arguments pour trouver les éléments dans les dossiers
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

#dossier pour l'executable
BINDIR=bin
BIN=$(BINDIR)/main

#programme du make
all:$(BIN)

.PHONY: clean dox

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BINDIR)/* || echo Rien à supprimer dans bin
	$(RM) $(OBJ)/* || echo Rien à supprimer dans obj
	$(RM) $(DATA)/* || echo Rien à supprimer dans dat

dox:
	mkdir $(DOC) || echo test
	doxygen Doxyfile