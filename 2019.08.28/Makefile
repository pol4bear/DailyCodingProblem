CC=g++
OBJS=main.o
TARGET=main

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

debug: $(OBJS)
	$(CC) -d -o $@ $(OBJS)

main.o: main.cpp

clean:
	rm -f $(TARGET) *.o
