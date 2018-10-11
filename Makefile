CC=g++
#LIBS= -lncurses -lpthread  -lpanel -lrt -L lib/ -lcdk_ps_64 -lX11 -lGL -lGLU -lglut
LIBS= -lGL -lGLU -lglut -lncurses -lpthread	-lpanel -lrt -L lib/ -lcdk_ps_64 
#LIBS= -lGL -lGLU -lglut -lncurses -lpthread  -lpanel -lrt -L lib/ -lcdk_new 
SRC_DIR=./c
EXE_DIR=./exe


_OBJ= \
		main.o\
		screen_update.o\
		main_page.o\
		sheet.o\
		serialmanager.o\
		rs232.o\
		histograms.o\
		gantry.o\
		timer.o\
		coords.o\
		curses_color.o\
		main_page.o\
		bed.o\
		dim.o

OBJ_DIR=./obj
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

_DEP = \
		 main.h\
		 screen_update.h\
		 main_page.h\
		 sheet.h\
		 serialmanager.h\
		 rs232.h\
		 histograms.h\
		 gantry.h\
		 timer.h\
		 coords.h\
		 curses_color.h\
		 main_page.h\
		 bed.h\
		 dim.h

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
