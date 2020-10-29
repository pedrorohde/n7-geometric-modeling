CC = g++
CCOPTS = -Wall -O3

ifeq ($(UNAME_S),Darwin)
LIBS := -framework OpenGL -lglut -lstdc++ -lm -Wno-deprecated-declarations
else
LIBS := -lglut -lGLU -lGL -lstdc++ -lm
endif

all: robot

# le code fourni
robot : robot.o
	$(CC) $(CCOPTS) -o $@ $^ $(LIBS)

clean:
	rm -f *.o robot
