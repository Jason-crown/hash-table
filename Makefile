CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g

TARGET = hash_table

OBJS = main.o hashtable.o

SRC = main.c hashtable.c

OBJ = $(SRC:.c=.o)


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


run: $(TARGET)
	.\$(TARGET).exe


clean:
	del /Q *.o $(TARGET).exe 2>NUL