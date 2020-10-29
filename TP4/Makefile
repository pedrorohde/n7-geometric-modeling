CC = gcc
CCOPTS = -Wall -O3

LIBS = -lGL -lglut -lm -lGLU

all:  lumiere 

solutions:  lumieresolution 

# solutions
lumieresolution: lumieresolution.o 
	$(CC) $(CCOPTS) -o $@ $^ $(LIBS)


# le code fourni
lumiere : lumiere.o 
	$(CC) $(CCOPTS) -o $@ $^ $(LIBS)


clean:
	rm -f *.o lumieresolution lumiere 

