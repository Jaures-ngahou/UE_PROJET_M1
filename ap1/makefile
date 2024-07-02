CC=gcc

LDFLAGS= -lm 
ARGS=-g -Wall -pthread  
OBJ= ./obj/main.o ./obj/programm.o 

EXE=./bin/limite_cpu_ram


$(EXE): $(OBJ)
	$(CC) $(ARGS) -o $(EXE) $(OBJ) $(LDFLAGS)


./obj/programm.o: ./src/programm.c  ./src/programm.h
	$(CC) $(ARGS) -o ./obj/programm.o -c ./src/programm.c 


./obj/main.o: ./src/main.c 
	$(CC) $(ARGS) -o ./obj/main.o -c ./src/main.c -I. $(LDFLAGS)


clean:
	rm -f ./obj/*
