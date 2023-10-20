CC = gcc
CFLAGS = 
BINS = asciicam clean

all: $(BINS)

clean:
	rm ./build/*.o

asciicam:
	$(CC) ./src/main.c -o ./build/asciicam.exe  $(CFLAGS)
