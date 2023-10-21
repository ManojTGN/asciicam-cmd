CC = g++
BINS = asciicam clean

CFLAGS = -Wall -Wextra
CVFLAGS = -lopencv_videoio455 -lopencv_core455 -lopencv_highgui455

CVLIB = ./opencv/build/x64/mingw/lib
CVINCLUDE = ./opencv/build/include

all: $(BINS)

clean:
	rm -f ./build/*.o

run: #only for testing will be removed on release
	./build/asciicam.exe
	rm ./*.json

ac_json.o:
	$(CC) -c ./src/ac_json.cpp -o ./build/ac_json.o

ac_cli.o: 
	$(CC) -c ./src/ac_cli.cpp -o ./build/ac_cli.o 

asciicam: ac_json.o ac_cli.o 
	$(CC) -o ./build/asciicam.exe ./src/main.cpp ./build/ac_cli.o ./build/ac_json.o -L$(CVLIB) -I$(CVINCLUDE) $(CFLAGS) $(CVFLAGS)
