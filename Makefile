CC=g++
#LIBS= -lncurses -lpthread  -lpanel -lrt -L lib/ -lcdk_ps_64 -lX11 -lGL -lGLU -lglut
LIBS= -lGL -lGLU -lglut -lncurses -lpthread  -lpanel -lrt -L lib/ -lcdk_ps_64 
#LIBS= -lGL -lGLU -lglut -lncurses -lpthread  -lpanel -lrt -L lib/ -lcdk_new 
SRC_DIR=./c
EXE_DIR=./exe


_OBJ= main.o screen_update.o menu.o sheet.o  bed.o serialmanager.o rs232.o histograms.o gantry.o dim.o
OBJ_DIR=./obj
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

_DEP = screen_update.h menu.h sheet.h  bed.hpp serialmanager.hpp rs232.h histograms.h gantry.h dim.h
DEP_DIR=./h
DEP = $(patsubst %,$(DEP_DIR)/%,$(_DEP))


sheet: ${OBJ}
	${CC} -o ${EXE_DIR}/$@ $^ ${LIBS}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${DEP}
	${CC}  -g -c -o $@  $< -I${DEP_DIR} 

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp ${DEP}
	${CC}  -g -c -o $@  $< -I${DEP_DIR} 
clean:
	@rm -f ${EXES} ${OBJ_DIR}/*
