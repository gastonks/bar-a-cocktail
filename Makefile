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

# commande pour suppresion
# Idee pour utiliser la fonction clean en fonction du systeme d'exploitation mais ne fonctionne pas: 
# ifdef _WIN32
# 	SUP = del
# 	CLEANFLAGS = /F /Q
# 	FILESUP = $(BINDIR)\* $(OBJ)\* $(DATA)\*
# else 
# 	SUP = rm
# 	CLEANFLAGS = -rf
# 	FILESUP = $(BINDIR)/* $(OBJ)/* $(DATA)/*
# endif

CLEANFLAGS = /F /Q

#programme du make

all:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

Clean pour windows :
clean:
	del $(CLEANFLAGS) $(BINDIR)\* $(OBJ)\* $(DATA)\*

# clean :
# 	rm -rf $(BINDIR)/* $(OBJ)/* $(DATA)/*