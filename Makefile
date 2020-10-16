CC=/usr/bin/clang
CARGS=-lncurses
COPT=-O3
TARGET=2048ncurses

all:
	$(CC) $(CARGS) $(COPT) *.c -o $(TARGET)
	
clean:
	rm -r $(TARGET)
