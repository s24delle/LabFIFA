CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: calibrazione


	$(CC) $(CFLAGS) -c $(CFLAGSROOT) $(LIBSROOT)
calibrazione: calibrazione.cpp 
	$(CC) $(CFLAGS) -o cia calibrazione.cpp $(CFLAGSROOT) $(LIBSROOT)

clean:
	rm *.o
