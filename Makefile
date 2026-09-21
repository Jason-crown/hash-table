CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g

TARGET = hash_table

OBJS = main.o hashtable.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c hashtable.h
	$(CC) $(CFLAGS) -c main.c

hashtable.o: hashtable.c hashtable.h
	$(CC) $(CFLAGS) -c hashtable.c

clean:
	del $(OBJS) $(TARGET)

run: $(TARGET)
	.\$(TARGET).exe

.PHONY: clean