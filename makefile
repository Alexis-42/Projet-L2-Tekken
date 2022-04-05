# Nom du projet ( change le nom de l'éxécutable)
TARGET = ProjetTekken

# Compilateur
CC	= gcc

# Flags de compilation
FLAGS=-Wall -g -fcommon


# Les dossiers

SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
SRCDIR	= src
OBJDIR	= obj
HEADERDIR = include
DOCDIR = doc


# Fichiers

.PHONY: $(OBJDIR)
all: $(OBJDIR) $(TARGET)

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(HEADERDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) $(FLAGS) -o $@ ${LIBS} ${INCS}
	@echo "Link terminé!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(FLAGS) -c $< -o $@ ${LIBS} ${INCS}
	@echo $<" Compilé !"


# à voir
.PHONY: remove
remove: clean
	@rm -f $(TARGET)
	@echo "Executable enlevés !"


# compile le code
jouer:$(TARGET)
	$(clean)
	./$(TARGET)


# compile la doc
docs:
	doxygen ./Doxyfile
	firefox doc/html/index.html

# efface les .o
.PHONY: clean
clean:
	@rm -f $(OBJECTS)
	@echo "Cleanup Terminé !"

# efface la doc ( latex et html )
cleanall:
	${clean}
	rm -f $(DOCDIR)/html/search/*
	rm -f $(DOCDIR)/latex/*

jonathan:$(TARGET)
	@echo "Oh, you're approaching me ?"
	./$(TARGET) drip