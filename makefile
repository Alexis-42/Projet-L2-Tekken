CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
INCL=include
BIN=bin
SOURCE=src

PROG=jeu

all: main
main: ${SOURCE}/main.c
	${CC} -o ${BIN}/${PROG} ${SOURCE}/main.c ${LIBS} ${INCS} ${FLAGS}
clean:
	rm -f ${BIN}/${PROG}
	rm -f ${BIN}/*.o
