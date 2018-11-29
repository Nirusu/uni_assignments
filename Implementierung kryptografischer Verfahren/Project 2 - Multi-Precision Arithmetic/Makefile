CC = gcc
CFLAGS = -O3 -Wall -pedantic
LIBS = -lgmp -lm
OBJ = mpa_algs.o testsuite.o main.o

# link
all:    $(OBJ)
	$(CC) -o main $(OBJ) $(LIBS)

# build object files
%.o:    %.c
	$(CC) $(CFLAGS) -c $<

# make clean
clean:
	-rm -f main
	-rm -f *.o