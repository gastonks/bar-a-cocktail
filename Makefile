# commande pour compiler
CC=gcc
CFLAGS=-Wall

#nom des dossiers
SRC=src
OBJ=obj
DATA=data
#arguments pour trouver les éléments dans les dossiers
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

#dossier pour l'executable
BINDIR=bin
BIN=$(BINDIR)/main

CLEANFLAGS = /F /Q

#programme du make

all:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean :
	rm -rf $(BINDIR)/* $(OBJ)/* $(DATA)/*