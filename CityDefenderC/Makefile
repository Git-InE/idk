# Makefile para CityDefender

CC = gcc
CFLAGS = -Wall -g
OBJ = CityDefender.o Tablero.o Cartas.o
TARGET = CityDefender

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

CityDefender.o: CityDefender.c Tablero.h Cartas.h
	$(CC) $(CFLAGS) -c CityDefender.c

Tablero.o: Tablero.c Tablero.h
	$(CC) $(CFLAGS) -c Tablero.c

Cartas.o: Cartas.c Cartas.h
	$(CC) $(CFLAGS) -c Cartas.c

clean:
	rm -f $(OBJ) $(TARGET)